#include "dlt_698_utl_take.h"
#include "dlt_698_parser_private.h"
/**
 * 提取帧类型[GET REQ/GET RES/SET REQ/SET RES/ACT REQ/ACT RES/REP NTF/REP RES/...]
 * 参数1：698解析器实例
 * 返回值：<0见异常枚举，>0帧类型
 */
int16_t dlt_698_take_type(dlt_698_parser *parser)
{
    /*检查空指针*/
    if ((NULL == parser) || (NULL == parser->_ins))
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    if (0 == ins_ptr->frame.type)
    {
        return DLT_698_ERR_INVALID;
    }
    return ins_ptr->frame.type;
}
/**
 * 提取帧控制码
 * 参数1：698解析器实例
 * 参数2：控制码指针
 * 返回值：<0见异常枚举,=0正常
 */
int16_t dlt_698_take_code(dlt_698_parser *parser, uint8_t *code)
{
    /*检查空指针*/
    if ((NULL == parser) || (NULL == parser->_ins) || (NULL == code))
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    if (0 == ins_ptr->_ptl.code)
    {
        return DLT_698_ERR_INVALID;
    }
    *code = ins_ptr->_ptl.code;
    return DLT_698_ERR_NONE;
}
/**
 * 提取帧地址
 * 参数1：698解析器实例
 * 参数2：地址结构体指针
 * 返回值：<0见异常枚举,=0正常
 */
int16_t dlt_698_take_addr(dlt_698_parser *parser, dlt_698_addr_t *addr_ptr)
{
    /*检查空指针*/
    if ((NULL == parser) || (NULL == parser->_ins) || (NULL == addr_ptr))
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    memcpy(addr_ptr, &ins_ptr->_ptl.addr, sizeof(*addr_ptr));
    return DLT_698_ERR_NONE;
}

int16_t dlt_698_take_sa(dlt_698_addr_t *addr_ptr, char *sa, int len)
{
    if (NULL == addr_ptr || NULL == sa)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    memset(sa, 0, len);
    uint8_t sa_len = addr_ptr->sa_feature.st.sa_len + 1;
    if (addr_ptr->ext > 1)    // 包含拓展逻辑地址
    {
        sa_len -= 1;
    }
    if (sa_len * 2 + 1 > len)    ///< 最后一位\0
    {
        return DLT_698_ERR_OVER;
    }
    char buff[3] = {0};
    for (int i = sa_len - 1; i >= 0; i--)
    {
        sprintf(buff, "%02x", addr_ptr->sa_addr[i]);
        strcat(sa, buff);
    }

    return DLT_698_ERR_NONE;
}

/**
 * 提取帧处理方法[NORMAL/NORMAL LIST/RECORD/RECORD LIST/]
 * 参数1：698解析器实例
 * 返回值：<0见异常枚举，>0帧类型
 */
int16_t dlt_698_take_method(dlt_698_parser *parser)
{
    /*检查空指针*/
    if ((NULL == parser) || (NULL == parser->_ins))
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    if (0 == ins_ptr->frame.type)
    {
        return DLT_698_ERR_INVALID;
    }
    return ins_ptr->frame.method;
}
/**
 * 提取有效数据APDU
 * 参数1：698解析器实例
 * 返回值：<0见异常枚举，>=0数据长度
 */
int16_t dlt_698_take_apdu(dlt_698_parser *parser, uint8_t *buf)
{
    /*检查空指针*/
    if ((NULL == parser) || (NULL == parser->_ins) || (NULL == buf))
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    for (int i = 0; i < ins_ptr->_payld_len; i++)
    {
        buf[i] = ins_ptr->_payld_ptr[i];
    }
    return ins_ptr->_payld_len;
}
/**
 * 提取服务序号及优先标志PIID
 * 参数1：698解析器实例
 * 参数2：piid指针
 * 返回值：<0见异常枚举,=0正常
 */
