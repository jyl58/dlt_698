#ifndef DLT_698_PARSER_PRIVATE_H_
#define DLT_698_PARSER_PRIVATE_H_
#include "dlt_698_type.h"
#include "dlt_698_parser.h"
#include "dlt_698_data.h"

#include "dlt_698_parser_get.h"
#include "dlt_698_parser_set.h"
#include "dlt_698_parser_action.h"
#include "dlt_698_parser_report.h"
#include "dlt_698_parser_security.h"
#include "dlt_698_parser_link.h"
#include "dlt_698_parser_connect.h"

#include "dlt_698_mempool.h"
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)
    /*698数据帧解析步骤状态机*/
    enum DLT_698_STEP
    {
        DLT_698_PARSE_STEP_HEAD = 0,
        DLT_698_PARSE_STEP_LEN,
        DLT_698_PARSE_STEP_CODE,
        DLT_698_PARSE_STEP_ADDR_SA_F,    // 服务器地址特征字
        DLT_698_PARSE_STEP_ADDR_EXT,     // 服务器扩展地址
        DLT_698_PARSE_STEP_ADDR_SA_A,    // 服务器地址
        DLT_698_PARSE_STEP_ADDR_CA,      // 客户机地址
        DLT_698_PARSE_STEP_HEAD_CHECK,
        DLT_698_PARSE_STEP_DATA,
        DLT_698_PARSE_STEP_FRAME_CHECK,
        DLT_698_PARSE_STEP_END
    };

    // 帧校验用到的结构体
    struct DLT_698_FCS
    {
        uint16_t head_cs;    // 计算得到协议头校验和
        uint16_t _fcs;       // FCS算法中间变量及整帧最后的校验值
    };
    struct DLT_698_PRIVATE
    {
        uint8_t _used : 1;         // 多个解析器池时，表征该实例已经分配完成
        uint8_t _inited : 1;       // 初始化完成标识
        uint64_t _tick_ms_last;    ///< 用于记录上次解析时间，用于超时检测
        uint16_t _timeout_ms;      ///< 超过阈值重新进行帧过滤 (默认3000ms)
        struct
        {
            /**
             *数据帧类型
             *{0x05,GET,请求},
             *{0x06,SET,请求},
             *{0x07,ACT,请求},
             *{0x08,REP,上报请求},
             *{0x09,PROXY,代理请求(暂未支持)}，
             *{0x10,SEC,安全请求(单独处理)},
             *{0x85,GET,响应},
             *{0x86,SET,响应},
             *{0x87,ACT,响应},
             *{0x88,REP,响应},
             *{0x89,PROXY,代理请求(暂未支持)},
             *{0x90,SEC,安全响应(单独处理)},
             */
            uint8_t type;
            /**
             *每个数据帧各自的数据处理方法
             *{0x05,GET,请求,[0]NULL,[1]GetRequestNormal,[2]GetRequestNormalList,[3]GetRequestRecord,[4]GetRequestRecordList,[5]GetRequestNext,[6]GetRequestMD5},
             *{0x06,SET,请求,[0]NULL,[1]SetRequestNormal,[2]SetRequestNormalList,[3]SetThenGetRequestNormalList},
             *{0x07,ACT,请求,[0]NULL,[1]ActionRequestNormal，[2]ActionRequestNormalList，[3]ActionThenGetRequestNormalList},
             *{0x08,REP,请求,[0]NULL,[1]ActionRequestNormal，[2]ActionRequestNormalList，[3]ActionThenGetRequestNormalList},
             *{0x09,PROXY,代理请求(暂未支持)}，
             *{0x10,SEC,安全请求(单独处理),[0]SID_MAC；[1]RN；[2]RN_MAC；[3]SID;},
             *{0x85,GET,响应,[0]NULL[1]GetResponseNormal,[2]GetResponseNormalList,[3]GetResponseRecord,[4]GetResponseRecordList,[5]GetResponseNext,[6]GetResponseMD5},
             *{0x86,SET,响应,[0]NULL[1]SetResponseNormal,[2]SetResponseNormalList,[3]SetThenGetResponseNormalList},
             *{0x87,ACT,响应,[0]NULL[1]ActionResponseNormal,[2]ActionResponseNormalList,[3]ActionThenGetResponseNormalList},
             *{0x88,REP,响应,[0]NULL[1]ReportResponseList,[2]ReportResponseRecordList,[3]ReportResponseTransData},
             *{0x90,SEC,安全响应(单独处理),[0]MAC},
             */
            uint8_t method;
            /**
             * 服务序号-优先级 PIID
             */
            uint8_t piid;
            dlt_698_data_t *time_tag;                  // 时间标签域
            dlt_698_follow_report_t *follow_report;    // 跟随上报数据
            union
            {
                /*GET 相关的操作*/
                struct DLT_698_GET_NOR_REQ *req_normal;    // GET normal/List 数据结构
                struct DLT_698_GET_NOR_RES *res_normal;    // GET normal reponse/List 数据结构
                struct DLT_698_GET_REC_REQ *req_record;    // 请求一个记录型数据结构
                struct DLT_698_GET_REC_RES *res_record;    // 回复一个记录型数据结构
                struct DLT_698_GET_NEXT_REQ *req_next;     // 请求下一个帧数据结构
                struct DLT_698_GET_NEXT_RES *res_next;     // 回复下一个帧数据结构,有可能会跟res_normal 或res_record同时存在
                struct DLT_698_GET_MD5_REQ *req_md5;       // GET MD5
                struct DLT_698_GET_MD5_RES *res_md5;       // 回复MD5请求

                /*SET 相关的操作*/
                struct DLT_698_SET_NOR_REQ *req_set;        // SET Request normal/List 数据结构
                struct DLT_698_SET_NOR_RES *res_set;        // SET Response normal/List 数据结构
                struct DLT_698_SET_GET_REQ *req_set_get;    // 请求SET then GET
                struct DLT_698_SET_GET_RES *res_set_get;    // 响应SET then GET
                /*ACTION 相关的操作*/
                struct DLT_698_ACT_NOR_REQ *req_act;        // ACTION Request normal/List 数据结构
                struct DLT_698_ACT_NOR_RES *res_act;        // ACTION 响应数据结构
                struct DLT_698_ACT_GET_REQ *req_act_get;    // ACT GET 请求
                struct DLT_698_ACT_GET_RES *res_act_get;    // ACT GET 响应
                /*REPORT 相关的操作*/
                struct DLT_698_REP_NTF_NOR *ntf_normal;     // REPORT normal list
                struct DLT_698_REP_NTF_REC *ntf_record;     // REPORT record list
                struct DLT_698_REP_RES_NOR *res_nor_rec;    // REPORT 属性/记录型响应
                struct DLT_698_REP_NTF_TRANS *ntf_trans;    // 上报TRANS数据

                /*LINK 相关的操作*/
                struct DLT_698_LINK_REQ *req_link;    // LINK-Request
                struct DLT_698_LINK_RES *res_link;    // LINK-Response

                /*CONNECT 相关的操作*/
                struct DLT_698_CONN_REQ *req_conn;    // CONNECT-Request
                struct DLT_698_CONN_RES *res_conn;    // CONECT-Response
                struct DLT_698_REL_RES *res_rel;      // RELEASE-Response
                struct DLT_698_REL_NTF *rel_nty;      // RELEASE-Notification

            } content;
            uint8_t _sec_type;    // 安全传输类型，0普通 1安全请求 2安全响应
            /*security 相关的操作*/
            struct DLT_698_SEC_REQ *req_sec;    // SECURITY-Request
            struct DLT_698_SEC_RES *res_sec;    // SECURITY-Request
        } frame;

        /*数据帧解析过程中的状态变量*/
        struct DLT_698_FCS _parse_cs;     // 帧校验和相关数据存储
        enum DLT_698_STEP _parse_step;    // 数据解析步骤状态机
        uint16_t _payld_len;                   // 有效载荷的有效长度
        uint16_t _payld_index;                 // 有效载荷的解析索引，会从载荷位置逐渐递增，用来解析ADPU数据
        uint8_t *_payld_ptr;                   // 指向载荷起始位置，默认指向应用层提供的buf起始位置
        struct
        {
            uint8_t head;                // 帧头
            uint16_t len;                // 长度域L  是传输帧中不包含起始字符和结束字符的字节数；
            uint8_t code;                // 控制域C  Bit7:传输方向DIR;Bit6:启动标志PRM;Bit5:分帧标志;Bit4保留;Bit3:扰码标志SC:Bit[0-2]功能码
            dlt_698_addr_t addr;    // 地址域A
            uint16_t head_ck;            // 帧头校验HCS
            uint16_t frame_ck;           // 帧校验FCS
            uint8_t end;                 // 结束字符（16H）
        } _ptl;
        uint16_t _parse_index;    // 数据帧解析过程中的数据递增索引
        uint8_t _parse_depth;     // APDU嵌套解析深度（SEC明文帧内可再嵌套APDU），防止递归栈溢出
        /*
         *请求或者响应解析结果的起始地址，从应用层提供的_buf中数据帧结束的位置开始结构化（避免动态申请内存），应用层要根据实际情况提供足够的ram空间。
         */
        void *_result_ptr;
        /*内存池数据结构，用来动态存储不确定个数的数据结构信息*/
        dlt_698_mem_manage_t _mem;
    };

    int16_t dlt_698_parse_entry(dlt_698_parser *parser);

#pragma pack()
#ifdef __cplusplus
}
#endif

#endif    // DLT_698_PARSER_PRIVATE_H_