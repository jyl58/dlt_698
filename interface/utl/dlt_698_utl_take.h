/**
 * @file dlt_698_utl_take.h
 * @date 2025-03-12
 * @brief 获取698帧中的关键信息，如类型、控制码、地址等。
 * @details 该文件定义了从698帧中提取关键信息的相关函数。
 */
#ifndef DLT_698_UTL_TAKE_H_
#define DLT_698_UTL_TAKE_H_
#include "dlt_698_parser.h"
#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief 提取帧类型[GET/SET/ACT/REP/...]
     * @param parser 698解析器实例
     * @return <0见异常枚举，>0帧类型
     */
    int16_t dlt_698_take_type(dlt_698_parser *parser);
    /**
     * @brief 提取帧控制码
     * @param parser 698解析器实例
     * @param code 控制码指针
     * @return <0见异常枚举，>0帧类型
     */
    int16_t dlt_698_take_code(dlt_698_parser *parser, uint8_t *code);
    /**
     * @brief 提取帧地址
     * @param parser 698解析器实例
     * @param addr_ptr 地址结构体指针
     * @return <0见异常枚举，>0帧类型
     */
    int16_t dlt_698_take_addr(dlt_698_parser *parser, dlt_698_addr_t *addr_ptr);

    /**
     * @brief 提取帧地址
     * @param parser 698解析器实例
     * @param addr_ptr 地址结构体指针
     * @return <0见异常枚举，>0帧类型
     */
    int16_t dlt_698_take_sa(dlt_698_addr_t *addr_ptr, char *sa, int len);
    /**
     * @brief 提取帧处理方法
     * @param parser 698解析器实例
     * @return <0见异常枚举，>0帧类型
     */
    int16_t dlt_698_take_method(dlt_698_parser *parser);
    /**
     * @brief 提取有效数据APDU,原始帧数据的APDU部分
     * @param parser 698解析器实例
     * @param buf 存放APDU数据的缓冲区
     * @return <0见异常枚举，>=0数据长度
     */
    int16_t dlt_698_take_apdu(dlt_698_parser *parser, uint8_t *buf);
    /**
     * @brief 提取服务序号及优先标志PIID
     * @param parser 698解析器实例
     * @param piid指针
     * @return <0见异常枚举，>=0数据长度
     */
    int16_t dlt_698_take_piid(dlt_698_parser *parser, uint8_t *piid);
    /**
     * @brief 获取数据传输类型  0 普通 1 安全请求 2 安全响应
     * @param parser 698解析器实例
     * @param sec_type 数据传输类型指针
     * @return <0见异常枚举，>=0数据长度
     */
    int16_t dlt_698_take_sec_type(dlt_698_parser *parser, uint8_t *sec_type);
    /**
     * @brief 提取时间标签域
     * @param parser 698解析器实例
     * @param time_tag时间标签域指针
     * @return <0见异常枚举，>=0数据长度
     */
    int16_t dlt_698_take_time_tag(dlt_698_parser *parser, dlt_698_data_t **time_tag);
    /**
     * @brief 提取跟随上报域
     * @param parser 698解析器实例
     * @param follow_report 跟随上报域指针
     * @return <0见异常枚举，>=0数据长度
     */
    int16_t dlt_698_take_follow_report(dlt_698_parser *parser, dlt_698_follow_report_t **follow_report);
    /**
     * @brief 提取解析完成的APDU数据信息链表头
     * @param parser 698解析器实例
     * @param type 帧类型，可通过dlt_698_take_type函数获得
     * @param method 帧方法，可通过dlt_698_take_method函数获得
     * @param head_ptr 存放数据链表头的指针
     * @return <0见异常枚举，>=0数据长度
     */
    int16_t dlt_698_take_apdu_info_head(dlt_698_parser *parser, uint8_t type, uint8_t method, void **head_ptr);



#ifdef __cplusplus
}
#endif
#endif