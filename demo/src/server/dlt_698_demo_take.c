/**
 * @file dlt_698_demo_take.c
 * @date 2026-11-24
 * @brief DL/T 698 字段提取示例
 * @details 演示解析完成后如何使用 dlt_698_take_* / dlt_698_get_* 系列接口,
 *          把帧头字段和 APDU 内各数据字段的值逐个提取出来。
 *          与 dlt_698_utl_print_* 的"整体打印"不同, 本文件演示的是
 *          "把具体值取到变量里"的用法, 便于应用程序直接使用。
 */
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "dlt_698_demo_take.h"
#include "dlt_698_utl_take.h"
#include "dlt_698_utl_data.h"
#include "dlt_698_utl_tools.h"
#include "dlt_698_data.h"
#include "dlt_698_parser_get_normal.h"
#include "dlt_698_parser_set_normal.h"

/**
 * @brief 按数据类型逐个取值并打印
 * @param parser  解析器
 * @param node    解析数据节点
 * @param tag     打印前缀
 */
static void demo_print_data_value(dlt_698_parser *parser, dlt_698_data_t *node, const char *tag)
{
    if ((NULL == parser) || (NULL == node))
    {
        return;
    }
    printf("%s[type=%d len=%u] ", tag, node->type, node->len);
    switch (node->type)
    {
        case DLT_698_TYPE_OOP_BOOL:
        {
            oop_bool val = 0;
            if (dlt_698_get_bool(parser, node, &val))
            {
                printf("bool = %u\n", val);
            }
            break;
        }
        case DLT_698_TYPE_OOP_DOUBLE_LONG:
        {
            oop_double_long val = 0;
            if (dlt_698_get_double_long(parser, node, &val))
            {
                printf("double-long = %d\n", val);
            }
            break;
        }
        case DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED:
        {
            oop_double_long_unsigned val = 0;
            if (dlt_698_get_double_long_unsigned(parser, node, &val))
            {
                printf("double-long-unsigned = %u\n", val);
            }
            break;
        }
        case DLT_698_TYPE_OOP_INTEGER:
        {
            oop_integer val = 0;
            if (dlt_698_get_integer(parser, node, &val))
            {
                printf("integer = %d\n", val);
            }
            break;
        }
        case DLT_698_TYPE_OOP_LONG:
        {
            oop_long val = 0;
            if (dlt_698_get_long(parser, node, &val))
            {
                printf("long = %d\n", val);
            }
            break;
        }
        case DLT_698_TYPE_OOP_UNSIGNED:
        {
            oop_unsigned val = 0;
            if (dlt_698_get_unsigned(parser, node, &val))
            {
                printf("unsigned = %u\n", val);
            }
            break;
        }
        case DLT_698_TYPE_OOP_LONG_UNSIGNED:
        {
            oop_long_unsigned val = 0;
            if (dlt_698_get_long_unsigned(parser, node, &val))
            {
                printf("long-unsigned = %u\n", val);
            }
            break;
        }
        case DLT_698_TYPE_OOP_LONG64:
        {
            oop_long64 val = 0;
            if (dlt_698_get_long64(parser, node, &val))
            {
                printf("long64 = %lld\n", (long long)val);
            }
            break;
        }
        case DLT_698_TYPE_OOP_LONG64_UNSIGNED:
        {
            oop_long64_unsigned val = 0;
            if (dlt_698_get_long64_unsigned(parser, node, &val))
            {
                printf("long64-unsigned = %llu\n", (unsigned long long)val);
            }
            break;
        }
        case DLT_698_TYPE_OOP_ENUM:
        {
            oop_enum val = 0;
            if (dlt_698_get_enum(parser, node, &val))
            {
                printf("enum = %u\n", val);
            }
            break;
        }
        case DLT_698_TYPE_OOP_FLOAT32:
        {
            oop_float32 val = 0;
            if (dlt_698_get_float32(parser, node, &val))
            {
                printf("float32 = %f\n", val);
            }
            break;
        }
        case DLT_698_TYPE_OOP_FLOAT64:
        {
            oop_float64 val = 0;
            if (dlt_698_get_float64(parser, node, &val))
            {
                printf("float64 = %f\n", val);
            }
            break;
        }
        case DLT_698_TYPE_OOP_OCTET_STRING:
        {
            uint8_t buf[64] = {0};
            uint16_t real = 0;
            if (dlt_698_get_octet_string(parser, node, buf, sizeof(buf), &real))
            {
                printf("octet-string[%u] =", real);
                for (uint16_t i = 0; i < real; i++)
                {
                    printf(" %02X", buf[i]);
                }
                printf("\n");
            }
            break;
        }
        case DLT_698_TYPE_OOP_VISIBLE_STRING:
        {
            char buf[64] = {0};
            uint16_t real = 0;
            if (dlt_698_get_visible_string(parser, node, (oop_visible_string *)buf, sizeof(buf), &real))
            {
                printf("visible-string[%u] = %s\n", real, buf);
            }
            break;
        }
        case DLT_698_TYPE_OOP_UTF8_STRING:
        {
            char buf[64] = {0};
            uint16_t real = 0;
            if (dlt_698_get_utf8_string(parser, node, (oop_utf8_string *)buf, sizeof(buf), &real))
            {
                printf("utf8-string[%u] = %s\n", real, buf);
            }
            break;
        }
        case DLT_698_TYPE_OOP_OI:
        {
            oop_oi val = 0;
            if (dlt_698_get_oi(parser, node, &val))
            {
                printf("oi = 0x%04X(%u)\n", val, val);
            }
            break;
        }
        case DLT_698_TYPE_OOP_OAD:
        {
            oop_oad val;
            memset(&val, 0, sizeof(val));
            if (dlt_698_get_oad(parser, node, &val))
            {
                printf("oad = oi:0x%04X att_tag:0x%02X att_index:0x%02X\n",
                       val.st.oi, val.st.att_tag, val.st.att_index);
            }
            break;
        }
        case DLT_698_TYPE_OOP_TI:
        {
            oop_ti val;
            memset(&val, 0, sizeof(val));
            if (dlt_698_get_ti(parser, node, &val))
            {
                printf("ti = unit:%u interval:%u\n", val.unit, val.interval);
            }
            break;
        }
        default:
        {
            /* 其他类型(含复合类型): 提取原始字节 */
            uint8_t buf[64] = {0};
            if ((node->len > 0) && (node->len <= sizeof(buf)) &&
                (dlt_698_get_data_arry(parser, node, buf, sizeof(buf)) == DLT_698_ERR_NONE))
            {
                printf("raw[%u] =", node->len);
                for (uint16_t i = 0; i < node->len; i++)
                {
                    printf(" %02X", buf[i]);
                }
                printf("\n");
            }
            break;
        }
    }
}

