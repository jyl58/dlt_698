/**
 * @file dlt_698_mempool.h
 * @date 2025-03-12
 * @brief 内存池管理
 * @details 内存池管理
 */
#ifndef DLT_698_MEMPOOL_H_
#define DLT_698_MEMPOOL_H_
#include "dlt_698_type.h"
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

#define mem_size_t uint16_t    ///< 内部用，表征所需内存大小，可根据实际分配大小调整类型，减少管理部分ram占用

    /**
     * @brief 管理内存池信息
     */
    typedef struct mp_mempool
    {
        uint8_t *start;                        ///< 内存起始位置 APDU后边是内存池的起始位置
        mem_size_t total_mempool_size;    ///< 内存池总大小
        mem_size_t alloc_mempool_size;    ///< 内存池已分配大小
    } dlt_698_mem_manage_t;
    /**
     * @brief 内存出初始化
     * @details 初始化内存池信息
     * @param mp 内存池管理信息
     * @param buf 内存池起始位置
     * @param total_size 内存池总大小
     * @return<O时见enum FDLT_698_ERR
     */
    int16_t dlt_698_mempool_init(dlt_698_mem_manage_t *mp, uint8_t *buf, mem_size_t total_mempool_size);
    /**
     * @brief 从内存池中申请内存
     * @details 从内存池中分配wantsize大小的内存
     * @param mp 内存池管理信息
     * @param wantsize 申请内存大小
     * @return<O时见enum FDLT_698_ERR
     */
    void *dlt_698_mempool_alloc(dlt_698_mem_manage_t *mp, mem_size_t wantsize);
    /**
     * @brief 获取内存池其起始位置指针
     * @details 获取内存池起始位置
     * @param mp 内存池管理信息
     * @return<O时见enum FDLT_698_ERR
     */
    void *RM_698_mempool_start(dlt_698_mem_manage_t *mp);
    /**
     * @brief 获取内存池总大小
     * @details 获取内存池总大小
     * @param mp 内存池管理信息
     * @param wantsize 申请内存大小
     * @return<O时见enum FDLT_698_ERR
     */
    mem_size_t dlt_698_mempool_total_size(dlt_698_mem_manage_t *mp);
    /**
     * @brief 获取内存池已申请大小
     * @details 获取内存池已申请大小
     * @param mp 内存池管理信息
     * @return<O时见enum FDLT_698_ERR
     */
    mem_size_t dlt_698_mempool_alloc_size(dlt_698_mem_manage_t *mp);
    /**
     * @brief 获取内存池剩余大小
     * @details 获取内存池剩余大小
     * @param mp 内存池管理信息
     * @return<O时见enum FDLT_698_ERR
     */
    mem_size_t dlt_698_mempool_remain_size(dlt_698_mem_manage_t *mp);

#pragma pack()
#ifdef __cplusplus
}
#endif

#endif