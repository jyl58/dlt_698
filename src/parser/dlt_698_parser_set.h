/**
 * @file dlt_698_parser_set.h
 * @date 2025-03-12
 * @brief 设置请求（SET-Request）/响应设置（SET-Response）报文解析接口
 * @details 通过该部分定义的接口可以解析SET相关报文
 */
#ifndef DLT_698_PARSER_SET_H_
#define DLT_698_PARSER_SET_H_
#include "dlt_698_type.h"
#include "dlt_698_parser.h"
#include "dlt_698_parser_set_normal.h"
#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief 设置请求（SET-Request）报文解析
     * @details 通过具体的报文类型调用相关解析接口
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_set_req(dlt_698_parser *parser);
    /**
     * @brief 响应设置（SET-Response）报文解析
     * @details 通过具体的报文类型调用相关解析接口
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_set_res(dlt_698_parser *parser);
    /**
     * @brief 请求设置一个对象属性（SetRequestNormal）
     * @details 解析06 01 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_set_req_normal(dlt_698_parser *parser);
    /**
     * @brief 请求设置若干个对象属性（SetRequestNormalList）
     * @details 解析06 02 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_set_req_normal_list(dlt_698_parser *parser);
    /**
     * @brief 响应设置一个对象属性（SetResponseNormal）
     * @details 解析86 01 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_set_res_normal(dlt_698_parser *parser);
    /**
     * @brief 响应设置若干个对象属性（SetResponseNormalList）
     * @details 解析86 02 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_set_res_normal_list(dlt_698_parser *parser);
    /**
     * @brief 请求设置后读取若干个对象属性（SetThenGetRequestNormalList）
     * @details 解析06 03 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_set_get_req_normal_list(dlt_698_parser *parser);
    /**
     * @brief 响应设置若干个对象属性以及读取若干个对象属性（SetThenGetResponseNormalList）
     * @details 解析86 03 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_set_get_res_normal_list(dlt_698_parser *parser);

#ifdef __cplusplus
}
#endif
#endif