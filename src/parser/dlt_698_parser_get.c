#include "dlt_698_parser_get.h"
#include "dlt_698_parser_private.h"
#include "dlt_698_parser_get_normal.h"
#include "dlt_698_parser_get_record.h"
#include "dlt_698_parser_get_md5.h"
#include "dlt_698_parser_widget.h"
typedef int16_t (*dlt_698_get_fun)(dlt_698_parser *parser);
/*解析GET各类型处理函数集，根据方法索引选择对应的函数*/
static const dlt_698_get_fun dlt_698_handle_get_req_tab[] = {
    NULL,                                 // 规范里GET 索引0是不存在的,占个位
    dlt_698_parse_get_req_normal,         // 请求GET一个属性值
    dlt_698_parse_get_req_normal_list,    // 请求GET多个属性值
    dlt_698_parse_get_req_record,         // 请求GET一个记录型
    dlt_698_parse_get_req_record_list,    // 请求GET多个记录型
    dlt_698_parse_get_req_next,           // 请求GET NEXT
    dlt_698_parse_get_req_md5,            // 请求GET MD5

};
int16_t dlt_698_parse_get_req(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.type = DLT_698_FRAME_TYPE_GET_REQ;    // 0x05是请求方法
    /*帧头固定域至少需要 method + PIID 两个字节*/
    if (dlt_698_payld_need(ins_ptr, 2) != DLT_698_ERR_NONE)
    {
        return DLT_698_ERR_OVER;
    }
    // 获取GET处理方法
    ins_ptr->frame.method = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    // 获取PIID
    ins_ptr->frame.piid = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    if ((ins_ptr->frame.method == 0) || (ins_ptr->frame.method >= (sizeof(dlt_698_handle_get_req_tab)) / (sizeof(dlt_698_handle_get_req_tab[0]))))
    {
        // TODO::get handle 函数索引超出预定数组，需要进行异常处理
        return DLT_698_ERR_PARSE;
    }

    int16_t ret = dlt_698_handle_get_req_tab[ins_ptr->frame.method](parser);
    if (ret == DLT_698_ERR_NONE)    // 解析成功
    {
        ret = dlt_698_parse_TimeTag(ins_ptr, &ins_ptr->frame.time_tag);
    }
    return ret;
}

/*解析GET各类型处理函数集，根据实际方法选择对应的函数*/
static const dlt_698_get_fun dlt_698_handle_get_res_tab[] = {
    NULL,                                 // 规范里GET 索引0是不存在的,占个位
    dlt_698_parse_get_res_normal,         // 响应GET一个属性值
    dlt_698_parse_get_res_normal_list,    // 响应GET多个属性值
    dlt_698_parse_get_res_record,         // 记录响应请求处理
    dlt_698_parse_get_res_record_list,    // 响应GET多个记录型值
    dlt_698_parse_get_res_next,           // 响应NEXT请求
    dlt_698_parse_get_res_md5,            // 响应GET MD5
};
int16_t dlt_698_parse_get_res(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.type = DLT_698_FRAME_TYPE_GET_RES;    // 0x85是响应方法
    /*帧头固定域至少需要 method + PIID 两个字节*/
    if (dlt_698_payld_need(ins_ptr, 2) != DLT_698_ERR_NONE)
    {
        return DLT_698_ERR_OVER;
    }
    // 获取GET处理方法
    ins_ptr->frame.method = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    // 获取PIID
    ins_ptr->frame.piid = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    if ((ins_ptr->frame.method == 0) || (ins_ptr->frame.method >= (sizeof(dlt_698_handle_get_res_tab)) / (sizeof(dlt_698_handle_get_res_tab[0]))))
    {
        // TODO::get handle 函数索引超出预定数组，需要进行异常处理
        return DLT_698_ERR_PARSE;
    }
    int16_t ret = dlt_698_handle_get_res_tab[ins_ptr->frame.method](parser);
    if (ret == DLT_698_ERR_NONE)
    {
        ret = dlt_698_parse_FollowReportTag(ins_ptr, &ins_ptr->frame.follow_report);
        if (ret == DLT_698_ERR_NONE)
        {
            ret = dlt_698_parse_TimeTag(ins_ptr, &ins_ptr->frame.time_tag);
        }
    }
    return ret;
}