void demo_take_frame_fields(dlt_698_parser *parser)
{
    if ((NULL == parser) || (NULL == parser->_ins))
    {
        return;
    }
    printf("\n========== [take] frame fields ==========\n");
    printf("[take] frame type = 0x%02X\n", dlt_698_take_type(parser));
    printf("[take] frame method = %d\n", dlt_698_take_method(parser));

    uint8_t code = 0;
    if (dlt_698_take_code(parser, &code) == DLT_698_ERR_NONE)
    {
        printf("[take] ctrl code = 0x%02X (DIR=%u PRM=%u FUN=%u)\n",
               code, (code & 0x80) >> 7, (code & 0x40) >> 6, (code & 0x0F));
    }

    dlt_698_addr_t addr;
    memset(&addr, 0, sizeof(addr));
    if (dlt_698_take_addr(parser, &addr) == DLT_698_ERR_NONE)
    {
        char sa[2 * sizeof(addr.sa_addr) + 1] = {0};
        dlt_698_take_sa(&addr, sa, sizeof(sa));
        printf("[take] server addr SA = %s, client addr CA = %u\n", sa, addr.ca);
    }

    uint8_t piid = 0;
    if (dlt_698_take_piid(parser, &piid) == DLT_698_ERR_NONE)
    {
        printf("[take] PIID = %u\n", piid);
    }

    uint8_t sec_type = 0xFF;
    if (dlt_698_take_sec_type(parser, &sec_type) == DLT_698_ERR_NONE)
    {
        printf("[take] sec type = %u (0=common)\n", sec_type);
    }

    dlt_698_data_t *tag = NULL;
    dlt_698_take_time_tag(parser, &tag);
    if (NULL != tag)
    {
        printf("[take] time tag present:\n");
        /* TimeTag节点是structure, 第一个子节点为date_time_s */
        dlt_698_data_t *dts_node = (dlt_698_data_t *)dlt_698_get_child_ptr(parser, tag->child_index);
        if (NULL != dts_node)
        {
            oop_date_time_s dts;
            memset(&dts, 0, sizeof(dts));
            if (dlt_698_get_date_time_s(parser, dts_node, &dts))
            {
                printf("[take]   TimeTag = %04u-%02u-%02u %02u:%02u:%02u\n",
                       dts.year, dts.month, dts.day, dts.hour, dts.minute, dts.second);
            }
        }
    }
    else
    {
        printf("[take] time tag: none\n");
    }

    dlt_698_follow_report_t *follow = NULL;
    dlt_698_take_follow_report(parser, &follow);
    printf("[take] follow report: %s\n", (NULL != follow) ? "yes" : "none");

    uint8_t apdu[512] = {0};
    int16_t apdu_len = dlt_698_take_apdu(parser, apdu);
    if ((apdu_len >= 0) && (apdu_len <= (int16_t)sizeof(apdu)))
    {
        printf("[take] APDU(%d bytes):", apdu_len);
        for (int16_t i = 0; i < apdu_len; i++)
        {
            printf(" %02X", apdu[i]);
        }
        printf("\n");
    }
}

