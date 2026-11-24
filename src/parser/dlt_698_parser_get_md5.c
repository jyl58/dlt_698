#include "dlt_698_parser_get_md5.h"
#include "dlt_698_parser_private.h"
#include "dlt_698_parser_widget.h"
/*解析GET MD5 请求*/
int16_t dlt_698_parse_get_req_md5(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.req_md5 = (struct DLT_698_GET_MD5_REQ *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_GET_MD5_REQ));
    if (ins_ptr->frame.content.req_md5 == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    return dlt_698_parse_oad(ins_ptr, &ins_ptr->frame.content.req_md5->oad);
}

/*解析GET MD5 响应*/
int16_t dlt_698_parse_get_res_md5(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.res_md5 = (struct DLT_698_GET_MD5_RES *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_GET_MD5_RES));
    if (ins_ptr->frame.content.res_md5 == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    int16_t ret = dlt_698_parse_oad(ins_ptr, &ins_ptr->frame.content.res_md5->oad);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }

    uint8_t result = 0;
    ret = dlt_698_payld_read_u8(ins_ptr, &result);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    uint8_t data_type = 0;
    if (result == 0)
    {
        ret = dlt_698_payld_read_u8(ins_ptr, &ins_ptr->frame.content.res_md5->dar);
        if (ret != DLT_698_ERR_NONE)
        {
            return ret;
        }
    }
    else
    {
        ins_ptr->frame.content.res_md5->dar = 0;
        data_type = 9;    ///< octet_string
    }
    // 解析数据信息
    return dlt_698_parse_data(ins_ptr, data_type, &ins_ptr->frame.content.res_md5->data);
}
