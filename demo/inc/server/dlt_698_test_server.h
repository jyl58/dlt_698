/**
 * @file    dlt_698_utl_server.h
 * @brief   处理客户机的请求，根据不同的命令执行相应的操作函数
 * @details 该函数根据客户机的请求，调用相应的处理函数
 * @date    2025-04-01
 * @version 1.0
 */
#ifndef DLT_698_UTL_SERVER_H_
#define DLT_698_UTL_SERVER_H_
#include "dlt_698_parser.h"
/**
 * @brief 处理客户机的请求，根据不同的命令执行相应的操作函数
 * @details 该函数根据客户机的请求，调用相应的处理函数。
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void dlt_698_utl_server_handler(dlt_698_parser *parser);

/**
 * @brief 请求读取处理
 * @details GET-Request处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void handle_get_req(dlt_698_parser *parser);
/**
 * @brief 请求读取一个或若干个对象属性
 * @details GetRequestNormal或GetRequestNormalList处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void DLT_WEAK dlt_server_handle_get_normal(dlt_698_parser *parser);
/**
 * @brief 请求读取一个或若干个记录型对象属性
 * @details GetRequestRecord或GetRequestRecordList处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void DLT_WEAK dlt_server_handle_get_record(dlt_698_parser *parser);
/**
 * @brief 请求读取分帧传输的下一帧
 * @details GetRequestNext处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void DLT_WEAK dlt_server_handle_get_next(dlt_698_parser *parser);
/**
 * @brief 请求读取一个对象属性的MD5值
 * @details GetRequestMD5处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void DLT_WEAK dlt_server_handle_get_md5(dlt_698_parser *parser);
/**
 * @brief 设置请求
 * @details SET-Request处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void handle_set_req(dlt_698_parser *parser);
/**
 * @brief 请求设置一个或若干个对象属性
 * @details SetRequestNormal或SetRequestNormalList处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void DLT_WEAK dlt_server_handle_set_normal(dlt_698_parser *parser);
/**
 * @brief 请求设置后读取若干个对象属性
 * @details SetThenGetRequestNormalList处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void DLT_WEAK dlt_server_handle_set_get_normal(dlt_698_parser *parser);
/**
 * @brief 操作请求处理
 * @details ACTION-Request处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void handle_act_req(dlt_698_parser *parser);
/**
 * @brief 请求操作一个或若干个对象方法
 * @details ActionRequestNormal或ActionRequestNormalList处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void DLT_WEAK dlt_server_handle_act_normal(dlt_698_parser *parser);
/**
 * @brief 请求操作若干个对象方法后读取若干个对象属性
 * @details ActionThenGetRequestNormalList处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void DLT_WEAK dlt_server_handle_act_get_normal(dlt_698_parser *parser);
/**
 * @brief 通知上报处理
 * @details REPORT-Notification处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void handle_rep_res(dlt_698_parser *parser);
/**
 * @brief 通知上报若干个对象属性或通知上报若干个记录型对象属性
 * @details ReportNotificationList或ReportNotificationRecordList处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void DLT_WEAK dlt_server_handle_rep_notify(dlt_698_parser *parser);
/**
 * @brief 通知上报透明数据
 * @details ReportNotificationTransData处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void DLT_WEAK dlt_server_handle_rep_trans(dlt_698_parser *parser);
/**
 * @brief 请求安全传输
 * @details SECURITY-Request处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void handle_sec_req(dlt_698_parser *parser);
/**
 * @brief 预连接请求
 * @details LINK-Request处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void handle_link_req(dlt_698_parser *parser);
/**
 * @brief 请求建立应用连接（CONNECT-Request）
 * @details CONNECT-Request处理
 * @param parser 解析器
 * @return void 返回类型为空，无返回值。
 */
void handle_conn_req(dlt_698_parser *parser);
#endif