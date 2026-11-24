/**
 * @file dlt_698_parser_report_normal.h
 * @date 2025-03-12
 * @brief 上报数据通知和响应
 * @details 定义数据类型
 */

#ifndef DLT_698_PARSER_REPORT_NORMAL_H_
#define DLT_698_PARSER_REPORT_NORMAL_H_
#include "dlt_698_type.h"
#include "dlt_698_data.h"
#include "dlt_698_parser_get_normal.h"
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)


    /**
     * @brief 通知上报若干个对象属性
     */
    struct DLT_698_REP_NTF_NOR
    {
        struct DLT_698_Result_Normal *normal_ptr;    ///< SEQUENCE OF A-ResultNormal
    };
    /**
     * @brief 通知上报若干个记录型对象属性
     */
    struct DLT_698_REP_NTF_REC
    {
        struct DLT_698_RESULT_RECORD *record_ptr;    ///< SEQUENCE OF A-ResultRecord
    };
    /**
     * @brief 响应上报若干个对象属性 ReportResponseList
     *        响应上报若干个记录型对象属性 ReportResponseRecordList
     */
    struct DLT_698_REP_RES_NOR
    {
        dlt_698_data_t *oad_ptr;    ///< SEQUENCE OF OAD
    };

    /**
     * @brief 通知上报透明数据 ReportNotificationTransData
     */
    struct DLT_698_REP_NTF_TRANS
    {
        dlt_698_data_t oad;          ///< OAD
        dlt_698_data_t *data_ptr;    ///< SEQUENCE OF octet-string
    };

#pragma pack()
#ifdef __cplusplus
}
#endif

#endif