int16_t dlt_698_take_piid(dlt_698_parser *parser, uint8_t *piid)
{
    /*检查空指针*/
    if ((NULL == parser) || (NULL == parser->_ins))
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    if (0 == ins_ptr->frame.type)
    {
        return DLT_698_ERR_INVALID;
    }
    *piid = ins_ptr->frame.piid;
    return DLT_698_ERR_NONE;
}
int16_t dlt_698_take_sec_type(dlt_698_parser *parser, uint8_t *sec_type)
{
    /*检查空指针*/
    if ((NULL == parser) || (NULL == parser->_ins))
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    *sec_type = ins_ptr->frame._sec_type;
    return DLT_698_ERR_NONE;
}
int16_t dlt_698_take_time_tag(dlt_698_parser *parser, dlt_698_data_t **time_tag)
{
    if ((NULL == parser) || (NULL == parser->_ins))
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    *time_tag = ins_ptr->frame.time_tag;
    return DLT_698_ERR_NONE;
}
int16_t dlt_698_take_follow_report(dlt_698_parser *parser, dlt_698_follow_report_t **follow_report)
{
    if ((NULL == parser) || (NULL == parser->_ins))
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    *follow_report = ins_ptr->frame.follow_report;
    return DLT_698_ERR_NONE;
}
/**
 * 提取数据信息链表头
 * 参数1：698解析器实例
 * 参数2：帧类型，可通过dlt_698_take_type函数获得
 * 参数3：帧方法，可通过dlt_698_take_method函数获得
 * 参数4：存放数据链表头的指针
 * 返回值：<0见异常枚举，=0正常
 */
