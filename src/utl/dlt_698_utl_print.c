#include "dlt_698_utl_print.h"
#include "dlt_698_parser_private.h"
#include "dlt_type.h"
#include "dlt_698_utl_tools.h"
#include "dlt_698_data.h"
#include "dlt_698_utl_take.h"
int16_t dlt_698_utl_print_head(dlt_698_parser *parser)
{
    /*检查空指针*/
    if (NULL == parser)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    DLT_printf("698 head.head=%02X\n", ins_ptr->_ptl.head);
    DLT_printf("698 head.len=%d\n", ins_ptr->_ptl.len);
    DLT_printf("698 head.sa.ctl=%02X\n", ins_ptr->_ptl.code);
    DLT_printf("698 head.sa.feature=%02X\n", ins_ptr->_ptl.addr.sa_feature.val);
    uint8_t sa_len = ins_ptr->_ptl.addr.sa_feature.st.sa_len + 1;
    if (ins_ptr->_ptl.addr.ext > 1)    // 包含拓展逻辑地址
    {
        sa_len -= 1;
    }
    DLT_printf("698 head.sa.addr=");
    for (int i = sa_len - 1; i >= 0; i--)
    {
        DLT_printf("%02x", ins_ptr->_ptl.addr.sa_addr[i]);
    }
    DLT_printf("\n");
    DLT_printf("698 head.sa.ext=%d\n", ins_ptr->_ptl.addr.ext);
    DLT_printf("698 head.sa.ca=%d\n", ins_ptr->_ptl.addr.ca);
    DLT_printf("698 head.check=");
    dlt_698_utl_print_arry((uint8_t *)&ins_ptr->_ptl.head_ck, 2);
    // DLT_printf("PAR head.check=");
    // dlt_698_utl_print_arry((uint8_t*)&ins_ptr->_parse_cs.head_cs,2);

    DLT_printf("698 frame.check=");
    dlt_698_utl_print_arry((uint8_t *)&ins_ptr->_ptl.frame_ck, 2);

    // DLT_printf("PAR frame.check=",(ins_ptr->_parse_cs._fcs^0xffff));
    return DLT_698_ERR_NONE;
}
int16_t dlt_698_utl_print_APDU(dlt_698_parser *parser)
{
    /*检查空指针*/
    if ((NULL == parser) || (NULL == parser->_ins))
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    DLT_printf("698 frame.APDU=");
    for (int i = 0; i < ins_ptr->_payld_len; i++)
    {
        DLT_printf("%02x", ins_ptr->_payld_ptr[i]);
    }
    DLT_printf("\n");
    return DLT_698_ERR_NONE;
}

/*打印mempool使用情况*/
int16_t dlt_698_utl_print_mempool_status(dlt_698_parser *parser)
{
    /*检查空指针*/
    if ((NULL == parser) || (NULL == parser->_ins))
    {
        return DLT_698_ERR_EMPTY_PTR;
    }

    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    DLT_printf("APDU.LEN=%d\n", ins_ptr->_payld_len);
    DLT_printf("MEM_POOL.SIZE=%d\n", dlt_698_mempool_total_size(&ins_ptr->_mem));
    DLT_printf("MEM_POOL.USED=%d\n", dlt_698_mempool_alloc_size(&ins_ptr->_mem));
    DLT_printf("MEM_POOL.REMAIN=%d\n", dlt_698_mempool_remain_size(&ins_ptr->_mem));

    return DLT_698_ERR_NONE;
}
/**打印数组 */
int16_t dlt_698_utl_print_arry(uint8_t *src, uint16_t len)
{
    if (NULL == src)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    if (0 == len)
    {
        DLT_printf("NULL\n");
        return DLT_698_ERR_NONE;
    }
    for (int i = 0; i < len; i++)
    {
        DLT_printf("%02X", src[i]);
    }
    DLT_printf("\n");
    return DLT_698_ERR_NONE;
}