void demo_take_apdu_fields(dlt_698_parser *parser)
{
    if ((NULL == parser) || (NULL == parser->_ins))
    {
        return;
    }
    int16_t type = dlt_698_take_type(parser);
    int16_t method = dlt_698_take_method(parser);
    printf("\n========== [get] APDU fields (type=0x%02X method=%d) ==========\n", type, method);

    switch (type)
    {
        case DLT_698_FRAME_TYPE_GET_REQ: /* GET请求 */
        {
            if ((DLT_698_GET_METHOD_NOR != method) && (DLT_698_GET_METHOD_NOR_LIST != method))
            {
                break;
            }
            struct DLT_698_GET_NOR_REQ *head = NULL;
            if (dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_GET_REQ, method, (void **)&head) != DLT_698_ERR_NONE ||
                (NULL == head))
            {
                break;
            }
            printf("[get] OAD count = %d\n",
                   dlt_698_get_common_sibling_cnt(parser, head->oad_ptr, offsetof(dlt_698_data_t, next_index)));
            dlt_698_data_t *oad = head->oad_ptr;
            int i = 0;
            while (NULL != oad)
            {
                oop_oad val;
                memset(&val, 0, sizeof(val));
                if (dlt_698_get_oad(parser, oad, &val))
                {
                    printf("[get]   OAD#%d = oi:0x%04X att_tag:0x%02X att_index:0x%02X\n",
                           i++, val.st.oi, val.st.att_tag, val.st.att_index);
                }
                oad = (0 != oad->next_index) ? (dlt_698_data_t *)dlt_698_get_next_ptr(parser, oad->next_index) : NULL;
            }
        }
        break;

        case DLT_698_FRAME_TYPE_GET_RES: /* GET响应 */
        {
            if ((DLT_698_GET_METHOD_NOR != method) && (DLT_698_GET_METHOD_NOR_LIST != method))
            {
                break;
            }
            struct DLT_698_GET_NOR_RES *head = NULL;
            if (dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_GET_RES, method, (void **)&head) != DLT_698_ERR_NONE ||
                (NULL == head))
            {
                break;
            }
            printf("[get] result normal count = %d\n",
                   dlt_698_get_common_sibling_cnt(parser, head->normal_ptr, offsetof(struct DLT_698_Result_Normal, next_index)));
            struct DLT_698_Result_Normal *cur = head->normal_ptr;
            int i = 0;
            while (NULL != cur)
            {
                oop_oad val;
                memset(&val, 0, sizeof(val));
                if (dlt_698_get_oad(parser, &cur->oad, &val))
                {
                    printf("[get]   Result#%d OAD = oi:0x%04X att_tag:0x%02X att_index:0x%02X\n",
                           i, val.st.oi, val.st.att_tag, val.st.att_index);
                }
                printf("[get]   Result#%d DAR = %u (0=success)\n", i, cur->get_result.dar);
                demo_print_data_value(parser, &cur->get_result.result_data, "[get]     value");
                cur = (0 != cur->next_index) ? (struct DLT_698_Result_Normal *)dlt_698_get_next_ptr(parser, cur->next_index) : NULL;
                i++;
            }
        }
        break;

        case DLT_698_FRAME_TYPE_SET_REQ: /* SET请求 */
        {
            if ((DLT_698_SET_METHOD_NOR != method) && (DLT_698_SET_METHOD_NOR_LIST != method))
            {
                break;
            }
            struct DLT_698_SET_NOR_REQ *head = NULL;
            if (dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_SET_REQ, method, (void **)&head) != DLT_698_ERR_NONE ||
                (NULL == head))
            {
                break;
            }
            struct DLT_698_SET_ATTRIBUTE *cur = head->set_ptr;
            int i = 0;
            while (NULL != cur)
            {
                oop_oad val;
                memset(&val, 0, sizeof(val));
                if (dlt_698_get_oad(parser, &cur->oad, &val))
                {
                    printf("[get]   SET#%d OAD = oi:0x%04X att_tag:0x%02X att_index:0x%02X\n",
                           i, val.st.oi, val.st.att_tag, val.st.att_index);
                }
                demo_print_data_value(parser, &cur->data, "[get]     DATA");
                cur = (0 != cur->next_index) ? (struct DLT_698_SET_ATTRIBUTE *)dlt_698_get_next_ptr(parser, cur->next_index) : NULL;
                i++;
            }
        }
        break;

        case DLT_698_FRAME_TYPE_SET_RES: /* SET响应 */
        {
            if ((DLT_698_SET_METHOD_NOR != method) && (DLT_698_SET_METHOD_NOR_LIST != method))
            {
                break;
            }
            struct DLT_698_SET_NOR_RES *head = NULL;
            if (dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_SET_RES, method, (void **)&head) != DLT_698_ERR_NONE ||
                (NULL == head))
            {
                break;
            }
            struct DLT_698_SET_RESULT *cur = head->result_ptr;
            int i = 0;
            while (NULL != cur)
            {
                oop_oad val;
                memset(&val, 0, sizeof(val));
                if (dlt_698_get_oad(parser, &cur->oad, &val))
                {
                    printf("[get]   SET-RES#%d OAD = oi:0x%04X att_tag:0x%02X att_index:0x%02X\n",
                           i, val.st.oi, val.st.att_tag, val.st.att_index);
                }
                printf("[get]   SET-RES#%d DAR = %u (0=success)\n", i, cur->DAR);
                cur = (0 != cur->next_index) ? (struct DLT_698_SET_RESULT *)dlt_698_get_next_ptr(parser, cur->next_index) : NULL;
                i++;
            }
        }
        break;

        default:
            printf("[get] frame type not handled in demo (only GET/SET normal/list).\n");
            break;
    }
}