int16_t dlt_698_take_apdu_info_head(dlt_698_parser *parser, uint8_t type, uint8_t method, void **head_ptr)
{
    /*检查空指针*/
    if ((NULL == parser) || (NULL == parser->_ins))
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    if (ins_ptr->frame._sec_type == DLT_698_SEC_COMMON)
    {
        if ((type != ins_ptr->frame.type) || (method != ins_ptr->frame.method))
        {
            return DLT_698_ERR_TAKE;
        }
    }
    switch ((enum DLT_698_FRAME_TYPE)type)
    {
        case DLT_698_FRAME_TYPE_LINK_REQ:
            *head_ptr = (void *)ins_ptr->frame.content.req_link;
            break;
        case DLT_698_FRAME_TYPE_LINK_RES:
            *head_ptr = (void *)ins_ptr->frame.content.res_link;
            break;
        case DLT_698_FRAME_TYPE_CONN_REQ:
            *head_ptr = (void *)ins_ptr->frame.content.req_conn;
            break;
        case DLT_698_FRAME_TYPE_CONN_RES:
            *head_ptr = (void *)ins_ptr->frame.content.res_conn;
            break;
        case DLT_698_FRAME_TYPE_REL_REQ:
            *head_ptr = NULL;
            break;
        case DLT_698_FRAME_TYPE_REL_RES:
            *head_ptr = (void *)ins_ptr->frame.content.res_rel;
            break;
        case DLT_698_FRAME_TYPE_REL_NTY:
            *head_ptr = (void *)ins_ptr->frame.content.rel_nty;
            break;
        case DLT_698_FRAME_TYPE_GET_REQ:    // GET请求
            switch ((enum DLT_698_GET_METHOD)method)
            {
                case DLT_698_GET_METHOD_NOR:         // GET NOMARL
                case DLT_698_GET_METHOD_NOR_LIST:    // GET NORMAL List
                    *head_ptr = (void *)ins_ptr->frame.content.req_normal;
                    break;
                case DLT_698_GET_METHOD_RECORD:    // GET RECORD
                case DLT_698_GET_METHOD_RECORD_LIST:
                    *head_ptr = (void *)ins_ptr->frame.content.req_record;
                    break;
                case DLT_698_GET_METHOD_NEXT:
                    *head_ptr = (void *)ins_ptr->frame.content.req_next;
                    break;
                case DLT_698_GET_METHOD_MD5:    // GET MD5
                    *head_ptr = (void *)ins_ptr->frame.content.req_md5;
                    break;
                default:
                    return DLT_698_ERR_TAKE;
            }
            break;
        case DLT_698_FRAME_TYPE_GET_RES:    // GET响应
            switch ((enum DLT_698_GET_METHOD)method)
            {
                case DLT_698_GET_METHOD_NOR:         // GET NOMARL
                case DLT_698_GET_METHOD_NOR_LIST:    // GET NORMAL List
                    *head_ptr = (void *)ins_ptr->frame.content.res_normal;
                    break;
                case DLT_698_GET_METHOD_RECORD:    // GET
                case DLT_698_GET_METHOD_RECORD_LIST:
                    *head_ptr = (void *)ins_ptr->frame.content.res_record;
                    break;
                case DLT_698_GET_METHOD_NEXT:
                    *head_ptr = (void *)ins_ptr->frame.content.res_next;
                    break;
                case DLT_698_GET_METHOD_MD5:
                    *head_ptr = (void *)ins_ptr->frame.content.res_md5;
                    break;

                default:
                    return DLT_698_ERR_TAKE;
            }
            break;
        case DLT_698_FRAME_TYPE_SET_REQ:    // SET请求
            switch ((enum DLT_698_SET_METHOD)method)
            {
                case DLT_698_SET_METHOD_NOR:
                case DLT_698_SET_METHOD_NOR_LIST:
                    *head_ptr = (void *)ins_ptr->frame.content.req_set;
                    break;
                case DLT_698_SET_METHOD_SET_GET_LIST:
                    *head_ptr = (void *)ins_ptr->frame.content.req_set_get;
                    break;
                default:
                    break;
            }
            break;
        case DLT_698_FRAME_TYPE_SET_RES:    // SET响应
            switch ((enum DLT_698_SET_METHOD)method)
            {
                case DLT_698_SET_METHOD_NOR:
                case DLT_698_SET_METHOD_NOR_LIST:
                    *head_ptr = (void *)ins_ptr->frame.content.res_set;
                    break;
                case DLT_698_SET_METHOD_SET_GET_LIST:
                    *head_ptr = (void *)ins_ptr->frame.content.res_set_get;
                    break;
                default:
                    break;
            }
            break;
        case DLT_698_FRAME_TYPE_ACT_REQ:    // ACT请求
            switch ((enum DLT_698_ACT_METHOD)method)
            {
                case DLT_698_ACT_METHOD_NOR:
                case DLT_698_ACT_METHOD_NOR_LIST:
                    *head_ptr = (void *)ins_ptr->frame.content.req_act;
                    break;
                case DLT_698_ACT_METHOD_SET_GET_LIST:
                    *head_ptr = (void *)ins_ptr->frame.content.req_act_get;
                    break;
                default:
                    break;
            }
            break;
        case DLT_698_FRAME_TYPE_ACT_RES:    // ACT响应
            switch ((enum DLT_698_ACT_METHOD)method)
            {
                case DLT_698_ACT_METHOD_NOR:
                case DLT_698_ACT_METHOD_NOR_LIST:
                    *head_ptr = (void *)ins_ptr->frame.content.res_act;
                    break;
                case DLT_698_ACT_METHOD_SET_GET_LIST:
                    *head_ptr = (void *)ins_ptr->frame.content.res_act_get;
                    break;
                default:
                    break;
            }
            break;
        case DLT_698_FRAME_TYPE_REP_REQ:    // 上报请求
            switch ((enum DLT_698_REP_METHOD)method)
            {
                case DLT_698_REP_METHOD_NOTIFY_LIST:
                    *head_ptr = (void *)ins_ptr->frame.content.ntf_normal;
                    break;
                case DLT_698_REP_METHOD_NOTIFY_RECORD_LIST:
                    *head_ptr = (void *)ins_ptr->frame.content.ntf_record;
                    break;
                case DLT_698_REP_METHOD_NOTIFY_TRANS:
                    *head_ptr = (void *)ins_ptr->frame.content.ntf_trans;
                    break;
                default:
                    break;
            }
            break;
        case DLT_698_FRAME_TYPE_REP_RES:    // 上报响应
            switch ((enum DLT_698_REP_METHOD)method)
            {
                case DLT_698_REP_METHOD_NOTIFY_LIST:
                case DLT_698_REP_METHOD_NOTIFY_RECORD_LIST:
                    *head_ptr = (void *)ins_ptr->frame.content.res_nor_rec;
                    break;
                case DLT_698_REP_METHOD_NOTIFY_TRANS:
                    *head_ptr = NULL;    // 透传响应没有具体数据要解析，收到响应帧即可
                    break;
                default:
                    break;
            }
            break;
        case DLT_698_FRAME_TYPE_SEC_REQ:
            *head_ptr = (void *)ins_ptr->frame.req_sec;
            break;
        case DLT_698_FRAME_TYPE_SEC_RES:
            *head_ptr = (void *)ins_ptr->frame.res_sec;
            break;
    }

    return DLT_698_ERR_NONE;
}