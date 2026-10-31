/**
 * @file dlt_system_utl.h
 * @date 2026-10-31
 * @brief 系统工具接口
 * @details 独立工程的系统级工具接口，默认基于POSIX时钟实现，
 *          移植到其他平台时替换 dlt_sys_start_timestamp_ms 实现即可
 */
#ifndef DLT_SYSTEM_UTL_H_
#define DLT_SYSTEM_UTL_H_

#include "dlt_type.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief 获取系统启动以来的毫秒时间戳
     * @return 毫秒时间戳
     */
    uint64_t dlt_sys_start_timestamp_ms(void);

#ifdef __cplusplus
}
#endif

#endif    // DLT_SYSTEM_UTL_H_
