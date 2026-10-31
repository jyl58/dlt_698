/**
 * @file dlt_698_parser_report.h
 * @date 2025-03-12
 * @brief 通知上报（REPORT-Notification）/响应上报（REPORT-Respone）报文解析接口
 * @details 通过该部分定义的接口可以解析report相关报文
 */

#ifndef DLT_698_PARSER_REPORT_H_
#define DLT_698_PARSER_REPORT_H_
#include "dlt_698_type.h"
#include "dlt_698_parser.h"
#include "dlt_698_parser_report_normal.h"
#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief 通知上报（REPORT-Notification）报文解析
     * @details 通过具体的报文类型调用相关解析接口
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_report_req(dlt_698_parser *parser);
    /**
     * @brief 响应上报（REPORT-Respone）报文解析
     * @details 通过具体的报文类型调用相关解析接口
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_report_res(dlt_698_parser *parser);
    /**
     * @brief 通知上报若干个对象属性（ReportNotificationList）
     * @details 解析88 01 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_rep_ntf_normal_list(dlt_698_parser *parser);
    /**
     * @brief 通知上报若干个记录型对象属性（ReportNotificationRecordList）
     * @details 解析88 02 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_rep_ntf_record_list(dlt_698_parser *parser);
    /**
     * @brief 通知上报透明数据（ReportNotificationTransData）
     * @details 解析88 03 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_rep_ntf_trans(dlt_698_parser *parser);
    /**
     * @brief 响应上报若干个对象属性（ReportResponseList）
     * @details 解析08 01 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_rep_res_normal_list(dlt_698_parser *parser);
    /**
     * @brief 响应上报若干个记录型对象属性（ReportResponseRecordList）
     * @details 解析08 02 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_rep_res_record_list(dlt_698_parser *parser);
    /**
     * @brief 响应上报透明数据（ReportResponseTransData）
     * @details 解析08 03 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_rep_res_trans(dlt_698_parser *parser);

#ifdef __cplusplus
}
#endif
#endif