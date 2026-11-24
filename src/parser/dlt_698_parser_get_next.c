#include "dlt_698_parser_get_next.h"
#include "dlt_698_parser_private.h"
#include "dlt_698_parser_get_normal.h"
#include "dlt_698_parser_widget.h"
int16_t dlt_698_parse_get_req_next(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.req_next = (struct DLT_698_GET_NEXT_REQ *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_GET_NEXT_REQ));
    if (ins_ptr->frame.content.req_next == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 分帧号起始位置)
    uint16_t last_frame = (ins_ptr->_payld_ptr[ins_ptr->_payld_index] << 8) + ins_ptr->_payld_ptr[ins_ptr->_payld_index + 1];
    ins_ptr->frame.content.req_next->last_frame = last_frame;
    ins_ptr->_payld_index += 2;
    return DLT_698_ERR_NONE;
}
int16_t dlt_698_parse_get_res_next(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.res_next = (struct DLT_698_GET_NEXT_RES *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_GET_NEXT_RES));
    if (ins_ptr->frame.content.res_next == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 末帧标志
    ins_ptr->frame.content.res_next->is_end = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    // 分帧序号，占两个字节
    ins_ptr->frame.content.res_next->frame_num = (ins_ptr->_payld_ptr[ins_ptr->_payld_index] << 8) + ins_ptr->_payld_ptr[ins_ptr->_payld_index + 1];
    ins_ptr->_payld_index += 2;
    // 响应数据选择
    uint8_t data_choice = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    ins_ptr->frame.content.res_next->data_choice = data_choice;
    switch (data_choice)
    {
        case 0:    // 错误信息           [0]   DAR，
            ins_ptr->frame.content.res_next->next_data.dar = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
            break;
        case 1:    // 对象属性         [1]   SEQUENCE OF A-ResultNormal
        {
            int cnt = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
            ins_ptr->frame.content.res_next->next_data.normal_ptr = NULL;
            struct DLT_698_Result_Normal **node_father = &ins_ptr->frame.content.res_next->next_data.normal_ptr;
            for (int i = 0; i < cnt; i++)
            {
                uint16_t next_index = ins_ptr->_mem.alloc_mempool_size;
                struct DLT_698_Result_Normal *node_ptr = (struct DLT_698_Result_Normal *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_Result_Normal));
                if (node_ptr == NULL)
                {
                    return DLT_698_ERR_EMPTY_PTR;
                }
                DLT_698_append_next(struct DLT_698_Result_Normal, ins_ptr->_mem.start, node_father, next_index);
                // 解析数据信息
                dlt_698_parse_result_normal(ins_ptr, node_ptr);
            }
        }
        break;
        case 2:    // 记录型对象属性    [2]   SEQUENCE OF A-ResultRecord
        {
            int cnt = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
            ins_ptr->frame.content.res_next->next_data.record_ptr = NULL;
            struct DLT_698_RESULT_RECORD **node_father = &ins_ptr->frame.content.res_next->next_data.record_ptr;
            for (int i = 0; i < cnt; i++)
            {
                uint16_t next_index = ins_ptr->_mem.alloc_mempool_size;
                struct DLT_698_RESULT_RECORD *node_ptr = (struct DLT_698_RESULT_RECORD *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_RESULT_RECORD));
                if (node_ptr == NULL)
                {
                    return DLT_698_ERR_EMPTY_PTR;
                }
                DLT_698_append_next(struct DLT_698_RESULT_RECORD, ins_ptr->_mem.start, node_father, next_index);
                // 解析数据信息
                dlt_698_parse_get_res_record_result(ins_ptr, node_ptr);
            }
        }
        break;
        default:
            break;
    }
    return DLT_698_ERR_NONE;
}