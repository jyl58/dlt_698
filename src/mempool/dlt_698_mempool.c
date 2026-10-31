#include "dlt_698_mempool.h"
#include "dlt_698_parser_private.h"

int16_t dlt_698_mempool_init(dlt_698_mem_manage_t *mp, uint8_t *buf, mem_size_t total_mempool_size)
{
    // 合法性检查
    if (!mp || !buf)
    {
        return DLT_698_ERR_MEM;
    }
    mp->start = buf;
    mp->total_mempool_size = total_mempool_size;
    mp->alloc_mempool_size = 0;
    return DLT_698_ERR_NONE;
}
void *dlt_698_mempool_alloc(dlt_698_mem_manage_t *mp, mem_size_t wantsize)
{
    if (!mp)
    {
        return NULL;
    }
    if (wantsize <= 0)
    {
        return NULL;
    }
    if (mp->start == NULL)
    {
        return NULL;
    }
    if (mp->alloc_mempool_size + wantsize > mp->total_mempool_size)
    {
        return NULL;
    }
    uint8_t *data = mp->start + mp->alloc_mempool_size;
    mp->alloc_mempool_size += wantsize;

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
