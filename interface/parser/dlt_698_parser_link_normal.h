/**
 * @file dlt_698_parser_link_normal.h
 * @date 2025-03-12
 * @brief 定义预连接相关数据类型
 * @details 定义数据类型
 */
#ifndef DLT_698_PARSER_LINK_NORMAL_H_
#define DLT_698_PARSER_LINK_NORMAL_H_
#include "dlt_698_parser.h"
#include "dlt_698_type.h"
#include "dlt_698_data.h"
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

    /**
     * @brief 预连接请求（LINK-Request）的数据类型
     * @note 用于LINK-Request(01)数据解析
     */
    struct DLT_698_LINK_REQ
    {
        uint8_t req_type;              ///< 请求类型 enum
        uint16_t heart_cycle;          ///< 心跳周期 ong-unsigned
        dlt_698_data_t req_dt;    ///< 请求时间 date_time
    };
    /**
     * @brief 预连接响应（LINK-Response）的数据类型
     * @note 用于LINK-Response(81)数据解析
     */
    struct DLT_698_LINK_RES
    {
        uint8_t result;                 ///< 结果
        dlt_698_data_t req_dt;     ///< 请求时间 date_time，
        dlt_698_data_t recv_dt;    ///< 收到时间 date_time，
        dlt_698_data_t res_dt;     ///< 响应时间 date_time
    };

#pragma pack()
#ifdef __cplusplus
}
#endif

#endif