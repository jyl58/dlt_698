/**
 * @file dlt_698_parser_set_normal.h
 * @date 2025-03-12
 * @brief 定义设置-SET相关数据类型
 * @details 定义数据类型
 */
#ifndef DLT_698_PARSER_SET_NORMAL_H_
#define DLT_698_PARSER_SET_NORMAL_H_
#include "dlt_698_parser.h"
#include "dlt_698_type.h"
#include "dlt_698_data.h"
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

    /**
     * @brief 对象属性
     */
    struct DLT_698_SET_ATTRIBUTE
    {
        dlt_698_data_t oad;     ///< 一个对象属性描述符
        dlt_698_data_t data;    ///< 数据
        uint16_t next_index;         ///< 兄弟节点索引下标，叶子节点为0
    };

    /**
     * @brief 对象属性设置结果
     */
    struct DLT_698_SET_RESULT
    {
        dlt_698_data_t oad;    ///< 一个对象属性描述符
        uint8_t DAR;                ///< 设置执行结果
        uint16_t next_index;        ///< 兄弟节点索引下标，叶子节点为0
    };
    /**
     * @brief 设置后读取对象属性
     */
    struct DLT_698_SET_GET_ATTRIBUTE
    {
        dlt_698_data_t set_oad;     ///< 一个设置的对象属性
        dlt_698_data_t set_data;    ///< 设置数据
        dlt_698_data_t get_oad;     ///< 一个读取的对象属性
        uint8_t delay;                   ///< 延时读取时间——单位：秒
        uint16_t next_index;             ///< 兄弟节点索引下标，叶子节点为0
    };
    /**
     * @brief 对象属性设置后读取结果
     */
    struct DLT_698_SET_GET_RESULT
    {
        dlt_698_data_t set_oad;                         ///< 一个设置的对象属性描述符
        uint8_t DAR;                                         ///< 设置执行结果
        struct DLT_698_Result_Normal result_nornaml;    ///< 一个对象属性及结果
        uint16_t next_index;                                 ///< 兄弟节点索引下标，叶子节点为0
    };

    /**
     * @brief 一个或若干个对象属性
     * @note 用于SetRequestNormal(06 01)/SetRequestNormalList(06 02)数据解析
     */
    struct DLT_698_SET_NOR_REQ
    {
        struct DLT_698_SET_ATTRIBUTE *set_ptr;    ///< 对象属性指针
    };

    /**
     * @brief 一个或若干个对象属性设置结果
     * @note 用于SetResponseNormal(86 01)/SetResponseNormalList(86 02)数据解析
     */
    struct DLT_698_SET_NOR_RES
    {
        struct DLT_698_SET_RESULT *result_ptr;    ///< 对象属性设置结果指针
    };
    /**
     * @brief 一个或若干个设置后读取对象属性
     * @note 用于SetThenGetRequestNormalList(06 03)数据解析
     */
    struct DLT_698_SET_GET_REQ
    {
        struct DLT_698_SET_GET_ATTRIBUTE *set_ptr;    ///< 设置后读取对象属性指针
    };
    /**
     * @brief 一个或若干个对象属性设置后读取结果
     * @note 用于SetThenGetRequestNormalList(86 03)数据解析
     */
    struct DLT_698_SET_GET_RES
    {
        struct DLT_698_SET_GET_RESULT *result_ptr;    ///< 对象属性设置后读取结果指针
    };


#pragma pack()
#ifdef __cplusplus
}
#endif

#endif