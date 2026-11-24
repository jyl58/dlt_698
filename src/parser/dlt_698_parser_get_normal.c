#include "dlt_698_parser_get_normal.h"
#include "dlt_698_parser_private.h"
#include "dlt_698_parser_widget.h"
int16_t dlt_698_parse_get_req_normal(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.req_normal = (struct DLT_698_GET_NOR_REQ *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_GET_NOR_REQ));
    if (ins_ptr->frame.content.req_normal == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    // 使用内存池管理工具，申请一个struct DLT_698_OAD结构
    ins_ptr->frame.content.req_normal->oad_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (ins_ptr->frame.content.req_normal->oad_ptr == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    return dlt_698_parse_oad(ins_ptr, ins_ptr->frame.content.req_normal->oad_ptr);
}
/*解析GET NORMAL LIST 请求数，根据数据序列设计，不能随便调整语句执行顺序*/
int16_t dlt_698_parse_get_req_normal_list(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.req_normal = (struct DLT_698_GET_NOR_REQ *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_GET_NOR_REQ));
    if (ins_ptr->frame.content.req_normal == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    // 获取到OAD个数
    uint8_t oad_cnt = 0;
    int16_t ret = dlt_698_payld_read_u8(ins_ptr, &oad_cnt);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    ins_ptr->frame.content.req_normal->oad_ptr = NULL;
    dlt_698_data_t **node_father = &ins_ptr->frame.content.req_normal->oad_ptr;
    for (int i = 0; i < oad_cnt; i++)
    {
        uint16_t next_index = ins_ptr->_mem.alloc_mempool_size;
        dlt_698_data_t *unit_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
        if (unit_ptr == NULL)
        {
            return DLT_698_ERR_MEM;
        }
        DLT_698_append_next(dlt_698_data_t, ins_ptr->_mem.start, node_father, next_index);
        ret = dlt_698_parse_oad(ins_ptr, unit_ptr);
        if (ret != DLT_698_ERR_NONE)
        {
            return ret;
        }
    }
    return DLT_698_ERR_NONE;
}

int16_t dlt_698_parse_get_res_normal(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.res_normal = (struct DLT_698_GET_NOR_RES *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_GET_NOR_RES));
    if (ins_ptr->frame.content.res_normal == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    ins_ptr->frame.content.res_normal->normal_ptr = (struct DLT_698_Result_Normal *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_Result_Normal));
    if (ins_ptr->frame.content.res_normal->normal_ptr == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    return dlt_698_parse_result_normal(ins_ptr, ins_ptr->frame.content.res_normal->normal_ptr);
}

int16_t dlt_698_parse_get_res_normal_list(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.res_normal = (struct DLT_698_GET_NOR_RES *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_GET_NOR_RES));
    if (ins_ptr->frame.content.res_normal == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    uint8_t res_cnt = 0;
    int16_t ret = dlt_698_payld_read_u8(ins_ptr, &res_cnt);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    ins_ptr->frame.content.res_normal->normal_ptr = NULL;
    struct DLT_698_Result_Normal **node_father = &ins_ptr->frame.content.res_normal->normal_ptr;
    // 循环解析每一个数据块信息
    for (int i = 0; i < res_cnt; i++)
    {
        uint16_t next_index = ins_ptr->_mem.alloc_mempool_size;
        struct DLT_698_Result_Normal *node_ptr = (struct DLT_698_Result_Normal *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_Result_Normal));
        if (node_ptr == NULL)
        {
            return DLT_698_ERR_MEM;
        }
        DLT_698_append_next(struct DLT_698_Result_Normal, ins_ptr->_mem.start, node_father, next_index);
        ret = dlt_698_parse_result_normal(ins_ptr, node_ptr);
        if (ret != DLT_698_ERR_NONE)
        {
            return ret;
        }
    }
    return DLT_698_ERR_NONE;
}
