/**
 * @file dlt_698_utl_data.h
 * @date 2025-04-18
 * @brief 698数据类型解析
 * @details 数据类型解析
 */
#ifndef __DLT_698_PARSER_DATA_H__
#define __DLT_698_PARSER_DATA_H__

#include <stdbool.h>
#include "dlt_698_type.h"
#include "dlt_698_data.h"
#include "dlt_698_parser.h"
#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief 解析oop_bool数据值
     * @details 解析dlt_698_data_t获取具体数据
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param val_ptr [out]解析数据
     * @return 1解析成功，解析失败
     */
    bool dlt_698_get_bool(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_bool *val_ptr);
    /**
     * @brief 解析oop_bit_string数据值
     * @details 解析dlt_698_data_t获取具体数据。位串按位展开存放，每个元素占 1 字节(值 0/1)，
     *          因此 bit_size 是"位数"而非字节数；内容位数 <= bit_size 即成功。
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param bit_ptr [out]数据存储区，至少 bit_size 个元素
     * @param bit_size 存储区可容纳的位数
     * @param real_size [out]实际位数
     * @return 1解析成功，0失败(指针为空、类型不符、存储区不足或载荷越界)
     */
    bool dlt_698_get_bit_string(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_bit_string *bit_ptr, uint16_t bit_size, uint16_t *real_size);
    /**
     * @brief 解析oop_double_long数据值
     * @details 解析dlt_698_data_t获取具体数据
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param val_ptr [out]解析数据
     * @return 1解析成功，解析失败
     */
    bool dlt_698_get_double_long(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_double_long *val_ptr);
    /**
     * @brief 解析oop_double_long_unsigned数据值
     * @details 解析dlt_698_data_t获取具体数据
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param val_ptr [out]解析数据
     * @return 1解析成功，解析失败
     */
    bool dlt_698_get_double_long_unsigned(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_double_long_unsigned *val_ptr);
    /**
     * @brief 解析oop_octet_string数据值
     * @details 解析dlt_698_data_t获取具体数据。字节串不加结束符，
     *          内容长度 <= octet_size 即成功(两者相等正好填满存储区)。
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param octet_ptr 数据存储区指针
     * @param octet_size 数据存储区大小(字节)
     * @param real_size [out]实际解析数据大小(字节)
     * @return 1解析成功，0失败(指针为空、类型不符、存储区不足或载荷越界)
     */
    bool dlt_698_get_octet_string(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_octet_string *octet_ptr, uint16_t octet_size, uint16_t *real_size);
    /**
     * @brief 解析oop_visible_string数据值
     * @details 解析dlt_698_data_t获取具体数据。字符串需要在末尾补 '\0'，
     *          因此存储区需比内容至少多 1 字节：内容长度 < visible_size 才成功。
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param visible_ptr 数据存储区指针
     * @param visible_size 数据存储区大小(含结束符)
     * @param real_size [out]实际解析数据大小(不含结束符)
     * @return 1解析成功，0失败(指针为空、类型不符、存储区不足或载荷越界)
     */
    bool dlt_698_get_visible_string(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_visible_string *visible_ptr, uint16_t visible_size, uint16_t *real_size);
    /**
     * @brief 解析oop_utf8_string数据值
     * @details 解析dlt_698_data_t获取具体数据，只接受 UTF8_STRING(12) 类型节点。
     *          字符串需要在末尾补 '\0'，因此存储区需比内容至少多 1 字节：
     *          内容长度 < utf8_size 才成功。
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param utf8_ptr 数据存储区指针
     * @param utf8_size 数据存储区大小(含结束符)
     * @param real_size [out]实际解析数据大小(不含结束符)
     * @return 1解析成功，0失败(指针为空、类型不符、存储区不足或载荷越界)
     */
    bool dlt_698_get_utf8_string(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_utf8_string *utf8_ptr, uint16_t utf8_size, uint16_t *real_size);

    /**
     * @brief 解析oop_integer数据值
     * @details 解析dlt_698_data_t获取具体数据
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param val_ptr [out]解析数据
     * @return 1解析成功，解析失败
     */
    bool dlt_698_get_integer(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_integer *val_ptr);

    /**
     * @brief 解析oop_long数据值
     * @details 解析dlt_698_data_t获取具体数据
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param val_ptr [out]解析数据
     * @return 1解析成功，解析失败
     */
    bool dlt_698_get_long(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_long *val_ptr);

    /**
     * @brief 解析oop_unsigned数据值
     * @details 解析dlt_698_data_t获取具体数据
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param val_ptr [out]解析数据
     * @return 1解析成功，解析失败
     */
    bool dlt_698_get_unsigned(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_unsigned *val_ptr);
    /**
     * @brief 解析oop_long_unsigned数据值
     * @details 解析dlt_698_data_t获取具体数据
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param val_ptr [out]解析数据
     * @return 1解析成功，解析失败
     */
    bool dlt_698_get_long_unsigned(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_long_unsigned *val_ptr);
    /**
     * @brief 解析oop_long64数据值
     * @details 解析dlt_698_data_t获取具体数据
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param val_ptr [out]解析数据
     * @return 1解析成功，解析失败
     */
    bool dlt_698_get_long64(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_long64 *val_ptr);
    /**
     * @brief 解析oop_long64数据值
     * @details 解析dlt_698_data_t获取具体数据
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param val_ptr [out]解析数据
     * @return 1解析成功，解析失败
     */
    bool dlt_698_get_long64_unsigned(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_long64_unsigned *val_ptr);
    /**
     * @brief 解析oop_enum数据值
     * @details 解析dlt_698_data_t获取具体数据
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param val_ptr [out]解析数据
     * @return 1解析成功，解析失败
     */
    bool dlt_698_get_enum(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_enum *val_ptr);
    /**
     * @brief 解析oop_float32数据值
     * @details 解析dlt_698_data_t获取具体数据
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param val_ptr [out]解析数据
     * @return 1解析成功，解析失败
     */
    bool dlt_698_get_float32(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_float32 *val_ptr);
    /**
     * @brief 解析oop_float64数据值
     * @details 解析dlt_698_data_t获取具体数据
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param val_ptr [out]解析数据
     * @return 1解析成功，解析失败
     */
    bool dlt_698_get_float64(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_float64 *val_ptr);
    /**
     * @brief 解析oop_date_time数据值
     * @details 解析dlt_698_data_t获取具体数据
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param val_ptr [out]解析数据
     * @return 1解析成功，解析失败
     */
    bool dlt_698_get_date_time(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_date_time *val_ptr);
    /**
     * @brief 解析oop_date数据值
     * @details 解析dlt_698_data_t获取具体数据
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param val_ptr [out]解析数据
     * @return 1解析成功，解析失败
     */
    bool dlt_698_get_date(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_date *val_ptr);
    /**
     * @brief 解析oop_time数据值
     * @details 解析dlt_698_data_t获取具体数据
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param val_ptr [out]解析数据
     * @return 1解析成功，解析失败
     */
    bool dlt_698_get_time(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_time *val_ptr);
    /**
     * @brief 解析oop_date_time_s数据值
     * @details 解析dlt_698_data_t获取具体数据
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param val_ptr [out]解析数据
     * @return 1解析成功，解析失败
     */
    bool dlt_698_get_date_time_s(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_date_time_s *val_ptr);
    /**
     * @brief 解析oop_oi数据值
     * @details 解析dlt_698_data_t获取具体数据
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param val_ptr [out]解析数据
     * @return 1解析成功，解析失败
     */
    bool dlt_698_get_oi(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_oi *val_ptr);
    /**
     * @brief 解析oop_oad数据值
     * @details 解析dlt_698_data_t获取具体数据
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param val_ptr [out]解析数据
     * @return 1解析成功，解析失败
     */
    bool dlt_698_get_oad(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_oad *val_ptr);
    /**
     * @brief 解析oop_omd数据值
     * @details 解析dlt_698_data_t获取具体数据
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param val_ptr [out]解析数据
     * @return 1解析成功，解析失败
     */
    bool dlt_698_get_omd(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_omd *val_ptr);
    /**
     * @brief 解析oop_ti数据值
     * @details 解析dlt_698_data_t获取具体数据
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param val_ptr [out]解析数据
     * @return 1解析成功，解析失败
     */
    bool dlt_698_get_ti(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_ti *val_ptr);
    /**
     * @brief 解析oop_scaler_unit数据值
     * @details 解析dlt_698_data_t获取具体数据
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param val_ptr [out]解析数据
     * @return 1解析成功，解析失败
     */
    bool dlt_698_get_scaler_unit(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_scaler_unit *val_ptr);
    /**
     * @brief 解析oop_comdcb数据值
     * @details 解析dlt_698_data_t获取具体数据
     * @param parser 解析器
     * @param data_ptr 解析数据信息
     * @param val_ptr [out]解析数据
     * @return 1解析成功，解析失败
     */
    bool dlt_698_get_comdcb(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_comdcb *val_ptr);
#ifdef __cplusplus
}
#endif
#endif