#include "dlt_698_parser_get_record.h"
#include "dlt_698_parser_private.h"
#include "dlt_698_parser_widget.h"

static int16_t dlt_698_parse_get_req_record_result(struct DLT_698_PRIVATE *ins_ptr, struct DLT_698_GET_RECORD *rec_ptr)
{
    rec_ptr->next_index = 0;
    // 解析OAD
    int16_t ret = dlt_698_parse_oad(ins_ptr, &rec_ptr->oad);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    // 解析RSD数据
    ret = dlt_698_parse_rsd(ins_ptr, &rec_ptr->rsd);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    // 解析RCSD数据
    ret = dlt_698_parse_rcsd(ins_ptr, &rec_ptr->rcsd);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    return DLT_698_ERR_NONE;
}
/*解析请求一个记录型数据*/
int16_t dlt_698_parse_get_req_record(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.req_record = (struct DLT_698_GET_REC_REQ *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_GET_REC_REQ));
    if (ins_ptr->frame.content.req_record == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    ins_ptr->frame.content.req_record->rec_ptr = (struct DLT_698_GET_RECORD *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_GET_RECORD));
    if (ins_ptr->frame.content.req_record->rec_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    return dlt_698_parse_get_req_record_result(ins_ptr, ins_ptr->frame.content.req_record->rec_ptr);
}
/*解析请求多个记录型数据*/
int16_t dlt_698_parse_get_req_record_list(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.req_record = (struct DLT_698_GET_REC_REQ *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_GET_REC_REQ));
    if (ins_ptr->frame.content.req_record == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    uint8_t req_cnt = 0;
    int16_t ret = dlt_698_payld_read_u8(ins_ptr, &req_cnt);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    ins_ptr->frame.content.req_record->rec_ptr = NULL;
    struct DLT_698_GET_RECORD **node_father = &ins_ptr->frame.content.req_record->rec_ptr;
    for (int i = 0; i < req_cnt; i++)
    {
        uint16_t next_index = ins_ptr->_mem.alloc_mempool_size;
        // 向内存池申请一个struct DLT_698_GET_REC_REQ_NODE结构
        struct DLT_698_GET_RECORD *node_ptr = (struct DLT_698_GET_RECORD *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_GET_RECORD));
        if (node_ptr == NULL)
        {
            return DLT_698_ERR_EMPTY_PTR;
        }
        DLT_698_append_next(struct DLT_698_GET_RECORD, ins_ptr->_mem.start, node_father, next_index);
        ret = dlt_698_parse_get_req_record_result(ins_ptr, node_ptr);
        if (ret != DLT_698_ERR_NONE)
        {
            return ret;
        }
    }

    return DLT_698_ERR_NONE;
}

/*解析响应一个记录型数据*/
int16_t dlt_698_parse_get_res_record(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.res_record = (struct DLT_698_GET_REC_RES *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_GET_REC_RES));
    if (ins_ptr->frame.content.res_record == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    ins_ptr->frame.content.res_record->rec_ptr = (struct DLT_698_RESULT_RECORD *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_RESULT_RECORD));
    if (ins_ptr->frame.content.res_record->rec_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    return dlt_698_parse_get_res_record_result(ins_ptr, ins_ptr->frame.content.res_record->rec_ptr);
}
/*响应读取多个记录型数据*/
int16_t dlt_698_parse_get_res_record_list(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.res_record = (struct DLT_698_GET_REC_RES *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_GET_REC_RES));
    if (ins_ptr->frame.content.res_record == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // List记录数据回复有多个数据单元
    uint8_t rec_cnt = 0;
    int16_t ret = dlt_698_payld_read_u8(ins_ptr, &rec_cnt);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    ins_ptr->frame.content.res_record->rec_ptr = NULL;
    struct DLT_698_RESULT_RECORD **node_father = &ins_ptr->frame.content.res_record->rec_ptr;
    // 循环解析多个记录回复数据单元
    for (int i = 0; i < rec_cnt; i++)
    {
        uint16_t next_index = ins_ptr->_mem.alloc_mempool_size;
        // 向内存池申请一个struct DLT_698_GET_REC_RES_NODE数据结构
        struct DLT_698_RESULT_RECORD *node_ptr = (struct DLT_698_RESULT_RECORD *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_RESULT_RECORD));
        if (node_ptr == NULL)
        {
            return DLT_698_ERR_EMPTY_PTR;
        }
        DLT_698_append_next(struct DLT_698_RESULT_RECORD, ins_ptr->_mem.start, node_father, next_index);
        ret = dlt_698_parse_get_res_record_result(ins_ptr, node_ptr);
        if (ret != DLT_698_ERR_NONE)
        {
            return ret;
        }
    }
    return DLT_698_ERR_NONE;
}
