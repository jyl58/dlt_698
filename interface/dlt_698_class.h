/**
 * @file dlt_698_class.h
 * @date 2025-03-12
 * @brief 定义组帧相关信息
 * @details 定义组帧相关信息
 */
#ifndef DLT_698_CLASS_H_
#define DLT_698_CLASS_H_
#include "dlt_698_type.h"
#include "dlt_698_data.h"
#include "dlt_698_parser.h"
#include <time.h>
#include <stdbool.h>
/**
 * @brief 计算结构体类型中成员的偏移量
 */
#ifndef offsetof
    #define offsetof(type, member) ((size_t)&((type *)0)->member)
#endif
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)
    /**
     * @brief 组帧信息结构体
     */
    struct DLT_698_CLASS_INFO
    {
        uint16_t len;       ///< 结构体类型中成员占用的字节数
        uint8_t arry;       ///< 数组元素个数，0表示不用数组
        uint16_t offset;    ///< 存储偏移地址
    };

    /**
     * @brief 组帧编码函数
     * @details 根据选择属性及索引进行组帧
     * @param if_tb 组帧信息表
     * @param data 待组帧数据
     * @param att 属性选择
     * @param att_index 属性数据索引，从1开始
     * @param att_len 属性数据个数
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_apdu_encoder(const struct DLT_698_CLASS_INFO *if_tb, void *data, uint8_t att, uint8_t att_index, uint8_t att_len, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief 请求读取或请求响应开始信息组帧
     * @details 组帧： 帧类型|数据类型|PIID  如：05 01 02
     * @param req 1表示请求读取，0表示请求响应
     * @param method 数据类型选择
     * @param piid 请求时为PIID，应答时为PIID-ACD
     * @param des 输出组帧数据缓冲区
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_header_get(bool req, enum DLT_698_GET_METHOD method, uint8_t piid, uint8_t *des);
    /**
     * @brief 请求设置或响应设置开始信息组帧
     * @details 组帧： 帧类型|数据类型|PIID  如：06 01 02
     * @param req 1表示请求设置，0表示响应设置
     * @param method 数据类型选择
     * @param piid 请求时为PIID，应答时为PIID-ACD
     * @param des 输出组帧数据缓冲区
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_header_set(bool req, enum DLT_698_SET_METHOD method, uint8_t piid, uint8_t *des);
    /**
     * @brief 请求操作或响应操作开始信息组帧
     * @details 组帧： 帧类型|数据类型|PIID  如：07 01 02
     * @param req 1表示请求操作，0表示响应操作
     * @param method 数据类型选择
     * @param piid 请求时为PIID，应答时为PIID-ACD
     * @param des 输出组帧数据缓冲区
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_header_act(bool req, enum DLT_698_ACT_METHOD method, uint8_t piid, uint8_t *des);
    /**
     * @brief Action-Request|REPORT-Notification开始信息组帧
     * @details 组帧： 帧类型|数据类型|PIID  如：07 01 02
     * @param report 1表示REPORT-Response，0表示Action_Response
     * @param method 数据类型选择
     * @param piid 请求时为PIID，应答时为PIID-ACD
     * @param des 输出组帧数据缓冲区
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_header_report(bool report, enum DLT_698_ACT_METHOD method, uint8_t piid, uint8_t *des);

    /**
     * @brief 追加null组帧
     * @details 组帧
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_null(uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief 追加array组帧
     * @details 组帧
     * @param cnt 数组元素个数
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_array(uint8_t cnt, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief 追加array组帧
     * @details 组帧
     * @param cnt 数组元素个数
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_struct(uint8_t cnt, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief oop_bool组帧
     * @details 组帧
     * @param val 数据值
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_bool(oop_bool val, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief oop_bit_string组帧
     * @details 组帧
     * @param bit_otr 待组帧数据指针
     * @param bit_len 待组帧数据长度
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_bit_string(oop_bit_string *bit_ptr, uint16_t bit_len, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief oop_double_long组帧
     * @details 组帧
     * @param val 数据值
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_double_long(oop_double_long val, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief oop_double_long_unsigned组帧
     * @details 组帧
     * @param val 数据值
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_double_long_unsigned(oop_double_long_unsigned val, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief oop_octet_string组帧
     * @details 组帧
     * @param octet_otr 待组帧数据指针
     * @param oct_len 待组帧数据长度
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_octet_string(oop_octet_string *octet_ptr, uint16_t octet_len, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief oop_visible_string组帧
     * @details 组帧
     * @param visible_otr  待组帧数据指针
     * @param visible_len 待组帧数据长度
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_visible_string(oop_visible_string *visible_ptr, uint16_t visible_len, bool tag, void *des_ptr, uint16_t des_len);
    /**
     * @brief oop_visible_string组帧
     * @details 组帧
     * @param utf8_ptr  待组帧数据指针
     * @param utf8_len 待组帧数据长度
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_utf8_string(oop_utf8_string *utf8_ptr, uint16_t utf8_len, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief oop_integer组帧
     * @details 组帧
     * @param val 数据值
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_integer(oop_integer val, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief oop_long组帧
     * @details 组帧
     * @param val 数据值
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_long(oop_long val, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief oop_unsigned组帧
     * @details 组帧
     * @param val 数据值
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_unsigned(oop_unsigned val, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief oop_long_unsigned组帧
     * @details 组帧
     * @param val 数据值
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_long_unsigned(oop_long_unsigned val, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief oop_long64组帧
     * @details 组帧
     * @param val 数据值
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_long64(oop_long64 val, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief oop_long64_unsigned组帧
     * @details 组帧
     * @param val 数据值
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_long64_unsigned(oop_long64_unsigned val, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief oop_enum组帧
     * @details 组帧
     * @param val 数据值
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_enum(oop_enum val, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief oop_float32组帧
     * @details 组帧
     * @param val 数据值
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_float32(oop_float32 val, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief oop_float64组帧
     * @details 组帧
     * @param val 数据值
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_float64(oop_float64 val, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief OAD组帧
     * @details 组帧
     * @param oad
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_oad(oop_oad oad, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief OMD组帧
     * @details 组帧
     * @param omd
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_omd(oop_omd omd, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief oop_date_time组帧
     * @details 组帧
     * @param dt 日期时间
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_date_time(oop_date_time dt, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief oop_date组帧
     * @details 组帧
     * @param dt 日期
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_date(oop_date dt, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief oop_date_time_s组帧
     * @details 组帧
     * @param ti 时间
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_time(oop_time ti, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief oop_date_time_s组帧
     * @details oop_date_time_s组帧
     * @param dts 日期时间
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_date_time_s(oop_date_time_s dts, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief oop_ti组帧
     * @details 组帧
     * @param ti 时间间隔
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_ti(oop_ti ti, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief oop_comdcb组帧
     * @details 组帧
     * @param com 串口控制块
     * @param tag 是否添加数据类型标签域
     * @param des_ptr 数据存储区指针
     * @param des_len 数据存储区长度
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_comdcb(oop_comdcb com, bool tag, uint8_t *des_ptr, uint16_t des_len);
    /**
     * @brief 可变长度编码
     * @details 可变长度编码
     * @param len 长度
     * @param des_ptr 目标指针
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_set_axdr_len(uint16_t len, uint8_t *des_ptr);

    /**
     * @brief GetRequestNormal或GetRequestNormalList请求读取组帧(整帧)
     * @details oad_cnt=1时GetRequestNormal  oad_cnt>时GetRequestNormalList
     * @param parser 解析器指针，用于获取组帧长度等信息
     * @param piid 请求时为PIID
     * @param oad_ptr oad数据指针
     * @param oad_cnt oad数据个数 目前限制64个OAD
     * @param dts_ptr 时间标签域数据指针
     * @param dlt_ptr 输出组帧数据缓冲区
     * @param dlt_size 输出组帧数据缓冲区大小
     * @return int16_t 返回组帧长度，若小于0表示出错。
     */
    int16_t dlt_698_encode_get_normal_req(dlt_698_parser *parser, uint8_t piid, oop_oad *oad_ptr, uint8_t oad_cnt, oop_date_time_s *dts_ptr, uint8_t *dlt_ptr, uint16_t dlt_size);

#pragma pack()
#ifdef __cplusplus
}
#endif
#endif