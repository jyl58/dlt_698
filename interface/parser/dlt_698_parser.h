/**
 * @file dlt_698_parser.h
 * @date 2025-03-12
 * @brief 定义解析器相关信息
 * @details 定义解析器相关信息
 */
#ifndef DLT_698_PARSER_H_
#define DLT_698_PARSER_H_
#include "dlt_698_type.h"
#include "dlt_698_data.h"
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)


    typedef struct DLT_698_PARSER dlt_698_parser;
/*基于以上定义
DIR    PRM    组合意义
0    0    客户机对服务器上报的响应
0    1    客户机发起的请求
1    0    服务器发起的上报
1    1    服务器对客户机请求的响应
*/
//! 传输方向DIR：客户机发出
#define DLT_698_FROM_CLIENT (0 << 7)
//! 传输方向DIR：服务器发出
#define DLT_698_FROM_SERVER (1 << 7)

//! 启动标志PRM：交互由客户机发起
#define DLT_698_CLIENT_LAUNCH (1 << 6)
//! 启动标志PRM：交互由服务器发起
#define DLT_698_SERVER_LAUNCH (0 << 6)

//! 分帧标志：有分帧
#define DLT_698_SUBFRAME_YES (1 << 5)
//! 分帧标志：无分帧
#define DLT_698_SUBFRAME_NO (0 << 5)
/*扰码标志位: bit3=0，表示此帧链路用户数据不加扰码；
bit3=1，表示此帧链路用户数据加扰码，发送时链路用户数据按字节加33H。
*/
//! 扰码标志：加扰
#define DLT_698_DISTURB_YES (1 << 3)
//! 扰码标志：不加扰
#define DLT_698_DISTURB_NO (0 << 3)
    /**
     * @brief 698帧功能码枚举
     */
    enum DLT_698_FRAME_FUN
    {
        RM_698_FRAME_FUN_0 = 0,    ///< 功能码0，保留
        RM_698_FRAME_FUN_1,        ///< 功能码1，链路管理，链路连接管理（登录，心跳，退出登录）
        RM_698_FRAME_FUN_2,        ///< 功能码2，保留
        RM_698_FRAME_FUN_3,        ///< 功能码3，用户数据，应用连接管理及数据交换服务
        RM_698_FRAME_FUN_4,        ///< 功能码4，保留
    };
    /**
     * @brief 698帧类型枚举
     */
    enum DLT_698_FRAME_TYPE
    {
        DLT_698_FRAME_TYPE_LINK_REQ = 0x01,    ///< LINK请求
        DLT_698_FRAME_TYPE_LINK_RES = 0x81,    ///< LINK响应
        DLT_698_FRAME_TYPE_CONN_REQ = 0x02,    ///< CONNECT请求
        DLT_698_FRAME_TYPE_CONN_RES = 0x82,    ///< CONNECT响应
        DLT_698_FRAME_TYPE_REL_REQ = 0x03,     ///< RELEASE请求
        DLT_698_FRAME_TYPE_REL_RES = 0x83,     ///< RELEASE响应
        DLT_698_FRAME_TYPE_REL_NTY = 0x84,     ///< RELEASE通知
        DLT_698_FRAME_TYPE_GET_REQ = 0x05,     ///< GET请求
        DLT_698_FRAME_TYPE_GET_RES = 0x85,     ///< GET响应
        DLT_698_FRAME_TYPE_SET_REQ = 0X06,     ///< SET请求
        DLT_698_FRAME_TYPE_SET_RES = 0X86,     ///< SET响应
        DLT_698_FRAME_TYPE_ACT_REQ = 0X07,     ///< ACT请求
        DLT_698_FRAME_TYPE_ACT_RES = 0X87,     ///< ACT响应
        DLT_698_FRAME_TYPE_REP_REQ = 0X88,     ///< 上报请求
        DLT_698_FRAME_TYPE_REP_RES = 0X08,     ///< 上报响应
        DLT_698_FRAME_TYPE_SEC_REQ = 0X10,     ///< 安全请求
        DLT_698_FRAME_TYPE_SEC_RES = 0X90,     ///< 安全响应
    };
    /**
     * @brief 请求读取（GET-Request）或响应读取（GET-Response）的数据类型定义
     */
    enum DLT_698_GET_METHOD
    {
        DLT_698_GET_METHOD_NOR = 1,        ///< [1]GetRequestNormal/GetResponseNormal
        DLT_698_GET_METHOD_NOR_LIST,       ///< [2]GetRequestNormalList/GetResponseNormalList
        DLT_698_GET_METHOD_RECORD,         ///< [3]GetRequestRecord/GetResponseRecord
        DLT_698_GET_METHOD_RECORD_LIST,    ///< [4]GetRequestRecordList/GetResponseRecordList
        DLT_698_GET_METHOD_NEXT,           ///< [5]GetRequestNext/GetResponseNext
        DLT_698_GET_METHOD_MD5             ///< [6]GetRequestMD5/GetResponseMD5
    };
    /**
     * @brief 设置请求（SET-Request）或响应设置（SET-Response）的数据类型定义
     */
    enum DLT_698_SET_METHOD
    {
        DLT_698_SET_METHOD_NOR = 1,         ///< [1]SetRequestNormal/SetResponseNormal
        DLT_698_SET_METHOD_NOR_LIST,        ///< [2]SetRequestNormalList/SetResponseNormalList
        DLT_698_SET_METHOD_SET_GET_LIST,    ///< [3]SetThenGetRequestNormalList/SetThenGetResponseNormalList
    };
    /**
     * @brief 请求操作（ACTION-Request）或响应操作（ACTION-Response）的数据类型定义
     */
    enum DLT_698_ACT_METHOD
    {
        DLT_698_ACT_METHOD_NOR = 1,         ///< [1]ActionRequestNormal/ActionResponseNormal
        DLT_698_ACT_METHOD_NOR_LIST,        ///< [2]ActionRequestNormalList/ActionResponseNormalList
        DLT_698_ACT_METHOD_SET_GET_LIST,    ///< [3]ActionThenGetRequestNormalList/ActionThenGetResponseNormalList
    };
    /**
     * @brief 通知上报（REPORT-Notification）响应上报（REPORT-Response）的数据类型定义
     */
    enum DLT_698_REP_METHOD
    {
        DLT_698_REP_METHOD_NOTIFY_LIST = 1,       ///< [1]ReportNotificationList/ReportResponseList
        DLT_698_REP_METHOD_NOTIFY_RECORD_LIST,    ///< [2]ReportResponseRecordList/ReportResponseRecordList
        DLT_698_REP_METHOD_NOTIFY_TRANS,          ///< [3]ReportNotificationTransData/ReportResponseTransData
    };

    /**
     * @brief 定义解析后回调函数指针
     * @details 初始化解析器
     * @param parser 698解析器实例指针
     * @return 无
     */
    typedef void (*dlt_698_cb)(dlt_698_parser *parser);

    /**
     * @brief 698 解析器实例结构
     * @note _fun:数据处理函数，应用层提供
     * _buf:应用层传入的缓存，用于存放帧载荷数据及中间数据变量
     * |-------------|--------------|
     * |   载荷数据   |   解析状态量  |
     * |-------------|--------------|
     * _ins:解析器私有指针，应用层无需配置
     */
    typedef struct DLT_698_PARSER
    {
        dlt_698_cb _fun;         ///< 数据解析完成之后调用的函数，由应用层提供
        uint8_t *_buf;                ///< 解析有效载荷缓存，由应用层声明/申请并传入
        uint32_t _buf_size;           ///< 应用层传入的buf大小
        dlt_698_addr_t _addr;    ///< 交互通信地址相关信息
        void *_ins;              ///< 解析器内部实例指针，应用层无需改动
    } dlt_698_parser;

    /**
     * @brief 获取解析器版本号信息
     * @details 获取解析器版本号信息
     * @return 返回版本号字符串信息
     */
    const char *dlt_698_parser_version();
    /**
     * @brief 创建并初始化698解析器实例
     * @details 初始化解析器。实例池固定为 DLT_698_PARSER_MAX_COUNT(4) 个，用完即
     *          init 失败；同一个 parser 重复 init 会复用其已占用的池槽位，不会重复占用，
     *          并且解析中间状态被复位（已收到的半帧被丢弃）。
     * @param parser 698解析器实例指针
     * @return DLT_698_ERR_NONE 成功；
     *         DLT_698_ERR_EMPTY_PTR(-3) parser 为空或 buff_size 为 0；
     *         DLT_698_ERR_CREAT(-2) 实例池已满
     */
    int16_t dlt_698_parser_init(dlt_698_parser *parser, dlt_698_addr_t addr, uint8_t *buff, uint16_t buff_size, dlt_698_cb cb);
    /**
     * @brief 释放698解析器实例
     * @details 归还实例池槽位，之后该 parser 上的 parse/parse_frame/set_timeout_ms
     *          都返回 DLT_698_ERR_EMPTY_PTR(-3)。可重复调用。
     * @param parser 698解析器实例指针
     * @return DLT_698_ERR_NONE 成功；
     *         DLT_698_ERR_EMPTY_PTR(-3) parser 为空、未初始化或已释放
     */
    int16_t dlt_698_parser_delete(dlt_698_parser *parser);
    /**
     * @brief 698解析器整帧报文解析
     * @details 按"一整帧"解析：frame 前面的杂字节会被跳过；解出一帧后立即返回，
     *          frame 中剩余字节(如同一包内的第二帧)被丢弃。
     *          无论解出与否，返回前都把内部状态复位到帧头，退出后实例可直接继续
     *          逐字节喂入 dlt_698_parse()，不会残留半帧。
     *          需要处理一包多帧或分块收数据时，请直接逐字节调用 dlt_698_parse()。
     * @param parser 解析器
     * @param frame 整帧报文缓冲区
     * @param len 整帧报文大小
     * @return DLT_698_ERR_NONE 解出一个完整帧；
     *         DLT_698_ERR_PARSE(-5) 这 len 字节中未解出完整帧(数据不完整或帧头/帧校验不符)，
     *         该值不代表报文内容解析失败；
     *         DLT_698_ERR_EMPTY_PTR(-3) 解析器未初始化
     */
    int16_t dlt_698_parse_frame(dlt_698_parser *parser, uint8_t *frame, uint16_t len);
    /**
     * @brief 698解析器执行函数
     * @details 按字节解析数据
     * @param parser 解析器
     * @param c 单字节数据
     * @return DLT_698_ERR_PARSING(-1) 帧未收完(正常中间态)；
     *         DLT_698_ERR_NONE(0) 收完一帧并解析成功(已回调)；
     *         其余负值为错误帧(见 enum FDLT_698_ERR)；
     *         DLT_698_ERR_EMPTY_PTR(-3) 解析器未初始化或已释放
     */
    int16_t dlt_698_parse(dlt_698_parser *parser, uint8_t c);
    /**
     * @brief 698组帧函数
     * @details 组帧。长度参数与返回值统一用 int32_t，避免 int16_t 在 32767 处截断。
     *          本库单帧上限为 65535 字节(含4个前导符与16H，数据域相应最多 65529 字节)：
     *          解析侧的长度入参与缓冲区下标都是 uint16_t，更长的帧本库无法回读，
     *          因此超过上限直接返回错误，不做截断。
     * @param parser 解析器
     * @param ctrl 控制码
     * @param apdu_ptr APDU数据
     * @param apdu_len APDU字节数(>0)
     * @param des_ptr 整帧存储起始指针
     * @param des_len 存储区大小(字节)
     * @return 成功返回写入的整帧字节数；
     *         DLT_698_ERR_EMPTY_PTR(-3) 空指针或 apdu_len<=0；
     *         DLT_698_ERR_LEN(-12) 无服务器地址却要求扩展逻辑地址；
     *         DLT_698_ERR_OVER(-8) 整帧超过 65535 字节，或 des_len 不足
     */
    int32_t dlt_698_encode(dlt_698_parser *parser, uint8_t ctrl, uint8_t *apdu_ptr, int32_t apdu_len, uint8_t *des_ptr, int32_t des_len);
    /**
     * @brief 接收数据之间的时间阈值，超过阈值重新过滤数据
     * @details 数据过滤
     * @param parser 解析器
     * @param ms 时间阈值(单位：毫秒)
     * @return DLT_698_ERR_NONE 成功；
     *         DLT_698_ERR_EMPTY_PTR(-3) parser 为空、未初始化或已释放
     */
    int16_t dlt_698_set_timeout_ms(dlt_698_parser *parser, uint16_t ms);
    /**
     * @brief 地址域初始化
     * @details 地址域初始化。服务器地址长度受 4bit 长度域限制：
     *          无扩展逻辑地址(sa_logic<=1)支持 1~16 字节；
     *          有扩展逻辑地址(sa_logic>1)支持 1~15 字节。
     * @param addr_info 地址域信息
     * @param sa 服务器地址(十六进制字符串，最长32个字符=16字节)
     * @param sa_logic 逻辑地址
     * @param ca 客户机地址
     * @return DLT_698_ERR_NONE 成功；
     *         DLT_698_ERR_EMPTY_PTR(-3) addr_info 或 sa 为空指针；
     *         DLT_698_ERR_LEN(-12) 地址为空、超过16字节，或超过15字节却要求扩展逻辑地址
     */
    int16_t dlt_698_addr_init(dlt_698_addr_t *addr_info, const char *sa, uint8_t sa_logic, uint8_t ca);
    /**
     * @brief 地址域初始化
     * @details 地址域初始化
     * @param addr_info 地址域信息
     * @param group 是否为组地址 0:否 1:是
     * @note  初始化地址后调用
     * @return 无
     */
    void dlt_698_set_addr_group(dlt_698_addr_t *addr_info, uint8_t group);
    /**
     * @brief 将16进制字符串转换为16进制数组
     * @details 16进制字符串转16进制数组
     * @param srcString 16进制字符串
     * @param grarrayoup 16进制数组
     * @return 无
     */
    int dlt_698_string_hex(const char *src_string, unsigned char *array);

#pragma pack()

#ifdef __cplusplus
}
#endif
#endif