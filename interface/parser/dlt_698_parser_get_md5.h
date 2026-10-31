/**
 * @file dlt_698_parser_get_md5.h
 * @date 2025-03-12
 * @brief 请求和响应读取一个对象属性MD5值
 * @details 定义数据类型
 */

#ifndef DLT_698_PARSER_GET_MD5_H_
#define DLT_698_PARSER_GET_MD5_H_
#include "dlt_698_parser.h"
#include "dlt_698_type.h"
#include "dlt_698_data.h"
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

    /**
     * @brief  请求读取一个对象属性的MD5值
     */
    struct DLT_698_GET_MD5_REQ
    {
        dlt_698_data_t oad;    ///< OAD
    };
    /**
     * @brief 响应读取一个对象属性的MD5值
     */
    struct DLT_698_GET_MD5_RES
    {
        dlt_698_data_t oad;     ///< OAD
        uint8_t dar;                 ///< 错误信息 0时data为MD5值 其他data=NULL
        dlt_698_data_t data;    ///< MD5值
    };


#pragma pack()
#ifdef __cplusplus
}
#endif

#endif