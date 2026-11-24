/**
 * @file    dlt_698_utl_client.h
 * @brief   最大需量组帧头文件
 * @details
 * @date    2025-04-01
 * @version 1.0
 */
#ifndef __DLT_698_UTL_ENCODE_H__
#define __DLT_698_UTL_ENCODE_H__
#include "dlt_698_parser.h"
/**
 * @brief 组帧函数组帧测试
 * @param parser 解析器指针
 * @return 返回void类型参数
 */
void dlt_698_encode_type(dlt_698_parser *parser);
/**
 * @brief 最大需量类组帧测试
 * @param parser 解析器指针
 * @return 返回void类型参数
 */
void dlt_698_encode_demand(dlt_698_parser *parser);
/**
 * @brief 电能量类组帧测试
 * @param parser 解析器指针
 * @return 返回void类型参数
 */
void dlt_698_encode_energy(dlt_698_parser *parser);

/**
 * @brief 参数变量类组帧测试
 * @param parser 解析器指针
 * @return 返回void类型参数
 */
void dlt_698_encode_param(dlt_698_parser *parser);
/**
 * @brief 数据变量类组帧测试
 * @param parser 解析器指针
 * @return 返回void类型参数
 */
void dlt_698_encode_var(dlt_698_parser *parser);
/**
 * @brief 功率类组帧测试
 * @param parser 解析器指针
 * @return 返回void类型参数
 */
void dlt_698_encode_power(dlt_698_parser *parser);
/**
 * @brief 分项变量类组帧测试
 * @param parser 解析器指针
 * @return 返回void类型参数
 */
void dlt_698_encode_phase(dlt_698_parser *parser);
/**
 * @brief 脉冲计量类组帧测试
 * @param parser 解析器指针
 * @return 返回void类型参数
 */
void dlt_698_encode_pulse(dlt_698_parser *parser);
/**
 * @brief ESAM接口类组帧测试
 * @param parser 解析器指针
 * @return 返回void类型参数
 */
void dlt_698_encode_esam(dlt_698_parser *parser);
/**
 * @brief 谐波变量类组帧测试
 * @param parser 解析器指针
 * @return 返回void类型参数
 */
void dlt_698_encode_harmonic(dlt_698_parser *parser);
/**
 * @brief GetRequestNormal或GetRequestNormalList组帧测试
 * @param parser 解析器指针
 * @return 返回void类型参数
 */
void dlt_698_test_get_normal_req(dlt_698_parser *parser);
/**
 * @brief 打印数据
 * @param title 标题
 * @param data_ptr 数据指针
 * @param apdu_len 数据长度
 * @return 返回void类型参数
 */
void printData(char *title, uint8_t *frame_ptr, int16_t frame_len);

#endif /* __DLT_698_UTL_ENCODE_H__ */