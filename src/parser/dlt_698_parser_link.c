#include "dlt_698_parser_link.h"
#include "dlt_698_parser_widget.h"

int16_t dlt_698_parse_link_req(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.req_link = (struct DLT_698_LINK_REQ *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_LINK_REQ));
    if (ins_ptr->frame.content.req_link == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    ins_ptr->frame.type = DLT_698_FRAME_TYPE_LINK_REQ;
    /*帧头固定域：PIID(1)+请求类型(1)+心跳周期(2)*/
    if (dlt_698_payld_need(ins_ptr, 4) != DLT_698_ERR_NONE)
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->frame.piid = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    ins_ptr->frame.content.req_link->req_type = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    ins_ptr->frame.content.req_link->heart_cycle = (ins_ptr->_payld_ptr[ins_ptr->_payld_index] << 8) + ins_ptr->_payld_ptr[ins_ptr->_payld_index + 1];
    ins_ptr->_payld_index += 2;
    int16_t ret = dlt_698_parse_date_time(ins_ptr, &ins_ptr->frame.content.req_link->req_dt);
    return ret;
}
int16_t dlt_698_parse_link_res(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.res_link = (struct DLT_698_LINK_RES *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_LINK_RES));
    if (ins_ptr->frame.content.res_link == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    ins_ptr->frame.type = DLT_698_FRAME_TYPE_LINK_RES;
    /*帧头固定域：PIID(1)+执行结果(1)*/
    if (dlt_698_payld_need(ins_ptr, 2) != DLT_698_ERR_NONE)
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->frame.piid = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    ins_ptr->frame.content.res_link->result = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    int16_t ret = dlt_698_parse_date_time(ins_ptr, &ins_ptr->frame.content.res_link->req_dt);
    if (ret == DLT_698_ERR_NONE)
    {
        ret = dlt_698_parse_date_time(ins_ptr, &ins_ptr->frame.content.res_link->recv_dt);
    }
    if (ret == DLT_698_ERR_NONE)
    {
        ret = dlt_698_parse_date_time(ins_ptr, &ins_ptr->frame.content.res_link->res_dt);
    }
    return ret;
}