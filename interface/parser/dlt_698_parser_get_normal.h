/**
 * @file dlt_698_parser_get_normal.h
 * @date 2025-03-12
 * @brief 请求和响应读取一个对象或若干个属性
 * @details 定义数据类型
 */

#ifndef DLT_698_PARSER_GET_NORMAL_H_
#define DLT_698_PARSER_GET_NORMAL_H_
#include "dlt_698_data.h"
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

    /**
     * @brief 一个或若干个对象属性描述符（OAD）
     * @note 用于GetRequestNormal(05 01)/GetRequestNormalList(05 02)数据解析
     */
    struct DLT_698_GET_NOR_REQ
    {
        dlt_698_data_t *oad_ptr;    ///< 对象属性描述符OAD指针
    };

    /**
     * @brief 一个或若干个对象属性及结果
     * @note 用于GetResponseNormal(85 01)/GetResponseNormalList(85 02)数据解析
     */
    struct DLT_698_GET_NOR_RES
    {
        struct DLT_698_Result_Normal *normal_ptr;    ///< 对象属性及结果指针
    };


#pragma pack()
#ifdef __cplusplus
}
#endif

#endif