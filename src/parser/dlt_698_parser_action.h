#ifndef DLT_698_PARSER_ACTION_H_
#define DLT_698_PARSER_ACTION_H_
#include "dlt_698_type.h"
#include "dlt_698_parser.h"
#include "dlt_698_parser_action_normal.h"
#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief 操作请求（ACTION-Request）报文解析
     * @details 通过具体的报文类型调用相关解析接口
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_act_req(dlt_698_parser *parser);
    /**
     * @brief 响应操作（ACTION-Response）报文解析
     * @details 通过具体的报文类型调用相关解析接口
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_act_res(dlt_698_parser *parser);
    /**
     * @brief 请求操作一个对象方法（ActionRequestNormal）
     * @details 解析07 01 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_act_req_normal(dlt_698_parser *parser);
    /**
     * @brief 请求操作若干个对象方法（ActionRequestNormalList）
     * @details 解析07 02 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_act_req_normal_list(dlt_698_parser *parser);
    /**
     * @brief 响应操作一个对象方法（ActionResponseNormal）
     * @details 解析87 01 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_act_res_normal(dlt_698_parser *parser);
    /**
     * @brief 响应操作若干个对象方法（ActionResponseNormalList）
     * @details 解析87 02 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_act_res_normal_list(dlt_698_parser *parser);
    /**
     * @brief 请求操作若干个对象方法后读取若干个对象属性（ActionThenGetRequestNormalList）
     * @details 解析07 03 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_act_get_req_normal_list(dlt_698_parser *parser);
    /**
     * @brief 响应操作若干个对象方法后读取若干个属性（ActionThenGetResponseNormalList）
     * @details 解析87 03 报文
     * @param parser 解析器
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_parse_act_get_res_normal_list(dlt_698_parser *parser);


#ifdef __cplusplus
}
#endif
#endif