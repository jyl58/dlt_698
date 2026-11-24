#include "dlt_698_parser.h"
#include "dlt_698_parser_private.h"
#include "dlt_698_parser_fcs.h"
#include "dlt_system_utl.h"
#include "dlt_698_cfg.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define DLT_698_FRAME_HEAD_LEN 10    // 698中除去帧头、帧尾、APDU、SA的长度，=长度(2)-控制项(1)-帧头校验(2)-帧校验(2)-地址特征(1)-展地址(1)-户机地址(1)
#define DLT_698_TIMEOUT_MS 3000      // 接收数据间隔时间
#define DLT_698_PARSE_MAX_DEPTH 4    // APDU嵌套解析最大深度（SEC明文数据单元内可嵌套APDU），防止报文驱动无限递归
#define DLT_698_PARSER_VERSION "V1.0.0"
static struct DLT_698_PRIVATE dlt_698_parser_private[DLT_698_PARSER_MAX_COUNT] = {0};

/*把实例指针映射回静态池的槽位：只有池内地址才是本库的实例。
 *用于识别"同一个 parser 重复 init"以及拒绝把任意指针当实例使用，
 *避免重复初始化耗尽实例池或往非法地址写状态。*/
static struct DLT_698_PRIVATE *dlt_698_parser_slot(const void *ins)
{
    for (int i = 0; i < DLT_698_PARSER_MAX_COUNT; i++)
    {
        if ((const void *)&dlt_698_parser_private[i] == ins)
        {
            return &dlt_698_parser_private[i];
        }
    }
    return NULL;
}

static int16_t dlt_698_parser_init_private(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->_used = 1;
    ins_ptr->_inited = 1;
    ins_ptr->_tick_ms_last = dlt_sys_start_timestamp_ms();
    ;
    ins_ptr->_timeout_ms = DLT_698_TIMEOUT_MS;
    /*复位解析中间状态：复用槽位时不能残留上一个帧的进度*/
    ins_ptr->_parse_step = DLT_698_PARSE_STEP_HEAD;
    ins_ptr->_parse_index = 0;
    ins_ptr->_payld_index = 0;
    ins_ptr->_payld_len = 0;
    ins_ptr->_parse_depth = 0;
    return DLT_698_ERR_NONE;
}
/*私有的解析用户数据的函数入口*/
static int16_t dlt_698_handle_payload_private(dlt_698_parser *parser);

const char *dlt_698_parser_version()
{
    return DLT_698_PARSER_VERSION;
}

int16_t dlt_698_parser_init(dlt_698_parser *parser, dlt_698_addr_t addr, uint8_t *buff, uint16_t buff_size, dlt_698_cb cb)
{
    /*检查空指针*/
    if ((NULL == parser) || (buff_size == 0))
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    parser->_addr = addr;
    parser->_buf = buff;
    parser->_buf_size = buff_size;
    parser->_fun = cb;
    /*同一个 parser 重复 init 时复用已经占用的槽位，否则每 init 一次就永久吃掉一个实例*/
    struct DLT_698_PRIVATE *slot = dlt_698_parser_slot(parser->_ins);
    if (NULL == slot)
    {
        for (int i = 0; i < DLT_698_PARSER_MAX_COUNT; i++)
        {
            if (0 == dlt_698_parser_private[i]._used)
            {
                slot = &dlt_698_parser_private[i];
                break;
            }
        }
    }
    if (NULL == slot)
    {
        return DLT_698_ERR_CREAT;
    }
    parser->_ins = (void *)slot;
    slot->_used = 1;
    return dlt_698_parser_init_private(parser);
}
int16_t dlt_698_parser_delete(dlt_698_parser *parser)
{
    /*检查空指针*/
    if ((NULL == parser) || (parser->_ins == NULL))
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    /*只释放本库实例池内的槽位，避免应用层指针异常时写非法内存；重复 delete 返回 EMPTY_PTR*/
    struct DLT_698_PRIVATE *ins_ptr = dlt_698_parser_slot(parser->_ins);
    if (NULL == ins_ptr)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 未初始化状态
    ins_ptr->_inited = 0;
    // 没有使用状态
    ins_ptr->_used = 0;
    parser->_ins = NULL;
    return DLT_698_ERR_NONE;
}

