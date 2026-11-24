/**
 * @file dlt_698_parser_security_normal.h
 * @date 2025-03-12
 * @brief 请求和响应安全传输
 * @details 定义数据类型
 */
#ifndef DLT_698_PARSER_SECURITY_NORMAL_H_
#define DLT_698_PARSER_SECURITY_NORMAL_H_
#include "dlt_698_type.h"
#include "dlt_698_data.h"
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

    /*698安全传输类型*/
    enum DLT_698_SEC_TYPE
    {
        DLT_698_SEC_COMMON = 0,    ///< 普通数据传输
        DLT_698_SEC_REQ,           ///< 安全请求
        DLT_698_SEC_RES,           ///< 安全响应
    };
    /**
     * @brief RN_MAC
     */
    struct DLT_698_SEC_RN_MAC
    {
        dlt_698_data_t RN;     ///< 随机数 RN
        dlt_698_data_t MAC;    ///< 消息认证码 MAC
    };
    /**
     * @brief 请求安全传输数据类型
     */
    struct DLT_698_SEC_REQ
    {
        uint8_t apdu_type;                ///< 应用数据单元类型  0 明文 1 密文
        dlt_698_data_t apdu_data;    ///< 明文/密文应用单元数据
        uint8_t verify_type;              ///< 数据验证信息类型
        union
        {
            dlt_698_data_t SID_MAC;              ///< [0]数据验证码 SID_MAC，
            dlt_698_data_t RN;                   ///< [1]随机数 RN
            struct DLT_698_SEC_RN_MAC RN_MAC;    ///< [2]随机数+MAC RN_MAC
            dlt_698_data_t SID;                  ///< [3]安全标识 SID
        } verify;
    };
    /**
     * @brief 数据验证信息
     */
    struct DLT_698_VERIFY_INFO
    {
        uint8_t verify_type;    ///< 数据验证信息类型
        union
        {
            dlt_698_data_t MAC;    ///< [0]数据MAC
        } verify_data;
    };
    /**
     * @brief 响应安全传输数据类型
     */
    struct DLT_698_SEC_RES
    {
        uint8_t apdu_type;    ///< 应用数据单元类型 0 明文 1 密文 2 错误码
        union
        {
            uint8_t dar;                      ///< 错误码
            dlt_698_data_t apdu_data;    ///< 明文/密文应用单元数据
        } apdu;

        struct DLT_698_VERIFY_INFO *verify_ptr;    ///< 数据验证信息
    };

#pragma pack()
#ifdef __cplusplus
}
#endif

#endif    // DLT_698_PARSER_SECURITY_NORMAL_H_