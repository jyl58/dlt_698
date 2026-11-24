#include "dlt_698_mempool.h"
#include "dlt_698_parser_private.h"
#include <stddef.h>

/**
 * @brief 内存池分配的地址对齐粒度
 * @details 池内分配的结果结构体包含指针成员，每个分配块的起始地址必须满足自然对齐，
 *          否则对这些成员取址、赋值是未定义行为（x86 上 UBSan 报 store to misaligned address，
 *          Cortex-M0 等严格对齐内核会触发 UsageFault）。
 *          默认取 max_align_t 的对齐值；嵌入式平台可用 -DDLT_698_MEMPOOL_ALIGN=4 之类覆盖。
 */
#ifndef DLT_698_MEMPOOL_ALIGN
#define DLT_698_MEMPOOL_ALIGN ((mem_size_t)_Alignof(max_align_t))
#endif

/* 对齐粒度必须是 2 的幂，否则上取整公式不成立 */
_Static_assert((DLT_698_MEMPOOL_ALIGN & (DLT_698_MEMPOOL_ALIGN - 1)) == 0, "DLT_698_MEMPOOL_ALIGN must be a power of two");
_Static_assert(DLT_698_MEMPOOL_ALIGN > 0, "DLT_698_MEMPOOL_ALIGN must be positive");

/* 向上取整到对齐粒度的整数倍，结果为0表示发生回绕 */
static mem_size_t dlt_698_mempool_align_up(mem_size_t size)
{
    return (mem_size_t)((size + (DLT_698_MEMPOOL_ALIGN - 1)) / DLT_698_MEMPOOL_ALIGN * DLT_698_MEMPOOL_ALIGN);
}

int16_t dlt_698_mempool_init(dlt_698_mem_manage_t *mp, uint8_t *buf, mem_size_t total_mempool_size)
{
    // 合法性检查
    if (!mp || !buf)
    {
        return DLT_698_ERR_MEM;
    }
    // 起始地址向上取整到对齐边界，后续每块分配都在对齐地址上开始
    uintptr_t addr = (uintptr_t)buf;
    uintptr_t mask = (uintptr_t)(DLT_698_MEMPOOL_ALIGN - 1);
    uintptr_t aligned_addr = (addr + mask) & ~mask;
    mem_size_t lost = (mem_size_t)(aligned_addr - addr);
    if (lost >= total_mempool_size)
    {
        return DLT_698_ERR_MEM;
    }
    mp->start = (uint8_t *)aligned_addr;
    mp->total_mempool_size = (mem_size_t)(total_mempool_size - lost);
    mp->alloc_mempool_size = 0;
    return DLT_698_ERR_NONE;
}
void *dlt_698_mempool_alloc(dlt_698_mem_manage_t *mp, mem_size_t wantsize)
{
    if (!mp)
    {
        return NULL;
    }
    if (wantsize == 0)
    {
        return NULL;
    }
    if (mp->start == NULL)
    {
        return NULL;
    }
    // 分配长度整体向上取整，保证下一块的起始地址仍然对齐
    mem_size_t need = dlt_698_mempool_align_up(wantsize);
    if (need == 0) // 取整后回绕，申请长度超出可表达能力
    {
        return NULL;
    }
    if ((uint32_t)mp->alloc_mempool_size + need > (uint32_t)mp->total_mempool_size)
    {
        return NULL;
    }
    uint8_t *data = mp->start + mp->alloc_mempool_size;
    mp->alloc_mempool_size = (mem_size_t)(mp->alloc_mempool_size + need);

    return data;
}
void *RM_698_mempool_start(dlt_698_mem_manage_t *mp)
{
    return mp->start;
}
mem_size_t dlt_698_mempool_total_size(dlt_698_mem_manage_t *mp)
{
    return mp->total_mempool_size;
}
mem_size_t dlt_698_mempool_alloc_size(dlt_698_mem_manage_t *mp)
{
    return mp->alloc_mempool_size;
}
mem_size_t dlt_698_mempool_remain_size(dlt_698_mem_manage_t *mp)
{
    return mp->total_mempool_size - mp->alloc_mempool_size;
}