int16_t dlt_698_parse_frame(dlt_698_parser *parser, uint8_t *frame, uint16_t len)
{
    if (NULL == parser || parser->_ins == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }

    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    int16_t ret = DLT_698_ERR_PARSE;
    for (int i = 0; i < len; i++)
    {
        if (dlt_698_parse(parser, frame[i]) == DLT_698_ERR_NONE)
        {
            ret = DLT_698_ERR_NONE;
            break;
        }
    }
    // 无论是否解出帧，返回前都清空状态：退出后实例一定停在帧头，下一帧从头开始过滤
    ins_ptr->_parse_step = DLT_698_PARSE_STEP_HEAD;
    return ret;
}

int16_t dlt_698_parse(dlt_698_parser *parser, uint8_t c)
{
    /*解析器未创建或已 delete 时直接返回，不能解引用空的内部实例*/
    if ((NULL == parser) || (NULL == parser->_ins))
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    int16_t ret = DLT_698_ERR_PARSING;
    uint64_t now = dlt_sys_start_timestamp_ms();
    uint64_t msInterval = now - ins_ptr->_tick_ms_last;
    if (msInterval > ins_ptr->_timeout_ms)    ///< 两次接收超过误差，重新过滤
    {
        ins_ptr->_parse_step = DLT_698_PARSE_STEP_HEAD;
    }
    ins_ptr->_tick_ms_last = now;
    switch (ins_ptr->_parse_step)
    {
        case DLT_698_PARSE_STEP_HEAD:
            if (c == 0x68)
            {
                ins_ptr->_ptl.head = c;
                ins_ptr->_parse_step = DLT_698_PARSE_STEP_LEN;
                ins_ptr->_parse_index = 0;
                ins_ptr->_ptl.len = 0;
                memset(parser->_buf, 0, parser->_buf_size);
                dlt_698_fcs_init(ins_ptr);
            }
            break;
        case DLT_698_PARSE_STEP_LEN:
            ins_ptr->_ptl.len |= c << (ins_ptr->_parse_index * 8);
            ins_ptr->_parse_index++;
            /*读取两个字节长度后跳转*/
            if (ins_ptr->_parse_index >= 2)
            {
                ins_ptr->_parse_step = DLT_698_PARSE_STEP_CODE;
            }
            dlt_698_fcs_16(ins_ptr, c);
            break;
        case DLT_698_PARSE_STEP_CODE:
            ins_ptr->_ptl.code = c;
            ins_ptr->_parse_step = DLT_698_PARSE_STEP_ADDR_SA_F;
            dlt_698_fcs_16(ins_ptr, c);
            break;
        case DLT_698_PARSE_STEP_ADDR_SA_F:
            ins_ptr->_ptl.addr.sa_feature.val = c;
            uint8_t sa_logic = ins_ptr->_ptl.addr.sa_feature.st.sa_logic;
            if (sa_logic == 0x00 || sa_logic == 0x01)    // 无拓展逻辑地址
            {
                ins_ptr->_ptl.addr.ext = sa_logic;
                ins_ptr->_parse_step = DLT_698_PARSE_STEP_ADDR_SA_A;
            }
            else
            {
                ins_ptr->_parse_step = DLT_698_PARSE_STEP_ADDR_EXT;
            }
            ins_ptr->_parse_index = 0;

            dlt_698_fcs_16(ins_ptr, c);
            break;
        case DLT_698_PARSE_STEP_ADDR_EXT:
            ins_ptr->_ptl.addr.ext = c;
            ins_ptr->_parse_step = DLT_698_PARSE_STEP_ADDR_SA_A;
            ins_ptr->_parse_index = 0;
            dlt_698_fcs_16(ins_ptr, c);
            break;
        case DLT_698_PARSE_STEP_ADDR_SA_A:
            ins_ptr->_ptl.addr.sa_addr[ins_ptr->_parse_index] = c;
            ins_ptr->_parse_index++;
            /*698协议：服务器地址SA由1字节地址特征和N个字节地址组成,N包括变字节地址+1个逻辑扩展字节,地址特征字节里的地址长度是不包括逻辑扩展地址的长度（N-1）*/
            uint8_t sa_len = ins_ptr->_ptl.addr.sa_feature.st.sa_len + 1;    // 服务器器地址长度，1个逻辑地址+指定长度个服务器地址
            if (ins_ptr->_ptl.addr.ext > 1)                             // 有拓展逻辑地址
            {
                sa_len -= 1;
            }

            if (ins_ptr->_parse_index >= sa_len)
            {
                ins_ptr->_parse_step = DLT_698_PARSE_STEP_ADDR_CA;
            }
            dlt_698_fcs_16(ins_ptr, c);
            break;
        case DLT_698_PARSE_STEP_ADDR_CA:
            ins_ptr->_ptl.addr.ca = c;
            ins_ptr->_parse_step = DLT_698_PARSE_STEP_HEAD_CHECK;
            ins_ptr->_ptl.head_ck = 0;
            ins_ptr->_parse_index = 0;
            dlt_698_fcs_16(ins_ptr, c);
            ins_ptr->_parse_cs.head_cs = ins_ptr->_parse_cs._fcs ^ 0xffff;
            break;
        case DLT_698_PARSE_STEP_HEAD_CHECK:
            ins_ptr->_ptl.head_ck |= c << (ins_ptr->_parse_index * 8);
            ins_ptr->_parse_index++;
            if (ins_ptr->_parse_index >= 2)
            {
                // 比对计算得到的帧头校验和与收到的帧头校验和
                if (ins_ptr->_parse_cs.head_cs == ins_ptr->_ptl.head_ck)
                {
                    /*校验长度域下限，防止u16下溢把_payld_len算成巨大值*/
                    uint16_t sa_len_chk = ins_ptr->_ptl.addr.sa_feature.st.sa_len;
                    if (ins_ptr->_ptl.len < (DLT_698_FRAME_HEAD_LEN + sa_len_chk))
                    {
                        DLT_printf("frame len invalid:%u\n", ins_ptr->_ptl.len);
                        ins_ptr->_parse_step = DLT_698_PARSE_STEP_HEAD;
                        ret = DLT_698_ERR_PARSE;
                        break;
                    }
                    ins_ptr->_parse_step = DLT_698_PARSE_STEP_DATA;
                    ins_ptr->_parse_index = 0;
                    // 计算一个载荷的有效长度，用于后续解析处理：=接收到的总长度-长度(2)-控制项(1)-帧头校验(2)-帧校验(2)-地址特征(1)-展地址(1)-户机地址(1)-SA地址(N)
                    ins_ptr->_payld_len = ins_ptr->_ptl.len - DLT_698_FRAME_HEAD_LEN - (ins_ptr->_ptl.addr.sa_feature.st.sa_len);
                    /*载荷长度不能超过接收缓冲区，否则丢弃整帧*/
                    if (ins_ptr->_payld_len > parser->_buf_size)
                    {
                        DLT_printf("payload len %u over buf %u\n", ins_ptr->_payld_len, parser->_buf_size);
                        ins_ptr->_parse_step = DLT_698_PARSE_STEP_HEAD;
                        ret = DLT_698_ERR_OVER;
                        break;
                    }
                }
                else
                {
                    ins_ptr->_parse_step = DLT_698_PARSE_STEP_HEAD;
                }
            }
            dlt_698_fcs_16(ins_ptr, c);
            break;
        case DLT_698_PARSE_STEP_DATA:

            /*不信任L域，写入前必须检查缓冲区上限，防止越界写*/
            if (ins_ptr->_parse_index >= parser->_buf_size)
            {
                DLT_printf("payload over buf size,drop frame\n");
                ins_ptr->_parse_step = DLT_698_PARSE_STEP_HEAD;
                ret = DLT_698_ERR_OVER;
                break;
            }
            /*有效载荷数据*/
            parser->_buf[ins_ptr->_parse_index] = c;
            ins_ptr->_parse_index++;
            /*帧数据长度，是传输帧中不包含起始字符和结束字符的字节数，这里减去帧头相关长度及服务器地址长度*/
            if (ins_ptr->_parse_index >= ins_ptr->_payld_len)
            {
                ins_ptr->_parse_step = DLT_698_PARSE_STEP_FRAME_CHECK;
                ins_ptr->_parse_index = 0;
                ins_ptr->_ptl.frame_ck = 0;
                /*明确了该帧数据的长度，结果数据从_buf[ins_ptr->_payld_len]开始结构存储*/
                ins_ptr->_result_ptr = &parser->_buf[ins_ptr->_payld_len];
            }
            dlt_698_fcs_16(ins_ptr, c);
            break;
        case DLT_698_PARSE_STEP_FRAME_CHECK:
            ins_ptr->_ptl.frame_ck |= c << (ins_ptr->_parse_index * 8);
            ins_ptr->_parse_index++;
            if (ins_ptr->_parse_index >= 2)
            {
                uint16_t frame_cs = ins_ptr->_parse_cs._fcs ^ 0xffff;
                if (frame_cs == ins_ptr->_ptl.frame_ck)
                {
                    ins_ptr->_parse_step = DLT_698_PARSE_STEP_END;
                }
                else
                {
                    ins_ptr->_parse_step = DLT_698_PARSE_STEP_HEAD;
                }
            }
            break;
        case DLT_698_PARSE_STEP_END:
            if (c == 0x16)
            {
                // 载荷数据处理函数
                ret = dlt_698_handle_payload_private(parser);
                /*解析器消费的字节数超过载荷长度，说明载荷被截断，按错误帧丢弃*/
                if ((DLT_698_ERR_NONE == ret) && (ins_ptr->_payld_index > ins_ptr->_payld_len))
                {
                    ret = DLT_698_ERR_OVER;
                }
                if (DLT_698_ERR_NONE == ret)
                {    // 数据帧解析完成
                    if (NULL != parser->_fun)
                    {
                        DLT_printf("parse done. \n");
                        parser->_fun(parser);
                    }
                }
                else
                {
                    // 数据帧解析异常
                    DLT_printf("parse ERR,code:%d\n", ret);
                }
            }
            ins_ptr->_parse_step = DLT_698_PARSE_STEP_HEAD;
            break;
        default:
            break;
    }
    return ret;
}
/*第一层用户数据处理函数表*/
typedef int16_t (*dlt_698_method_fun)(dlt_698_parser *parser);
typedef struct DLT_698_METHODS
{
    uint8_t key;
    dlt_698_method_fun method;    // 698最顶层处理函数
} dlt_698_top_method_t;
static dlt_698_top_method_t dlt_698_top_method_tab[] = {
    {DLT_698_FRAME_TYPE_LINK_REQ, dlt_698_parse_link_req},  {DLT_698_FRAME_TYPE_CONN_REQ, dlt_698_parse_conn_req},    {DLT_698_FRAME_TYPE_REL_REQ, dlt_698_parse_rel_req},
    {DLT_698_FRAME_TYPE_GET_REQ, dlt_698_parse_get_req},    {DLT_698_FRAME_TYPE_SET_REQ, dlt_698_parse_set_req},      {DLT_698_FRAME_TYPE_ACT_REQ, dlt_698_parse_act_req},
    {DLT_698_FRAME_TYPE_REP_REQ, dlt_698_parse_report_req}, {DLT_698_FRAME_TYPE_SEC_REQ, dlt_698_parse_security_req}, {DLT_698_FRAME_TYPE_LINK_RES, dlt_698_parse_link_res},
    {DLT_698_FRAME_TYPE_CONN_RES, dlt_698_parse_conn_res},  {DLT_698_FRAME_TYPE_REL_RES, dlt_698_parse_rel_res},      {DLT_698_FRAME_TYPE_REL_NTY, dlt_698_parse_rel_ntf},
    {DLT_698_FRAME_TYPE_GET_RES, dlt_698_parse_get_res},    {DLT_698_FRAME_TYPE_SET_RES, dlt_698_parse_set_res},      {DLT_698_FRAME_TYPE_ACT_RES, dlt_698_parse_act_res},
    {DLT_698_FRAME_TYPE_REP_RES, dlt_698_parse_report_res}, {DLT_698_FRAME_TYPE_SEC_RES, dlt_698_parse_security_res},
};
int16_t dlt_698_parse_entry(dlt_698_parser *parser)
{
    // 循环比对处理函数值，找到后执行相应的处理函数
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    /*嵌套深度超限直接报错，防止SEC帧嵌套SEC导致栈溢出*/
    if (ins_ptr->_parse_depth >= DLT_698_PARSE_MAX_DEPTH)
    {
        return DLT_698_ERR_OVER;
    }
    if (dlt_698_payld_remain(ins_ptr) < 1)
    {
        return DLT_698_ERR_OVER;
    }
    uint8_t method_key = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    int i = 0;
    for (i = 0; i < (sizeof(dlt_698_top_method_tab)) / (sizeof(dlt_698_top_method_tab[0])); i++)
    {
        if (method_key == dlt_698_top_method_tab[i].key)
        {
            int16_t ret = DLT_698_ERR_PARSE;
            ins_ptr->_parse_depth++;
            ret = dlt_698_top_method_tab[i].method(parser);
            ins_ptr->_parse_depth--;
            return ret;
        }
    }
    if (i >= (sizeof(dlt_698_top_method_tab)) / (sizeof(dlt_698_top_method_tab[0])))
    {
        // TODO:添加未找到合适解析函数的异常处理
    }
    // 添加后续时间戳处理
    return DLT_698_ERR_PARSE;
}
int16_t dlt_698_handle_payload_private(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.time_tag = NULL;                   // 默认不带时间标签
    ins_ptr->frame.follow_report = NULL;              // 默认不带跟随报告
    ins_ptr->frame._sec_type = DLT_698_SEC_COMMON;    // 默认不带安全数据
    // 指向有效载荷起始位置
    ins_ptr->_payld_index = 0;
    ins_ptr->_parse_depth = 0;    // 每帧开始时复位嵌套深度
    // 数据从buf初始位置开始存储
    ins_ptr->_payld_ptr = parser->_buf;
    /*载荷长度达到缓冲区大小时没有剩余空间存放解析结果，防止无符号回绕出巨大内存池*/
    if (ins_ptr->_payld_len >= parser->_buf_size)
    {
        return DLT_698_ERR_OVER;
    }
    /**
     * 引入内存动态管理数据处理方式，用来存储解析完的结果，每次解析完698帧后，对存储区的内存进行初始化，用处理新的数据
     */
    // 初始化
    int16_t ret = dlt_698_mempool_init(&ins_ptr->_mem, ins_ptr->_result_ptr, (parser->_buf_size - ins_ptr->_payld_len));
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }

    return dlt_698_parse_entry(parser);
}

