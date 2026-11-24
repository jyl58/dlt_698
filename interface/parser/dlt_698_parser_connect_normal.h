/**
 * @file dlt_698_parser_connect_normal.h
 * @date 2025-03-12
 * @brief 定义应用连接相关数据类型
 * @details 定义数据类型
 */
#ifndef DLT_698_PARSER_CONNECT_NORMAL_H_
#define DLT_698_PARSER_CONNECT_NORMAL_H_
#include "dlt_698_parser.h"
#include "dlt_698_type.h"
#include "dlt_698_data.h"
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

    /**
     * @brief 一般密码
     */
    struct DLT_698_Password_Security
    {
        dlt_698_data_t security;    ///< visible-string
    };
    /**
     * @brief 对称加密
     */
    struct DLT_698_Symmetry_Security
    {
        dlt_698_data_t ciphertext;    ///< 密文1 octet-string
        dlt_698_data_t signature;     ///< 客户机签名1 octet-string
    };
    /**
     * @brief 数字签名
     */
    struct DLT_698_Signature_Security
    {
        dlt_698_data_t ciphertext;    ///< 密文2 octet-string
        dlt_698_data_t signature;     ///< 客户机签名2 octet-string
    };
    /**
     * @brief 请求建立应用连接（CONNECT-Request）的数据类型
     * @note 用于CONNECT-Request(02)数据解析
     */
    struct DLT_698_CONN_REQ
    {
        uint16_t protocol_version;          ///< 期望的协议版本号 long-unsigned
        uint8_t protocol_conform[8];        ///< 期望的协议一致性块 ProtocolConformance bit-string（SIZE（64））
        uint8_t function_conform[16];       ///< 期望的功能一致性块 FunctionConformance bit-string（SIZE（128））
        uint16_t frame_send_max_size;       ///< 客户机发送帧最大尺寸 long-unsigned
        uint16_t frame_recv_max_size;       ///< 客户机接收帧最大尺寸 long-unsigned
        uint8_t frame_recv_max_wnd_size;    ///< 客户机接收帧最大窗口尺寸 unsigned
        uint16_t frame_handle_max_size;     ///< 客户机最大可处理帧尺寸 long-unsigned
        uint32_t connect_timeout;           ///< 期望的应用连接超时时间 double-long-unsigned
        uint8_t sec_choice;                 ///< 认证请求对象选择
        union                          ///< 认证请求对象 ConnectMechanismInfo
        {
            dlt_698_data_t null_data;                       ///< [0]公共连接 NullSecurity
            struct DLT_698_Password_Security password;      ///< [1]一般密码 PasswordSecurity
            struct DLT_698_Symmetry_Security symmetry;      ///< [2]对称加密 SymmetrySecurity
            struct DLT_698_Signature_Security signature;    ///< [3]数字签名 SignatureSecurity
        } security;
    };

    /**
     * @brief  服务器签名
     */
    struct DLT_698_Security_Data
    {
        dlt_698_data_t RN;      ///< 服务器随机数RN
        dlt_698_data_t info;    ///< 服务器签名信息 octet-string
    };
    /**
     * @brief RSA公钥
     */
    struct DLT_698_RSA_Public_Key
    {
        dlt_698_data_t modulus;    ///< 模数
        dlt_698_data_t key;        ///< 公钥
    };
    /**
     * @brief 连接响应对象
     */
    struct DLT_698_Connect_Response_Info
    {
        uint8_t connect_result;    ///< 认证结果
        uint8_t optional;          ///< 数据类型
        union
        {
            dlt_698_data_t *null_data;                     ///< NULL
            struct DLT_698_Security_Data *sec_data;        ///<  服务器签名
            struct DLT_698_RSA_Public_Key *rsa_pub_key;    ///< RSA公钥
        } verify;
    };
    /**
     * @brief 服务器厂商版本信息
     */
    struct DLT_698_Factory_Version
    {
        uint8_t factory_code[4];         ///< 厂商代码 visible-string(SIZE(4))
        uint8_t software_version[4];     ///< 软件版本号 visible-string(SIZE(4))，
        uint8_t software_date[6];        ///< 软件版本日期 visible-string(SIZE(6))，
        uint8_t hardware_version[4];     ///< 硬件版本号 visible-string(SIZE(4))，
        uint8_t hardware_date[6];        ///< 硬件版本日期   visible-string(SIZE(6))，
        uint8_t factory_extension[8];    ///< 厂商扩展信息   visible-string(SIZE(8))
    };
    /**
     * @brief 建立应用连接响应（CONNECT-Response）
     * @note 用于CONNECT-Response(82)数据解析
     */
    struct DLT_698_CONN_RES
    {
        struct DLT_698_Factory_Version factory_verison;    ///< 服务器厂商版本信息 FactoryVersion
        uint16_t protocol_version;                              ///< 商定的协议版本号 long-unsigned
        uint8_t protocol_conform[8];                            ///< 商定的协议一致性块 ProtocolConformance
        uint8_t function_conform[16];                           ///< 商定的功能一致性块 FunctionConformance
        uint16_t frame_send_max_size;                           ///< 服务器发送帧最大尺寸 long-unsigned
        uint16_t frame_recv_max_size;                           ///< 服务器接收帧最大尺寸 long-unsigned
        uint8_t frame_recv_max_wnd_size;                        ///< 服务器接收帧最大窗口尺寸 unsigned
        uint16_t frame_handle_max_size;                         ///< 服务器最大可<处理帧尺寸 long-unsigned
        uint32_t connect_timeout;                               ///< 商定的应用连接超时时间 double-long-unsigned
        struct DLT_698_Connect_Response_Info res_info;     ///< 连接响应对象 ConnectResponseInfo
    };
    /**
     * @brief 断开应用连接响应（RELEASE-Response）
     * @note 用于RELEASE-Response(82)数据解析
     */
    struct DLT_698_REL_RES
    {
        uint8_t result;    ///< 结果
    };

    /**
     * @brief 断开应用连接通知（RELEASE-Notification）
     * @note 用于RELEASE-Notification(83)数据解析
     */
    struct DLT_698_REL_NTF
    {
        dlt_698_data_t link_dt;    ///< 应用连接建立时间 date_time_s
        dlt_698_data_t cur_dt;     ///< 务器当前时间 date_time_s
    };

#pragma pack()
#ifdef __cplusplus
}
#endif

#endif