/**
 * @file dlt_698_parser_link.h
 * @date 2025-03-12
 * @brief 预连接请求（LINK-Request）/预连接响应（LINK-Response）报文解析接口
 * @details 通过该部分定义的接口可以解析预连接相关报文
 */

#ifndef DLT_698_PARSER_LINK_H_
#define DLT_698_PARSER_LINK_H_
#include "dlt_698_type.h"
#include "dlt_698_parser_link_normal.h"
#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief 预连接请求（LINK-Request）报文解析
     * @details 解析01报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_link_req(dlt_698_parser *parser);

    /**
     * @brief 响应安全传输（SECURITY-Response）报文解析
     * @details  解析81报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_link_res(dlt_698_parser *parser);

#ifdef __cplusplus
}
#endif
#endif    // DLT_698_PARSER_LINK_H_