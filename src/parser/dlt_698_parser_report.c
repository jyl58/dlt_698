#include "dlt_698_parser_report.h"
#include "dlt_698_parser_private.h"
#include "dlt_698_parser_widget.h"
typedef int16_t (*dlt_698_rep_fun)(dlt_698_parser *parser);
/*解析REPORT 请求数据*/
/*解析REPORT各类型处理函数集，根据方法索引选择对应的函数*/
static const dlt_698_rep_fun dlt_698_handle_rep_req_tab[] = {
    NULL,                                 // 规范里REPORT 索引0是不存在的,占个位
    dlt_698_parse_rep_ntf_normal_list,    // 请求REPORT多个属性值
    dlt_698_parse_rep_ntf_record_list,    // 请求REPORT多个记录值
    dlt_698_parse_rep_ntf_trans,          // REPORT 透明传输数据
};

int16_t dlt_698_parse_report_req(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.type = DLT_698_FRAME_TYPE_REP_REQ;    // 0x08是请求方法

    // 获取REP处理方法
    ins_ptr->frame.method = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    // 获取PIID
    ins_ptr->frame.piid = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    if ((ins_ptr->frame.method == 0) || (ins_ptr->frame.method >= (sizeof(dlt_698_handle_rep_req_tab)) / (sizeof(dlt_698_handle_rep_req_tab[0]))))
    {
        // TODO::get handle 函数索引超出预定数组，需要进行异常处理
        return DLT_698_ERR_PARSE;
    }
    int16_t ret = dlt_698_handle_rep_req_tab[ins_ptr->frame.method](parser);
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


/*解析REPORT 请求数据*/
/*解析REPORT各类型处理函数集，根据方法索引选择对应的函数*/
static const dlt_698_rep_fun dlt_698_handle_rep_res_tab[] = {
    NULL,                                 // 规范里REPORT 索引0是不存在的,占个位
    dlt_698_parse_rep_res_normal_list,    // 响应REPORT多个属性值
    dlt_698_parse_rep_res_record_list,    // 响应REPORT多个记录值
    dlt_698_parse_rep_res_trans,          // 响应REPORT 透明传输数据
};
/*解析REPORT 响应数据*/
int16_t dlt_698_parse_report_res(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    // 0x88是请求方法
    ins_ptr->frame.type = DLT_698_FRAME_TYPE_REP_RES;
    // 获取REP处理方法
    ins_ptr->frame.method = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    // 获取PIID
    ins_ptr->frame.piid = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    if ((ins_ptr->frame.method == 0) || (ins_ptr->frame.method >= (sizeof(dlt_698_handle_rep_res_tab)) / (sizeof(dlt_698_handle_rep_res_tab[0]))))
    {
        // TODO::get handle 函数索引超出预定数组，需要进行异常处理
        return DLT_698_ERR_PARSE;
    }
    int16_t ret = dlt_698_handle_rep_res_tab[ins_ptr->frame.method](parser);
    if (ret == DLT_698_ERR_NONE)    // 解析成功
    {
        ret = dlt_698_parse_TimeTag(ins_ptr, &ins_ptr->frame.time_tag);
    }
    return ret;
}