int32_t dlt_698_encode(dlt_698_parser *parser, uint8_t ctrl, uint8_t *apdu_ptr, int32_t apdu_len, uint8_t *des_ptr, int32_t des_len)
{
    /*检查空指针*/
    if ((NULL == parser) || (NULL == apdu_ptr) || apdu_len <= 0 || (NULL == des_ptr))
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    /*扩展逻辑地址下长度域按实际字节数计，0 表示没有服务器地址，不允许组帧*/
    if ((parser->_addr.ext > 1) && (parser->_addr.sa_feature.st.sa_len == 0))
    {
        return DLT_698_ERR_LEN;
    }

    // 数据域长度
    int32_t data_len = apdu_len + DLT_698_FRAME_HEAD_LEN + (parser->_addr.sa_feature.st.sa_len);
    ///< 整帧长度=4个前导符+数据域+2帧头帧尾
    int32_t dlt_len = 4 + data_len + 2;
    /*本库单帧上限 65535 字节：解析侧的长度入参与缓冲区下标都是 uint16_t，
     *超过这个长度组出来的帧本库自己也收不回来，因此直接报错而不是截断长度域*/
    if (dlt_len > 0xFFFF)
    {
        return DLT_698_ERR_OVER;
    }
    if (dlt_len > des_len)
    {
        return DLT_698_ERR_OVER;
    }
    int32_t pos = 0;
    // 前导符
    des_ptr[pos++] = 0xFE;
    des_ptr[pos++] = 0xFE;
    des_ptr[pos++] = 0xFE;
    des_ptr[pos++] = 0xFE;
    // 帧头
    des_ptr[pos++] = 0x68;
    // sa_len 包含SA和一个扩展逻辑地址
    // 数据长度，小端传输
    des_ptr[pos++] = (uint8_t)((data_len) & 0xFF);
    des_ptr[pos++] = (uint8_t)((data_len >> 8) & 0xFF);
    // 控制域
    des_ptr[pos++] = ctrl;
    // 地址域
    des_ptr[pos++] = parser->_addr.sa_feature.val;
    uint8_t sa_len = parser->_addr.sa_feature.st.sa_len + 1;
    if (parser->_addr.ext > 1)    ///< 包含拓展逻辑地址
    {
        sa_len -= 1;
        des_ptr[pos++] = parser->_addr.ext;
    }
    // SA地址
    for (int i = 0; i < sa_len; i++)
    {
        des_ptr[pos++] = parser->_addr.sa_addr[i];
    }
    // 客户地址
    des_ptr[pos++] = parser->_addr.ca;
    // 帧头校验和
    uint16_t head_check = dlt_698_fcs_16_block(des_ptr + 5, (uint16_t)(pos - 5));
    des_ptr[pos++] = head_check & 0xFF;
    des_ptr[pos++] = (head_check >> 8) & 0xFF;
    // 数据域
    if (NULL != apdu_ptr)
    {
        for (int32_t i = 0; i < apdu_len; i++)
        {
            des_ptr[pos++] = apdu_ptr[i];
        }
    }
    // 帧校验
    uint16_t frame_check = dlt_698_fcs_16_block(des_ptr + 5, (uint16_t)(pos - 5));
    des_ptr[pos++] = frame_check & 0xFF;
    des_ptr[pos++] = (frame_check >> 8) & 0xFF;
    des_ptr[pos++] = 0x16;
    return pos;
}
/*设置帧过滤时间阈值*/
int16_t dlt_698_set_timeout_ms(dlt_698_parser *parser, uint16_t ms)
{
    if (NULL == parser)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    /*只允许设置本库实例池内的槽位，未初始化/已释放的解析器直接拒绝*/
    struct DLT_698_PRIVATE *ins_ptr = dlt_698_parser_slot(parser->_ins);
    if (NULL == ins_ptr)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    ins_ptr->_timeout_ms = ms;
    return DLT_698_ERR_NONE;
}
/*初始化地址信息*/
int16_t dlt_698_addr_init(dlt_698_addr_t *addr_info, const char *sa, uint8_t sa_logic, uint8_t ca)
{
    if ((NULL == addr_info) || (NULL == sa))
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    int addr_len = strlen(sa);
    if (addr_len > 32)
    {
        return DLT_698_ERR_LEN;
    }
    // 地址域最大16个字节
    char addr_str[33] = {0};
    strcpy(addr_str, sa);
    if (addr_len % 2 == 1)    // 奇数
    {
        addr_str[addr_len] = 'F';
        addr_len += 1;
    }
    uint8_t addr_hex[16] = {0};
    int sa_len = dlt_698_string_hex(addr_str, addr_hex);
    /*地址长度域只有4bit：无扩展逻辑地址时表示(实际字节数-1)，可表示1~16字节；
     *有扩展逻辑地址时表示实际字节数，可表示1~15字节。越界会被位域截断，必须提前拒绝*/
    if (sa_len <= 0 || sa_len > 16)
    {
        return DLT_698_ERR_LEN;
    }
    if (sa_logic > 1 && sa_len > 15)
    {
        return DLT_698_ERR_LEN;
    }
    addr_info->sa_feature.st.sa_type = DLT_698_ADDR_SINGLE;    ///< 单地址
    if (sa_len == 1 && addr_hex[0] == 0xAA)                    ///< 广播地址的长度固定为1字节，广播地址=AAH
    {
        addr_info->sa_feature.st.sa_type = DLT_698_ADDR_BROADCAST;    ///< 广播地址
    }
    else
    {
        for (int i = 0; i < sa_len; i++)
        {
            if ((addr_hex[i] & 0xF0) == 0xA0 || (addr_hex[i] & 0x0F) == 0x0A)
            {
                addr_info->sa_feature.st.sa_type = DLT_698_ADDR_COMMON;    ///< 通配地址
                break;
            }
        }
    }
    ///< 地址长度取值范围：0…15，对应表示1…16个字节长度；
    if (sa_logic > 1)    ///< 有拓展逻辑地址
    {
        addr_info->sa_feature.st.sa_logic = 2;       ///< bit5 bit4 为 1 0
        addr_info->sa_feature.st.sa_len = sa_len;    ///< 包含一个字节的拓展逻辑地址，不需要减1
    }
    else    ///< 无拓展逻辑地址
    {
        addr_info->sa_feature.st.sa_logic = sa_logic;    ///< bit5 bit4 为 0 0或 0 1
        addr_info->sa_feature.st.sa_len = sa_len - 1;    ///< 不包含拓展逻辑地址，长度为实际长度减1
    }

    for (int i = 0; i < sa_len; i++)
    {
        addr_info->sa_addr[i] = addr_hex[sa_len - i - 1];
    }
    addr_info->ext = sa_logic;
    addr_info->ca = ca;
    return DLT_698_ERR_NONE;
}
void dlt_698_set_addr_group(dlt_698_addr_t *addr_info, uint8_t group)
{
    if (group == 1)
    {
        addr_info->sa_feature.st.sa_type = DLT_698_ADDR_GROUP;    ///< 组地址
    }
    else
    {
        addr_info->sa_feature.st.sa_type = DLT_698_ADDR_SINGLE;    ///< 单地址
        uint8_t sa_len = addr_info->sa_feature.st.sa_len + 1;
        if (addr_info->ext > 1)
        {
            sa_len -= 1;
        }
        if (sa_len == 1 && addr_info->sa_addr[0] == 0xAA)    ///< 广播地址的长度固定为1字节，广播地址=AAH
        {
            addr_info->sa_feature.st.sa_type = DLT_698_ADDR_BROADCAST;    ///< 广播地址
        }
        else
        {
            for (int i = 0; i < sa_len; i++)
            {
                if ((addr_info->sa_addr[i] & 0xF0) == 0xA0 || (addr_info->sa_addr[i] & 0x0F) == 0x0A)
                {
                    addr_info->sa_feature.st.sa_type = DLT_698_ADDR_COMMON;    ///< 通配地址
                    break;
                }
            }
        }
    }
}

int dlt_698_string_hex(const char *src_string, unsigned char *array)
{
    int len = strlen(src_string);
    char hexByte[3] = {0};
    int byteIndex = 0;
    int hexIdx = 0;
    for (int i = 0; i < len; i++)
    {
        char ch = toupper(src_string[i]);
        if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F'))
        {
            hexByte[byteIndex++] = ch;
            if (byteIndex == 2)
            {
                byteIndex = 0;
                array[hexIdx++] = (unsigned char)strtol(hexByte, NULL, 16);
            }
        }
    }
    return hexIdx;
}
