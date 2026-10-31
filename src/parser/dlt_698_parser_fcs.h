/**
 * 698规范里的校验和实现
 * 作者：王军
 * 时间：2024.11.05
 */
#ifndef DLT_698_PARSER_FCS_H_
#define DLT_698_PARSER_FCS_H_
#include "dlt_698_type.h"
#include "dlt_698_parser_private.h"
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)
    // extern const  uint16_t fcstab[256];
    /**
     * 边解析边计算校验和时的初始化
     * 返回值：异常值见枚举
     */
    int16_t dlt_698_fcs_init(struct DLT_698_PRIVATE *ins);
    /**
     * 698规范里的校验和计算方案
     * 该函数随着字节解析计算校验和
     */
    void dlt_698_fcs_16(struct DLT_698_PRIVATE *ins, uint8_t c);

    uint16_t dlt_698_fcs_16_block(uint8_t *cp, uint16_t len);
#pragma pack()
#ifdef __cplusplus
}
#endif
#endif