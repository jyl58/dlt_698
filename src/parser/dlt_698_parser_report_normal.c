#include "dlt_698_parser_report_normal.h"
#include "dlt_698_parser_private.h"
#include "dlt_698_parser_widget.h"
/*请求 REPORT*/
int16_t dlt_698_parse_rep_ntf_normal_list(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.ntf_normal = (struct DLT_698_REP_NTF_NOR *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_REP_NTF_NOR));
    if (ins_ptr->frame.content.ntf_normal == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 获取到OAD个数
    uint8_t res_cnt = 0;
    int16_t ret = dlt_698_payld_read_u8(ins_ptr, &res_cnt);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    ins_ptr->frame.content.ntf_normal->normal_ptr = NULL;
    struct DLT_698_Result_Normal **node_father = &ins_ptr->frame.content.ntf_normal->normal_ptr;
    // 循环解析每一个数据块信息,上报的信息块与GET normal list的响应保持一致
    for (int i = 0; i < res_cnt; i++)
    {
        uint16_t next_index = ins_ptr->_mem.alloc_mempool_size;
        struct DLT_698_Result_Normal *node_ptr = (struct DLT_698_Result_Normal *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_Result_Normal));
        if (!node_ptr)
        {
            return DLT_698_ERR_EMPTY_PTR;
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
int16_t dlt_698_parse_rep_ntf_record_list(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.ntf_record = (struct DLT_698_REP_NTF_REC *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_REP_NTF_REC));
    if (ins_ptr->frame.content.ntf_record == NULL)
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
    ins_ptr->frame.content.ntf_record->record_ptr = NULL;
    struct DLT_698_RESULT_RECORD **node_father = &ins_ptr->frame.content.ntf_record->record_ptr;
    // 循环解析多个记录回复数据单元
    for (int i = 0; i < rec_cnt; i++)
    {
        uint16_t next_index = ins_ptr->_mem.alloc_mempool_size;
        struct DLT_698_RESULT_RECORD *node_ptr = (struct DLT_698_RESULT_RECORD *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_RESULT_RECORD));
        if (!node_ptr)
        {
            return DLT_698_ERR_OVER;
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

/*响应 REPORT*/
int16_t dlt_698_parse_rep_res_normal_list(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.res_nor_rec = (struct DLT_698_REP_RES_NOR *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_REP_RES_NOR));
    if (ins_ptr->frame.content.res_nor_rec == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 获取到OAD个数
    uint8_t oad_cnt = 0;
    int16_t ret = dlt_698_payld_read_u8(ins_ptr, &oad_cnt);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    ins_ptr->frame.content.res_nor_rec->oad_ptr = NULL;
    dlt_698_data_t **node_father = &ins_ptr->frame.content.res_nor_rec->oad_ptr;
    for (int i = 0; i < oad_cnt; i++)
    {
        uint16_t next_index = ins_ptr->_mem.alloc_mempool_size;
        // 向内存池申请一个struct DLT_698_GET_NOR_REQ_NODE结构
        dlt_698_data_t *node_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
        if (!node_ptr)
        {
            return DLT_698_ERR_OVER;
        }
        DLT_698_append_next(dlt_698_data_t, ins_ptr->_mem.start, node_father, next_index);
        ret = dlt_698_parse_oad(ins_ptr, node_ptr);
        if (ret != DLT_698_ERR_NONE)
        {
            return ret;
        }
    }
    return DLT_698_ERR_NONE;
}
int16_t dlt_698_parse_rep_res_record_list(dlt_698_parser *parser)
{
    // 上报记录响应与上报属性响应保持一致
    return dlt_698_parse_rep_res_normal_list(parser);
}

// /*上报透明传输 ReportNotificationTransData*/
// static int16_t dlt_698_parse_rep_ntf_trans_result(struct DLT_698_PRIVATE* ins_ptr,struct DLT_698_REP_NTF_TRANS_NODE* data_ptr)
// {
//     dlt_698_parse_octet_string(ins_ptr,&data_ptr->data);
//     return DLT_698_ERR_NONE;
// }
int16_t dlt_698_parse_rep_ntf_trans(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.ntf_trans = (struct DLT_698_REP_NTF_TRANS *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_REP_NTF_TRANS));
    if (ins_ptr->frame.content.ntf_trans == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 获取OAD
    int16_t ret = dlt_698_parse_oad(ins_ptr, &ins_ptr->frame.content.ntf_trans->oad);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    uint8_t cnt = 0;
    ret = dlt_698_payld_read_u8(ins_ptr, &cnt);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    ins_ptr->frame.content.ntf_trans->data_ptr = NULL;
    dlt_698_data_t **node_father = &ins_ptr->frame.content.ntf_trans->data_ptr;
    for (int i = 0; i < cnt; i++)
    {
        uint16_t next_index = ins_ptr->_mem.alloc_mempool_size;
        // 向内存池申请一个struct DLT_698_REP_NTF_TRANS_NODE 结构
        dlt_698_data_t *node_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
        if (!node_ptr)
        {
            return DLT_698_ERR_EMPTY_PTR;
        }
        DLT_698_append_next(dlt_698_data_t, ins_ptr->_mem.start, node_father, next_index);
        ret = dlt_698_parse_octet_string(ins_ptr, node_ptr);
        if (ret != DLT_698_ERR_NONE)
        {
            return ret;
        }
    }

    return DLT_698_ERR_NONE;
}
/*响应上报透明传输*/
int16_t dlt_698_parse_rep_res_trans(dlt_698_parser *parser)
{
    // 只解析到PIID
    return DLT_698_ERR_NONE;
}
