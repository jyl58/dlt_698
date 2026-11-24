/**
 * @file dlt_698_parser_get_record.h
 * @date 2025-03-12
 * @brief 请求和响应读取读取一个记录型对象属性
 * @details 定义数据类型
 */
#ifndef DLT_698_PARSER_GET_RECORD_H_
#define DLT_698_PARSER_GET_RECORD_H_
#include "dlt_698_parser.h"
#include "dlt_698_type.h"
#include "dlt_698_data.h"
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

    /**
     * @brief  记录型对象属性
     */
    struct DLT_698_GET_RECORD
    {
        dlt_698_data_t oad;     ///< 对象属性描述符 OAD
        dlt_698_data_t rsd;     ///< 记录行选择描述符 RSD
        dlt_698_data_t rcsd;    ///< 记录列选择描述符 RCSD
        uint16_t next_index;         ///< 兄弟节点索引下标，叶子节点为0
    };
    /**
     * @brief  记录行数据--第1列…第N列的数据
     */
    struct DLT_698_GET_RECORD_ROW
    {
        dlt_698_data_t *data;    ///< 记录列数据
        uint16_t next_index;          ///< 兄弟节点索引下标，叶子节点为0
    };
    /**
     * @brief 记录型对象响应数据
     */
    struct DLT_698_GET_RECORD_DATA
    {
        uint8_t dar;                                    ///< 错误信息
        struct DLT_698_GET_RECORD_ROW *row_ptr;    ///< 记录行数据
    };
    /**
     * @brief 一个记录型对象属性及结果 A-ResultRecord
     */
    struct DLT_698_RESULT_RECORD
    {
        dlt_698_data_t oad;                       ///< 记录型对象属性描述符OAD
        dlt_698_data_t rcsd;                      ///< 记录的N列属性描述符RCSD
        struct DLT_698_GET_RECORD_DATA record;    ///< 响应数据
        int next_index;                           ///< 兄弟节点索引下标，叶子节点为0
    };

    /**
     * @brief 一个或若干个记录型对象属性
     * @note 用于GetRequestRecord(05 03)/GetRequestRecordList(05 04)数据解析
     */
    struct DLT_698_GET_REC_REQ
    {
        struct DLT_698_GET_RECORD *rec_ptr;    ///< 记录型对象属性指针
    };
    /**
     * @brief 一个或若干个记录型对象属性及结果
     * @note 用于GetResponseRecord(85 03)/GetRequestRecordList(85 04)数据解析
     */
    struct DLT_698_GET_REC_RES
    {
        struct DLT_698_RESULT_RECORD *rec_ptr;    ///< 记录型对象属性及结果指针
    };


#pragma pack()
#ifdef __cplusplus
}
#endif
#endif