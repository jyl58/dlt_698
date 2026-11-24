/**
 * @file dlt_698_parser_get.h
 * @date 2025-03-12
 * @brief 请求读取（GET-Request）/响应读取（GET-Response）报文解析接口
 * @details 通过该部分定义的接口可以解析GET相关报文
 */

#ifndef DLT_698_PARSER_GET_H_
#define DLT_698_PARSER_GET_H_
#include "dlt_698_type.h"
#include "dlt_698_parser.h"
#include "dlt_698_parser_get_normal.h"
#include "dlt_698_parser_get_record.h"
#include "dlt_698_parser_get_next.h"
#include "dlt_698_parser_get_md5.h"
#include "dlt_698_parser_report_normal.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief 请求读取（GET-Request）报文解析
     * @details 通过具体的报文类型调用相关解析接口
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_get_req(dlt_698_parser *parser);
    /**
     * @brief 响应读取（GET-Response）报文解析
     * @details 通过具体的报文类型调用相关解析接口
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_get_res(dlt_698_parser *parser);
    /**
     * @brief 请求读取一个对象属性（GetRequestNormal）
     * @details 解析05 01 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_get_req_normal(dlt_698_parser *parser);
    /**
     * @brief 请求读取若干个对象属性（GetRequestNormalList）
     * @details 解析05 02 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_get_req_normal_list(dlt_698_parser *parser);
    /**
     * @brief 读取一个对象属性的响应（GetResponseNormal）
     * @details 解析85 01 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_get_res_normal(dlt_698_parser *parser);
    /**
     * @brief 读取若干个对象属性的响应（GetResponseNormalList）
     * @details 解析85 02 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_get_res_normal_list(dlt_698_parser *parser);
    /**
     * @brief 请求读取一个记录型对象属性 （GetRequestRecord）
     * @details 解析05 03 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_get_req_record(dlt_698_parser *parser);
    /**
     * @brief 请求读取若干个记录型对象属性（GetRequestRecordList）
     * @details 解析05 04 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_get_req_record_list(dlt_698_parser *parser);
    /**
     * @brief 读取一个记录型对象属性的响应（ GetResponseRecord）
     * @details 解析85 03报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_get_res_record(dlt_698_parser *parser);
    /**
     * @brief 读取若干个记录型对象属性的响应（GetResponseRecordList）
     * @details 解析85 04 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_get_res_record_list(dlt_698_parser *parser);
    /**
     * @brief 请求读取分帧传输的下一帧（GetRequestNext）
     * @details 解析05 05 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_get_req_next(dlt_698_parser *parser);
    /**
     * @brief 读取分帧传输的下一帧的响应（GetResponseNext）
     * @details 解析85 05 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_get_res_next(dlt_698_parser *parser);
    /**
     * @brief 请求读取一个对象属性的MD5值（GetRequestMD5）
     * @details 解析05 06报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_get_req_md5(dlt_698_parser *parser);
    /**
     * @brief 读取一个对象属性的MD5值的响应（GetResponseMD5）
     * @details 解析85 06报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_get_res_md5(dlt_698_parser *parser);


#ifdef __cplusplus
}
#endif
#endif