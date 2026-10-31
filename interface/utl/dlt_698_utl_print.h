/**
 * @file dlt_698_utl_print.h
 * @date 2025-03-12
 * @brief 打印相关函数
 * @details 常用函数定义
 */
#ifndef DLT_698_UTL_PRINT_H_
#define DLT_698_UTL_PRINT_H_
#include "dlt_698_parser.h"
#include "dlt_698_data.h"
#include "dlt_698_parser_get_record.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief 打印698解析器解析到的帧头信息
     * @details 打印帧头
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_utl_print_head(dlt_698_parser *parser);
    /**
     * @brief 打印APDU数据
     * @details 打印APDU数据
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_utl_print_APDU(dlt_698_parser *parser);
    /**
     * @brief 打印内存池使用情况
     * @details 打印内存池使用情况
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_utl_print_mempool_status(dlt_698_parser *parser);
    /**
     * @brief 打印数组
     * @details  打印数组
     * @param src 数据指针
     * @param len 数据长度
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_utl_print_arry(uint8_t *src, uint16_t len);
    /**
     * @brief 递归打印数据-先子节点后兄弟节点
     * @details  打印数据
     * @param parser 解析器
     * @param data_ptr 数据解析信息
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_utl_print_data(dlt_698_parser *parser, dlt_698_data_t *data_ptr);
    /**
     * @brief 只打印当前节点数据（不递归）
     * @details打印数据
     * @param parser 解析器
     * @param data_ptr 数据解析信息
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_utl_print_node_data(dlt_698_parser *parser, dlt_698_data_t *data_ptr);
    /**
     * @brief 打印读取结果信息
     * @details  打印数据
     * @param parser 解析器
     * @param result_ptr 读取结果
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_utl_print_get_result(dlt_698_parser *parser, struct DLT_698_Get_Result *result_ptr);
    /**
     * @brief 递归打印对象属性及结果
     * @details  打印数据
     * @param parser 解析器
     * @param normal_ptr 对象属性及结果
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_utl_print_result_normal(dlt_698_parser *parser, struct DLT_698_Result_Normal *normal_ptr);
    /**
     * @brief 递归打印记录型对象属性及结果
     * @details  打印数据
     * @param parser 解析器
     * @param record_ptr 记录型对象属性及结果
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_utl_print_result_record(dlt_698_parser *parser, struct DLT_698_RESULT_RECORD *record_ptr);

    /**
     * @brief 打印时间标签域
     * @details  打印数据
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_utl_print_time_tag(dlt_698_parser *parser);
    /**
     * @brief 打印跟随上报域
     * @details  打印数据
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_utl_print_follow_report(dlt_698_parser *parser);
#ifdef __cplusplus
}
#endif
#endif