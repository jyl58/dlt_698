/**
 * @file dlt_698_parser_security.h
 * @date 2025-03-12
 * @brief 请求安全传输（SECURITY-Request）/响应安全传输（SECURITY-Response）报文解析接口
 * @details 通过该部分定义的接口可以解析安全传输相关报文
 */

#ifndef DLT_698_PARSER_SECURITY_H_
#define DLT_698_PARSER_SECURITY_H_
#include "dlt_698_type.h"
#include "dlt_698_parser_security_normal.h"
#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief 请求安全传输（SECURITY-Request）报文解析
     * @details 解析10报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_security_req(dlt_698_parser *parser);

    /**
     * @brief 响应安全传输（SECURITY-Response）报文解析
     * @details  解析90报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_security_res(dlt_698_parser *parser);

#ifdef __cplusplus
}
#endif

#endif    // DLT_698_PARSER_PRIVATE_H_