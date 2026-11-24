/**
 * @file dlt_698_type.h
 * @date 2025-03-12
 * @brief 定义数据类型
 * @details 定义数据类型
 */
#ifndef DLT_698_TYPE_H_
#define DLT_698_TYPE_H_
#include "dlt_type.h"
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)


    /// 布尔值数据类型定义
    typedef uint8_t oop_bool;
    /// 位串数据类型定义
    typedef uint8_t oop_bit_string;
    /// 32位整数数据类型定义
    typedef int32_t oop_double_long;
    /// 32位正整数数据类型定义
    typedef uint32_t oop_double_long_unsigned;
    /// 8位字节串数据类型定义
    typedef uint8_t oop_octet_string;
    /// ASCII字符串数据类型定义
    typedef char oop_visible_string;
    /// UTF-8编码的字符串数据类型定义
    typedef uint8_t oop_utf8_string;
    /// 8位整数数据类型定义
    typedef int8_t oop_integer;
    /// 16位整数数据类型定义
    typedef int16_t oop_long;
    /// 8位正整数数据类型定义
    typedef uint8_t oop_unsigned;
    /// 16位正整数数据类型定义
    typedef uint16_t oop_long_unsigned;
    /// 64位整数数据类型定义
    typedef int64_t oop_long64;
    /// 64位正整数数据类型定义
    typedef uint64_t oop_long64_unsigned;
    /// 枚举数据类型定义
    typedef uint8_t oop_enum;
    /// 32位浮点数数据类型定义
    typedef float oop_float32;
    /// 64位浮点数数据类型定义
    typedef double oop_float64;
    /**
     * @brief 日期时间数据类型定义
     */
    typedef struct DLT_698_OOP_DATE_TIME
    {
        oop_long_unsigned year;           ///< 年 FFFFH 表示无效
        oop_unsigned month;               ///< 月 FFH表示无效
        oop_unsigned day;                 ///< 日 FFH表示无效
        oop_unsigned day_of_week;         ///< 星期几 FFH表示无效, 0表示周日，1…6分别表示周一到周六
        oop_unsigned hour;                ///< 时 FFH表示无效
        oop_unsigned minute;              ///< 分 FFH表示无效
        oop_unsigned second;              ///< 秒 FFH表示无效
        oop_long_unsigned millisecond;    ///< 毫秒 FFFFH表示无效

    } oop_date_time;
    /**
     * @brief 日期数据类型定义
     */
    typedef struct DLT_698_OOP_DATE
    {
        oop_long_unsigned year;      ///< 年 FFFFH 表示无效
        oop_unsigned month;          ///< 月 FFH表示无效
        oop_unsigned day;            ///< 日 FFH表示无效
        oop_unsigned day_of_week;    ///< 星期几 FFH表示无效, 0表示周日，1…6分别表示周一到周六
    } oop_date;
    /**
     * @brief 时间数据类型定义
     */
    typedef struct DLT_698_OOP_TIME
    {
        oop_unsigned hour;      ///< 时 FFH表示无效
        oop_unsigned minute;    ///< 分 FFH表示无效
        oop_unsigned second;    ///< 秒 FFH表示无效
    } oop_time;
    /**
     * @brief 日期时间数据类型定义
     */
    typedef struct DLT_698_OOP_DATE_TIME_S
    {
        oop_long_unsigned year;    ///< 年 FFFFH表示无效
        oop_unsigned month;        ///< 月 FFH表示无效
        oop_unsigned day;          ///< 日 FFH表示无效
        oop_unsigned hour;         ///< 时 FFH表示无效
        oop_unsigned minute;       ///< 分 FFH表示无效
        oop_unsigned second;       ///< 秒 FFH表示无效
    } oop_date_time_s;
    /// 对象标识数据类型定义
    typedef uint16_t oop_oi;
    /**
     * @brief 对象属性描述符OAD数据类型定义
     */
    typedef union DLT_698_OOP_OAD
    {
        uint32_t val;
        struct
        {
            oop_unsigned att_index;    ///< 属性内元素索引
            oop_unsigned att_tag;      ///< 属性标识及其特征
            oop_oi oi;                 ///< 对象标识
        } st;
    } oop_oad;
    /**
     * @brief 对象方法描述符OMD数据类型定义
     */
    typedef union DLT_698_OOP_OMD
    {
        uint32_t val;
        struct
        {
            oop_unsigned act_mode;    ///< 操作模式
            oop_unsigned func_tag;    ///< 方法标识
            oop_oi oi;                ///< 对象标识
        } st;
    } oop_omd;
    /**
     * @brief 时间间隔数据类型定义
     */
    typedef struct DLT_698_OOP_TI
    {
        oop_enum unit;                 ///< 单位枚举值
        oop_long_unsigned interval;    ///< 间隔值
    } oop_ti;
    /**
     * @brief 换算及单位数据类型定义
     */
    typedef struct DLT_698_OOP_SCALER_UNIT
    {
        oop_integer scaler;    ///< 换算因子
        oop_enum unit;         ///< 单位枚举值
    } oop_scaler_unit;

    /**
     * @brief 串口控制块COMDCB数据类型定义
     */
    typedef struct DLT_698_OOP_COMDCB
    {
        oop_enum baud_rate;       ///< 波特率
        oop_enum parity;          ///< 校验位
        oop_enum data_bits;       ///< 数据位
        oop_enum stop_bits;       ///< 停止位
        oop_enum flow_control;    ///< 流控
    } oop_comdcb;

    /**
     * @brief 跟随上报信息域
     */
    typedef struct DLT_698_Follow_Report
    {
        uint8_t follow_type;    ///< 上报类型
        union
        {
            struct DLT_698_Result_Normal *normal_ptr;    ///< 对象属性及结果指针
            struct DLT_698_RESULT_RECORD *result_ptr;    ///< 记录型对象属性及结果指针
        } data;

    } dlt_698_follow_report_t;

    /**
     * @brief 数据类型枚举定义
     */
    enum DLT_698_DATA_TYPE
    {
        DLT_698_TYPE_OOP_NULL = 0,                    ///< [0]NULL
        DLT_698_TYPE_OOP_ARRAY = 1,                   ///< [1]array
        DLT_698_TYPE_OOP_STRUCT = 2,                  ///< [2]structure
        DLT_698_TYPE_OOP_BOOL = 3,                    ///< [3]bool
        DLT_698_TYPE_OOP_BIT_STRING = 4,              ///< [4]bit string
        DLT_698_TYPE_OOP_DOUBLE_LONG = 5,             ///< [5]double long
        DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED = 6,    ///< [6]double long unsigned
        DLT_698_TYPE_OOP_OCTET_STRING = 9,            ///< [9]octet string
        DLT_698_TYPE_OOP_VISIBLE_STRING = 10,         ///< [10]visible-string
        DLT_698_TYPE_OOP_UTF8_STRING = 12,            ///< [12]utf8-string
        DLT_698_TYPE_OOP_INTEGER = 15,                ///< [15]integer
        DLT_698_TYPE_OOP_LONG = 16,                   ///< [16]LONG
        DLT_698_TYPE_OOP_UNSIGNED = 17,               ///< [17]unsigned
        DLT_698_TYPE_OOP_LONG_UNSIGNED = 18,          ///< [18]long unsigned
        DLT_698_TYPE_OOP_LONG64 = 20,                 ///< [20]long64
        DLT_698_TYPE_OOP_LONG64_UNSIGNED = 21,        ///< [21]long64 unsigned
        DLT_698_TYPE_OOP_ENUM = 22,                   ///< [22]enum
        DLT_698_TYPE_OOP_FLOAT32 = 23,                ///< [23]float32
        DLT_698_TYPE_OOP_FLOAT64 = 24,                ///< [24]float64
        DLT_698_TYPE_OOP_DATE_TIME = 25,              ///< [25]date_time
        DLT_698_TYPE_OOP_DATE = 26,                   ///< [26]date
        DLT_698_TYPE_OOP_TIME = 27,                   ///< [27]time
        DLT_698_TYPE_OOP_DATE_TIME_S = 28,            ///< [28]date_time_s
        DLT_698_TYPE_OOP_OI = 80,                     ///< [80]OI
        DLT_698_TYPE_OOP_OAD = 81,                    ///< [81]OAD
        DLT_698_TYPE_OOP_ROAD = 82,                   ///< [82]ROAD
        DLT_698_TYPE_OOP_OMD = 83,                    ///< [83]OMD
        DLT_698_TYPE_OOP_TI = 84,                     ///< [84]TI
        DLT_698_TYPE_OOP_TSA = 85,                    ///< [85]TSA
        DLT_698_TYPE_OOP_MAC = 86,                    ///< [86]MAC
        DLT_698_TYPE_OOP_RN = 87,                     ///< [87]RN
        DLT_698_TYPE_OOP_REGION = 88,                 ///< [88]Region
        DLT_698_TYPE_OOP_SCALER_UNIT = 89,            ///< [89]Scaler_Unit
        DLT_698_TYPE_OOP_RSD = 90,                    ///< [90]RSD
        DLT_698_TYPE_OOP_CSD = 91,                    ///< [91]CSD
        DLT_698_TYPE_OOP_MS = 92,                     ///< [92]MS
        DLT_698_TYPE_OOP_SID = 93,                    ///< [93]SID
        DLT_698_TYPE_OOP_SID_MAC = 94,                ///< [94]SID_MAC
        DLT_698_TYPE_OOP_COMDCB = 95,                 ///< [95]COMDCB
        DLT_698_TYPE_OOP_RCSD = 96,                   ///< [96]RCSD
    };
    /**
     * @brief 解析器异常值枚举
     */
    enum DLT_698_ERR
    {
        DLT_698_ERR_NONE = 0,           ///< 正常
        DLT_698_ERR_PARSING = -1,       ///< 正在解析
        DLT_698_ERR_CREAT = -2,         ///< 创建698解析器失败
        DLT_698_ERR_EMPTY_PTR = -3,     ///< 空指针
        DLT_698_ERR_DAR = -4,           ///< 数据无效错误
        DLT_698_ERR_PARSE = -5,         ///< 解析数据过程遇到错误
        DLT_698_ERR_RESULT_PTR = -6,    ///< 结果存储异常
        DLT_698_ERR_INVALID = -7,       ///< 数据无效
        DLT_698_ERR_OVER = -8,          ///< 下标溢出
        DLT_698_ERR_MEM = -9,           ///< 内存池空间不足或内部内存操作异常
        DLT_698_ERR_TAKE = -10,         ///< 提取数据异常
        DLT_698_ERR_TYPE = -11,         ///< 类型错误
        DLT_698_ERR_LEN = -12,          ///< 长度错误
        DLT_698_ERR_DATA = -13,         ///< 数据错误
        DLT_698_ERR_FIND = -14,         ///< 未找到一致数据
    };


#pragma pack()
#ifdef __cplusplus
}
#endif
#endif