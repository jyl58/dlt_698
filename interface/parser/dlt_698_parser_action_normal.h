/**
 * @file dlt_698_parser_action_normal.h
 * @date 2025-03-12
 * @brief 定义操作-ACTION相关数据类型
 * @details 定义数据类型
 */
#ifndef DLT_698_PARSER_ACTION_NORMAL_H_
#define DLT_698_PARSER_ACTION_NORMAL_H_
#include "dlt_698_parser.h"
#include "dlt_698_type.h"
#include "dlt_698_data.h"
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)


    /**
     * @brief 对象方法
     */
    struct DLT_698_ACT_METHOD_PARA
    {
        dlt_698_data_t omd;     ///< 对象方法描述符 OMD
        dlt_698_data_t data;    ///< 方法参数
        int next_index;         ///< 兄弟节点索引下标，叶子节点为0
    };
    /**
     * @brief 对象方法操作结果
     */
    struct DLT_698_ACT_METHOD_RESULT
    {
        dlt_698_data_t omd;     ///< 对象方法描述符 OMD
        uint8_t DAR;                 ///< 操作执行结果
        dlt_698_data_t data;    ///< 操作返回数据 OPTIONAL
        int next_index;         ///< 兄弟节点索引下标，叶子节点为0
    };
    /**
     * @brief 操作若干个对象方法后读取对象属性
     */
    struct DLT_698_ACT_GET_MOTHOD_PARA
    {
        dlt_698_data_t act_omd;    ///< 一个设置的对象方法描述符OMD
        dlt_698_data_t data;       ///< 方法参数
        dlt_698_data_t get_oad;    ///< 一个读取的对象属性描述符OAD
        uint8_t delay;                  ///< 读取延时——单位：秒
        uint16_t next_index;            ///< 兄弟节点索引下标，叶子节点为0
    };
    /**
     * @brief 操作若干个对象方法后读取属性的结果
     */
    struct DLT_698_ACT_GET_MOTHOD_RESUlT
    {
        dlt_698_data_t act_omd;                        ///< 一个设置的对象方法描述符OMD
        uint8_t DAR;                                        ///< 操作执行结果
        dlt_698_data_t get_data;                       ///< 操作返回数据
        struct DLT_698_Result_Normal result_normal;    ///< 一个对象属性及结果
        uint16_t next_index;                                ///< 兄弟节点索引下标，叶子节点为0
    };
    /**
     * @brief 一个或若干个对象方法
     * @note 用于ActionRequestNormal(07 01)数据解析
     * @note 用于ActionRequestNormalList(07 02)数据解析
     */
    struct DLT_698_ACT_NOR_REQ
    {
        struct DLT_698_ACT_METHOD_PARA *act_ptr;    ///< 对象方法指针
    };
    /**
     * @brief 一个或若干个对象方法操作结果
     * @note 用于ActionResponseNormal(87 01)数据解析
     * @note 用于ActionResponseNormalList(87 02)数据解析
     */
    struct DLT_698_ACT_NOR_RES
    {
        struct DLT_698_ACT_METHOD_RESULT *result_ptr;    ///< 对象方法操作结果指针
    };
    /**
     * @brief 操作若干个对象方法后读取对象属性
     * @note ActionThenGetRequestNormalList(07 03)数据解析
     */
    struct DLT_698_ACT_GET_REQ
    {
        struct DLT_698_ACT_GET_MOTHOD_PARA *act_ptr;    ///< 操作若干个对象方法后读取对象属性指针
    };
    /**
     * @brief  操作若干个对象方法后读取属性的结果
     * @note 用于ActionThenGetResponseNormalList(87 03)数据解析
     */
    struct DLT_698_ACT_GET_RES
    {
        struct DLT_698_ACT_GET_MOTHOD_RESUlT *result_ptr;    ///< 操作若干个对象方法后读取属性的结果指针
    };

#pragma pack()
#ifdef __cplusplus
}
#endif

#endif