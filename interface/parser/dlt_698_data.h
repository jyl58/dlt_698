/**
 * @file dlt_698_data.h
 * @date 2025-03-12
 * @brief 定义通用数据类型
 * @details 定义数据类型
 */
#ifndef DLT_698_DATA_H_
#define DLT_698_DATA_H_
#include "dlt_698_type.h"
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

    /**
     * @brief 地址类型枚举定义
     */
    typedef enum DLT_698_ADDR_TYPE
    {
        DLT_698_ADDR_SINGLE = 0,    ///< [0]单地址
        DLT_698_ADDR_COMMON,        ///< [1]通配地址
        DLT_698_ADDR_GROUP,         ///< [2]组地址
        DLT_698_ADDR_BROADCAST      ///< [3]广播地址
    } dlt_698_addr_type_t;
    /**
     * @brief 数据帧地址信息
     */
    typedef struct DLT_698_ADDR
    {
        union
        {
            uint8_t val;    ///< 一个字节地址特征
            struct
            {
                uint8_t sa_len : 4;      ///< 地址长度
                uint8_t sa_logic : 2;    ///< 逻辑地址
                uint8_t sa_type : 2;     ///< 地址类型
            } st;
        } sa_feature;
        uint8_t ext;            ///< 扩展逻辑地址  1个字节
        uint8_t sa_addr[16];    ///< 服务器SA地址，最大16字节地址
        uint8_t ca;             ///< 客户机地址，1个字节
    } dlt_698_addr_t;

    /**
     * @brief 采用类似多叉树存储数据解析数据信息
     */
    typedef struct DLT_698_DATA
    {
        uint8_t type;            ///< 数据类型
        uint16_t index;          ///< 数据在数据帧中起始位置
        uint16_t len;            ///< 数据长度
        uint16_t child_index;    ///< 子节点索引下标，叶子节点为0
        uint16_t next_index;     ///< 兄弟节点索引下标，叶子节点为0
    } dlt_698_data_t;
    /**
     * @brief 读取结果
     * @note dar=0时正常，result_data数据；dar为其他值表示错误信息，result_data=NULL
     */
    struct DLT_698_Get_Result
    {
        uint8_t dar;                        ///< 错误信息
        dlt_698_data_t result_data;    ///< 数据
    };
    /**
     * @brief 对象属性及结果
     */
    struct DLT_698_Result_Normal
    {
        dlt_698_data_t oad;                      ///< 对象属性描述符
        struct DLT_698_Get_Result get_result;    ///< 读取结果
        uint16_t next_index;                          ///< 兄弟节点索引下标，叶子节点为0
    };


#pragma pack()
#ifdef __cplusplus
}
#endif
#endif
