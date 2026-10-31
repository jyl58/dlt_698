/**
 * @file dlt_698_parser_get_next.h
 * @date 2025-03-12
 * @brief 请求和响应读取分帧传输的下一帧
 * @details 定义数据类型
 */

#ifndef DLT_698_PARSER_GET_NEXT_H_
#define DLT_698_PARSER_GET_NEXT_H_
#include "dlt_698_data.h"
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)


    /**
     * @brief 请求读取分帧传输的下一帧
     * @note 用于GetRequestNext(05 05)数据解析
     */
    struct DLT_698_GET_NEXT_REQ
    {
        uint16_t last_frame;    ///< 已接收的最后分帧序号
    };

    /**
     * @brief 读取分帧传输的下一帧的响应
     * @note 用于GetResponseNext(85 05)数据解析
     */
    struct DLT_698_GET_NEXT_RES
    {
        uint8_t is_end;         ///< 末帧标志
        uint16_t frame_num;     ///< 分帧序号
        uint8_t data_choice;    ///< 分帧响应数据选择
        union
        {
            uint8_t dar;                                      ///< [0]DAR
            struct DLT_698_Result_Normal *normal_ptr;    ///< [1]SEQUENCE OF A-ResultNormal，
            struct DLT_698_RESULT_RECORD *record_ptr;    ///< [2]SEQUENCE OF A-ResultRecord
        } next_data;
    };


#pragma pack()
#ifdef __cplusplus
}
#endif

#endif