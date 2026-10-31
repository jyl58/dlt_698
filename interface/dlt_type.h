/**
 * @file dlt_type.h
 * @date 2025-03-12
 * @brief 基础数据类型定义
 * @details 独立工程的基础类型定义，与具体平台/框架解耦
 */
#ifndef DLT_TYPE_H_
#define DLT_TYPE_H_

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

/**x86架构，powerPC架构，ARM架构 */
#if defined(__x86_64__) || defined(__ppc64__) || defined(__aarch64__)
typedef uint64_t dlt_pword_t;    // 指针类型大小
#else
typedef uint32_t dlt_pword_t;    // 指针类型大小
#endif

#define DLT_printf printf

#ifdef DLT_ON_LINUX
    #include <unistd.h>
    #define DLT_sleep_ms(x) usleep(1000 * x)
#endif

#ifdef DLT_ON_RTOS

#endif

#define DLT_UNUSED(x) (void)(x)
// 弱符号定义
#if defined(__CC_ARM) || defined(__IAR_SYSTEMS_ICC__)
    #define DLT_WEAK __weak
#elif defined(__GNUC__) || defined(__clang__) || defined(__riscv)
    #define DLT_WEAK __attribute__((weak))
#endif

#endif    // DLT_TYPE_H_
