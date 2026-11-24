#ifndef DLT_698_PARSER_WIDGET_H_
#define DLT_698_PARSER_WIDGET_H_
#include "dlt_698_type.h"
#include "dlt_698_parser_private.h"
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

// 获取node最有一个节点的next地址
#define DLT_698_append_next(type, buf, list, index)                                                                                                                                                    \
    {                                                                                                                                                                                                  \
        type *node = (type *)(buf + index);                                                                                                                                                            \
        if (*list == NULL)                                                                                                                                                                             \
        {                                                                                                                                                                                              \
            *list = node;                                                                                                                                                                              \
        }                                                                                                                                                                                              \
        else                                                                                                                                                                                           \
        {                                                                                                                                                                                              \
            type *node = *list;                                                                                                                                                                        \
            while (node->next_index != 0)                                                                                                                                                              \
            {                                                                                                                                                                                          \
                node = (type *)(buf + node->next_index);                                                                                                                                               \
            }                                                                                                                                                                                          \
            node->next_index = index;                                                                                                                                                                  \
        }                                                                                                                                                                                              \
    }

    /*根据预先定义的数据类型表，获取数据长度信息*/
    int16_t dlt_698_parse_data(struct DLT_698_PRIVATE *ins_ptr, uint8_t data_type, dlt_698_data_t *data_ptr);
    /*解析数组*/
    int16_t dlt_698_parse_null(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /*解析数组*/
    int16_t dlt_698_parse_arry(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /*解析结构体*/
    int16_t dlt_698_parse_struct(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析BOOL数据结构 */
    int16_t dlt_698_parse_bool(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析Bit string数据结构 */
    int16_t dlt_698_parse_bit_string(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析double-long数据结构 */
    int16_t dlt_698_parse_double_long(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析double-long-unsigned数据结构 */
    int16_t dlt_698_parse_double_long_unsigned(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析octet-string数据结构 */
    int16_t dlt_698_parse_octet_string(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析ascii数据结构 */
    int16_t dlt_698_parse_visible_string(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析UTF-8数据结构 */
    int16_t dlt_698_parse_octet_utf8_string(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析integer数据结构 */
    int16_t dlt_698_parse_integer(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析long数据结构 */
    int16_t dlt_698_parse_long(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析unsigned数据结构 */
    int16_t dlt_698_parse_unsigned(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析long-unsigned数据结构 */
    int16_t dlt_698_parse_long_unsigned(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析long64数据结构 */
    int16_t dlt_698_parse_long64(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析long64-unsigned数据结构 */
    int16_t dlt_698_parse_long64_unsigned(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析ENUM数据结构 */
    int16_t dlt_698_parse_enum(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析float32数据结构 */
    int16_t dlt_698_parse_float32(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析float64数据结构 */
    int16_t dlt_698_parse_float64(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析date_time数据结构 */
    int16_t dlt_698_parse_date_time(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析date数据结构 */
    int16_t dlt_698_parse_date(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析time数据结构 */
    int16_t dlt_698_parse_time(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析date_time_s数据结构 */
    int16_t dlt_698_parse_date_time_s(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析OI数据结构 */
    int16_t dlt_698_parse_oi(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析OAD数据结构 */
    int16_t dlt_698_parse_oad(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析ROAD数据结构 */
    int16_t dlt_698_parse_road(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析OMD数据结构 */
    int16_t dlt_698_parse_omd(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析ti数据结构 */
    int16_t dlt_698_parse_ti(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析TSA数据结构 */
    int16_t dlt_698_parse_tsa(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析MAC数据结构 */
    int16_t dlt_698_parse_mac(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析RN数据结构 */
    int16_t dlt_698_parse_rn(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析REGION数据结构 */
    int16_t dlt_698_parse_region(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析Scaler_Unit数据结构 */
    int16_t dlt_698_parse_scaler_unit(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析RSD数据结构 */
    int16_t dlt_698_parse_rsd(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析CSD数据结构 */
    int16_t dlt_698_parse_csd(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析MS数据结构 */
    int16_t dlt_698_parse_ms(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析SID数据结构 */
    int16_t dlt_698_parse_sid(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析SID_MAC数据结构 */
    int16_t dlt_698_parse_sid_mac(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析COMDCB数据结构 */
    int16_t dlt_698_parse_comdcb(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析RCSD数据结构 */
    int16_t dlt_698_parse_rcsd(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);

    /**解析可变长度 */
    int16_t dlt_698_parse_axdr_len(const uint8_t *pData, uint16_t remain, uint16_t *pFieldLen, uint16_t *pContentLen);
    /**解析DR数据结构 */
    int16_t dlt_698_parse_dr(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr);
    /**解析时间标签域TimeTag数据结构 */
    int16_t dlt_698_parse_TimeTag(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t **tag_ptr);
    /**解析跟随上报域TimeTag数据结构 */
    int16_t dlt_698_parse_FollowReportTag(struct DLT_698_PRIVATE *ins_ptr, dlt_698_follow_report_t **follow_ptr);
    /**解析ResultNormal数据结构 */
    int16_t dlt_698_parse_result_normal(struct DLT_698_PRIVATE *ins_ptr, struct DLT_698_Result_Normal *result_normal);
    /**解析Get-Result数据结构 */
    int16_t dlt_698_parse_get_result(struct DLT_698_PRIVATE *ins_ptr, struct DLT_698_Get_Result *get_result);
    /*ResultRecord 响应解析*/
    int16_t dlt_698_parse_get_res_record_result(struct DLT_698_PRIVATE *ins_ptr, struct DLT_698_RESULT_RECORD *data_ptr);
    /*解析RSD中选择方法*/
    int16_t dlt_698_parse_rsd_sel0(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *rsd_ptr);
    int16_t dlt_698_parse_rsd_sel1(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *rsd_ptr);
    int16_t dlt_698_parse_rsd_sel2(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *rsd_ptr);
    int16_t dlt_698_parse_rsd_sel3(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *rsd_ptr);
    int16_t dlt_698_parse_rsd_sel4(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *rsd_ptr);
    int16_t dlt_698_parse_rsd_sel5(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *rsd_ptr);
    int16_t dlt_698_parse_rsd_sel6(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *rsd_ptr);
    int16_t dlt_698_parse_rsd_sel7(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *rsd_ptr);
    int16_t dlt_698_parse_rsd_sel8(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *rsd_ptr);
    int16_t dlt_698_parse_rsd_sel9(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *rsd_ptr);
    int16_t dlt_698_parse_rsd_sel10(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *rsd_ptr);

#pragma pack()
#ifdef __cplusplus
}
#endif
#endif