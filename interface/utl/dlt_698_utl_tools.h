/**
 * @file dlt_698_utl_tools.h
 * @date 2025-03-12
 * @brief 定义常用的工具函数
 * @details 常用函数定义
 */
#ifndef DLT_698_UTL_TOOLS_H_
#define DLT_698_UTL_TOOLS_H_
#include "dlt_698_parser.h"
#include "dlt_698_type.h"
#include "dlt_698_data.h"
#include "dlt_698_parser.h"
#include "dlt_698_parser_get_record.h"
#include "dlt_698_parser_set_normal.h"
#include "dlt_698_parser_action_normal.h"
#include <time.h>

#ifdef __cplusplus
extern "C"
{
#endif



    /**
     * @brief 根据数据信息(dlt_698_data_t)提取数据
     * @details 获取数据
     * @param parser 解析器
     * @param data_ptr 当前节点
     * @param arry_ptr 存储数据缓冲器指针
     * @param len 存储数据缓冲器指针
     * @return 返回值：<0见异常枚举，=0正常
     */
    int16_t dlt_698_get_data_arry(dlt_698_parser *parser, dlt_698_data_t *data_ptr, uint8_t *arry_ptr, int len);
    /**
     * @brief 获取第一个子节点指针
     * @details 获取子节点指针
     * @param parser 解析器
     * @param parent_ptr 父节点
     * @return<O时见enum FDLT_698_ERR
     */
    void *dlt_698_get_child_ptr(dlt_698_parser *parser, uint16_t child_index);

    /**
     * @brief 获取当前节点的下一个同级节点指针
     * @details 获取下一个同级节点指针
     * @param parser 解析器
     * @param data_ptr 当前节点
     * @return<O时见enum FDLT_698_ERR
     */
    void *dlt_698_get_next_ptr(dlt_698_parser *parser, uint16_t next_index);
    /**
     * @brief 统计子节点个数
     * @details 统计子节点个数
     * @param parser 解析器
     * @param parent_ptr 父节点
     * @return<O时见enum FDLT_698_ERR
     */
    int dlt_698_get_data_children_cnt(dlt_698_parser *parser, dlt_698_data_t *parent_ptr);
    /**
     * @brief 统计当前节点后续兄弟节点个数（包含当前节点）
     * @details 统计当前节点后续兄弟节点个数（包含当前节点）
     * @param parser 解析器
     * @param parent_ptr 父节点
     * @return<O时见enum FDLT_698_ERR
     */
    int dlt_698_get_data_sibling_cnt(dlt_698_parser *parser, dlt_698_data_t *data_ptr);
    /**
     * @brief 统计当前节点后续兄弟节点个数（包含当前节点）
     * @details 统计当前节点后续兄弟节点个数（包含当前节点）
     * @param parser 解析器
     * @param data_ptr 当前节点
     * @param offset next_index在数据结构体中的偏移
     * @return<O时见enum FDLT_698_ERR
     */
    int dlt_698_get_common_sibling_cnt(dlt_698_parser *parser, void *data_ptr, uint16_t offset);
    /**
     * @brief 比对当前节点数据与验证数据是否一致(只比较当前节点，不遍历)
     * @details 数据比对
     * @param parser 解析器
     * @param act_ptr 当前节点
     * @param data_type 验证数据类型
     * @param arry_ptr 验证数据指针
     * @param len 验证数据长度
     * @return 0一致 <O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_equal_data(dlt_698_parser *parser, dlt_698_data_t *data_ptr, enum DLT_698_DATA_TYPE data_type, uint8_t *arry_ptr, uint16_t arry_len);

    /**
     * @brief 递归遍历是否存在与验证数据一致的节点，遍历顺序先当前节点，再子节点，最后兄弟节点
     * @details 查询数据
     * @param parser 解析器
     * @param act_ptr 当前节点,从当前节点开始查找
     * @param data_type 验证数据类型
     * @param arry_ptr 验证数据指针
     * @param len 验证数据长度
     * @return 0一致 <O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_find_data(dlt_698_parser *parser, dlt_698_data_t *data_ptr, dlt_698_data_t **node_ptr, enum DLT_698_DATA_TYPE data_type, uint8_t *arry_ptr, uint16_t arry_len);
    /**
     * @brief 判断是否为小端字节序
     * @details 判断电脑字节序
     * @return 1是  0不是
     */
    int is_little_endian();
    /**
     * @brief u16转换成大端数据
     * @details 字节序转换
     * @param parser 解析器
     * @return 转换后数据
     */
    uint16_t dlt_698_to_big_endian_u16(uint16_t val);
    /**
     * @brief u32转换成大端数据
     * @details 字节序转换
     * @param parser 解析器
     * @return 转换后数据
     */
    uint32_t dlt_698_to_big_endian_u32(uint32_t val);
    /**
     * @brief 字节序转换函数，用于两个值赋值时进行大端转换
     * @details 若电脑为小段，则进行字节倒序转换
     * @param dst_ptr 目的数据指针
     * @param src_ptr 源数据指针
     * @param src_size 数据大小
     * @return 0成功 <O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_big_endian(void *dst_ptr, void *src_ptr, int src_size);
    /**
     * @brief  若小端系统
     * @details 若电脑为小段，则进行字节倒序转换
     * @param data_ptr 数据指针
     * @param size 数据大小
     * @return 0成功 <O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_big_reverse(void *data_ptr, int size);
    /**
     * @brief 二进制数组解析为16进制数组
     * @details 二进制转16禁止
     * @param bit_ptr 二进制数据指针
     * @param bit_len 二进制数据大小
     * @param hex_ptr 十六进制数据指针
     * @return <O时见enum FDLT_698_ERR  其他表示十六进制大小
     */
    int16_t dlt_698_bit_string_to_hex(uint8_t *bit_ptr, int bit_len, uint8_t *hex_ptr);

    /**
     * @brief 将时间字符串2024-12-01 12:02:02转换为date_time_s
     * @details  时间转换
     * @param ti 时间戳
     * @param [out]dts
     * @return void
     */
    void dlt_698_str_to_dts(const char *ti, oop_date_time_s *dts);
    /**
     * @brief 将时间戳转换为date_time_s
     * @details  时间转换
     * @param ti 时间戳
     * @param [out]dts
     * @return void
     */
    void dlt_698_convert_dts(const time_t ti, oop_date_time_s *dts);

#ifdef __cplusplus
}
#endif
#endif