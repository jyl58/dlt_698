/**
 * @file dlt_system_utl.c
 * @date 2026-10-31
 * @brief 系统工具接口实现
 * @details 默认基于POSIX时钟实现，移植时替换本文件即可
 */
#include "dlt_system_utl.h"

#include <time.h>

uint64_t dlt_sys_start_timestamp_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000u + (uint64_t)ts.tv_nsec / 1000000u;
}
