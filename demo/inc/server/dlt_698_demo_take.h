/**
 * @file dlt_698_demo_take.h
 * @date 2026-11-24
 * @brief DL/T 698 字段提取示例
 * @details 演示解析完成后如何使用 dlt_698_take_* / dlt_698_get_* 系列接口,
 *          把帧头字段和 APDU 内各数据字段的值逐个提取出来。
 */
#ifndef DLT_698_DEMO_TAKE_H_
#define DLT_698_DEMO_TAKE_H_

#include "dlt_698_parser.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief 提取并打印帧头字段(帧类型/控制码/地址/PIID/时间标签/APDU等)
     * @param parser 698解析器实例
     */
    void demo_take_frame_fields(dlt_698_parser *parser);

    /**
     * @brief 提取并打印 APDU 内各数据字段的值
     * @details 根据 dlt_698_take_apdu_info_head 拿到解析结果结构头指针,
     *          再用 dlt_698_get_* 按数据类型取值。
     *          支持 GET-Request/GET-Response/SET-Request/SET-Response 的 normal 及 normal list。
     * @param parser 698解析器实例
     */
    void demo_take_apdu_fields(dlt_698_parser *parser);

#ifdef __cplusplus
}
#endif

#endif
