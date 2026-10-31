/**
 * @file dlt_698_parser_connect.h
 * @date 2025-03-12
 * @brief 建立应用连接报文解析接口
 * @details 通过该部分定义的接口可以解析建立应用连接相关报文
 */

#ifndef DLT_698_PARSER_CONNNECT_H_
#define DLT_698_PARSER_CONNNECT_H_
#include "dlt_698_type.h"
#include "dlt_698_parser_connect_normal.h"
#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief 请求建立应用连接（CONNECT-Request）
     * @details 解析02报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_conn_req(dlt_698_parser *parser);

    /**
     * @brief 建立应用连接响应（CONNECT-Response）
     * @details  解析82报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_conn_res(dlt_698_parser *parser);

    /**
     * @brief 请求断开应用连接（RELEASE-Request）
     * @details 解析03报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_rel_req(dlt_698_parser *parser);
    /**
     * @brief 断开应用连接响应（RELEASE-Response）
     * @details 解析83报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_rel_res(dlt_698_parser *parser);

    /**
     * @brief 断开应用连接通知（RELEASE-Notification）
     * @details 解析84报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_rel_ntf(dlt_698_parser *parser);


#ifdef __cplusplus
}
#endif
#endif    // DLT_698_PARSER_CONNECT_H_