int16_t dlt_698_utl_print_data(dlt_698_parser *parser, dlt_698_data_t *data_ptr)
{
    if (!data_ptr)
    {
        DLT_printf(" NULL\n");
    }
    uint8_t temp_data[1024] = {0};
    if (NULL != data_ptr)
    {
        DLT_printf("Data.type=%d\n", data_ptr->type);
        DLT_printf("Data.content=");
        int16_t res = dlt_698_get_data_arry(parser, data_ptr, temp_data, sizeof(temp_data));
        if (res != DLT_698_ERR_NONE)
        {
            DLT_printf("read data arry error");
            return res;
        }
        dlt_698_utl_print_arry(temp_data, data_ptr->len);

        dlt_698_data_t *child_ptr = dlt_698_get_child_ptr(parser, data_ptr->child_index);
        if (child_ptr)
        {
            dlt_698_utl_print_data(parser, child_ptr);
        }

        dlt_698_data_t *next_ptr = dlt_698_get_next_ptr(parser, data_ptr->next_index);
        if (next_ptr)
        {
            dlt_698_utl_print_data(parser, next_ptr);
        }
    }
    return DLT_698_ERR_NONE;
}
int16_t dlt_698_utl_print_node_data(dlt_698_parser *parser, dlt_698_data_t *data_ptr)
{
    if (!data_ptr)
    {
        DLT_printf(" NULL\n");
    }
    uint8_t temp_data[1024] = {0};
    if (NULL != data_ptr)
    {
        DLT_printf("Data.type=%d\n", data_ptr->type);
        DLT_printf("Data.content=");
        int16_t res = dlt_698_get_data_arry(parser, data_ptr, temp_data, sizeof(temp_data));
        if (res != DLT_698_ERR_NONE)
        {
            DLT_printf("read data arry error");
            return res;
        }
        dlt_698_utl_print_arry(temp_data, data_ptr->len);
    }
    return DLT_698_ERR_NONE;
}
int16_t dlt_698_utl_print_get_result(dlt_698_parser *parser, struct DLT_698_Get_Result *result_ptr)
{
    DLT_printf("read dar=%d\n", result_ptr->dar);
    dlt_698_utl_print_data(parser, &result_ptr->result_data);
    return DLT_698_ERR_NONE;
}

int16_t dlt_698_utl_print_result_normal(dlt_698_parser *parser, struct DLT_698_Result_Normal *normal_ptr)
{
    while (normal_ptr)
    {
        dlt_698_utl_print_data(parser, &normal_ptr->oad);
        dlt_698_utl_print_get_result(parser, &normal_ptr->get_result);
        normal_ptr = dlt_698_get_next_ptr(parser, normal_ptr->next_index);
    }
    return DLT_698_ERR_NONE;
}
int16_t dlt_698_utl_print_result_record(dlt_698_parser *parser, struct DLT_698_RESULT_RECORD *record_ptr)
{
    while (record_ptr)
    {
        // OAD
        DLT_printf("OAD=");
        dlt_698_utl_print_data(parser, &record_ptr->oad);
        // RCSD
        DLT_printf("RCSD=");
        dlt_698_utl_print_data(parser, &record_ptr->rcsd);
        DLT_printf("dar=%d\n", record_ptr->record.dar);
        struct DLT_698_GET_RECORD_ROW *row_ptr = record_ptr->record.row_ptr;
        while (row_ptr)
        {
            // data
            DLT_printf("Data=");
            dlt_698_utl_print_data(parser, row_ptr->data);
            row_ptr = dlt_698_get_next_ptr(parser, row_ptr->next_index);
        }
        record_ptr = dlt_698_get_next_ptr(parser, record_ptr->next_index);
    }
    return DLT_698_ERR_NONE;
}

int16_t dlt_698_utl_print_time_tag(dlt_698_parser *parser)
{
    DLT_printf("TimeTag ");
    dlt_698_data_t *time_tag = NULL;
    dlt_698_take_time_tag(parser, &time_tag);
    dlt_698_utl_print_data(parser, time_tag);
    return DLT_698_ERR_NONE;
}

int16_t dlt_698_utl_print_follow_report(dlt_698_parser *parser)
{
    DLT_printf("follow report=");
    dlt_698_follow_report_t *follow_report = NULL;
    dlt_698_take_follow_report(parser, &follow_report);
    if (NULL == follow_report)
    {
        DLT_printf("NULL\n");
        return DLT_698_ERR_NONE;
    }
    DLT_printf("follow report type=%d\n", follow_report->follow_type);
    if (follow_report->follow_type == 1)
    {
        DLT_printf("follow report time=");
        dlt_698_utl_print_result_normal(parser, follow_report->data.normal_ptr);
    }
    else if (follow_report->follow_type == 2)
    {
        DLT_printf("Result Record:");
        dlt_698_utl_print_result_record(parser, follow_report->data.result_ptr);
    }
    else
    {
        DLT_printf("unkown follow report type err\n");
    }

    return DLT_698_ERR_NONE;
}
