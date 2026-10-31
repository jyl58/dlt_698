/**
 * @file    dlt_698_test_client.h
 * @brief   处理服务器的请求，根据不同的命令执行相应的操作函数
 * @details 该函数根据服务器的请求，调用相应的处理函数
 * @date    2025-04-01
 * @version 1.0
 */
#ifndef DLT_698_UTL_CLIENT_H_
#define DLT_698_UTL_CLIENT_H_
#include "dlt_698_parser.h"

/**
 * @brief 处理服务器的请求，根据不同的命令执行相应的操作函数
 * @details 该函数根据服务器的请求，调用相应的处理函数。
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void dlt_698_utl_client_handler(dlt_698_parser *parser);
/**
 * @brief 响应读取处理
 * @details GET-Response处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void handle_get_res(dlt_698_parser *parser);
/**
 * @brief 读取一个或若干个对象属性的响应
 * @details GetResponseNormal或GetResponseNormalList处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void DLT_WEAK dlt_cli_handle_get_normal(dlt_698_parser *parser);
/**
 * @brief 读取一个或若干个记录型对象属性的响应
 * @details GetResponseRecord或GetResponseRecordList处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void DLT_WEAK dlt_cli_handle_get_record(dlt_698_parser *parser);
/**
 * @brief 读取分帧传输的下一帧的响应
 * @details GetResponseNext处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void DLT_WEAK dlt_cli_handle_get_record_next(dlt_698_parser *parser);
/**
 * @brief 读取一个对象属性的MD5值的响应
 * @details GetResponseMD5处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void DLT_WEAK dlt_cli_handle_get_md5(dlt_698_parser *parser);
/**
 * @brief 响应设置处理
 * @details SET-Response处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void handle_set_res(dlt_698_parser *parser);
/**
 * @brief 设置一个或若干个对象属性的响应
 * @details SetResponseNormal或SetResponseNormalList处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void DLT_WEAK dlt_cli_handle_set_normal(dlt_698_parser *parser);
/**
 * @brief 设置的确认信息以及读取的响应
 * @details SetThenGetResponseNormalList处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void DLT_WEAK dlt_cli_handle_set_get_normal(dlt_698_parser *parser);
/**
 * @brief 响应操作处理
 * @details ACTION-Response处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void handle_act_res(dlt_698_parser *parser);
/**
 * @brief 操作一个或若干个对象方法的响应
 * @details ActionResponseNormal或ActionResponseNormalList处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void DLT_WEAK dlt_cli_handle_act_normal(dlt_698_parser *parser);
/**
 * @brief 操作若干个对象方法后读取若干个属性的响应
 * @details ActionThenGetResponseNormalList处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void DLT_WEAK dlt_cli_handle_act_get_normal(dlt_698_parser *parser);
/**
 * @brief 上报通知处理
 * @details REPORT-Notification处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void handle_rep_req(dlt_698_parser *parser);
/**
 * @brief 通知上报若干个对象属性
 * @details ReportNotificationList处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void DLT_WEAK dlt_cli_handle_rep_notify(dlt_698_parser *parser);
/**
 * @brief 通知上报若干个记录型对象属性
 * @details ReportNotificationRecordList处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void DLT_WEAK dlt_cli_handle_rep_record_notify(dlt_698_parser *parser);
/**
 * @brief 通知上报透明数据
 * @details ReportNotificationTransData处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void DLT_WEAK dlt_cli_handle_rep_trans_notify(dlt_698_parser *parser);
/**
 * @brief 响应安全传输
 * @details SECURITY-Response处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void handle_sec_res(dlt_698_parser *parser);
/**
 * @brief 预连接响应
 * @details LINK-Response处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void handle_link_res(dlt_698_parser *parser);
/**
 * @brief 建立应用连接响应
 * @details CONNECT-Response处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void handle_conn_res(dlt_698_parser *parser);
/**
 * @brief 断开应用连接响应
 * @details RELEASE-Response处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void handle_rel_res(dlt_698_parser *parser);
/**
 * @brief 断开应用连接通知
 * @details RELEASE-Notification处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void handle_rel_nty(dlt_698_parser *parser);
#endif