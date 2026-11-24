/**
 * @file dlt_698_param_0x4004.h
 * @brief 设备地理坐标组帧
 * @details 设备地理坐标组帧
 * @date 2025-04-28
 * @version 1.0
 */
#ifndef DLT_698_PARAM_0x4004_H_
#define DLT_698_PARAM_0x4004_H_
#include "dlt_698_class.h"
#include "dlt_698_utl_tools.h"
#define DLT_698_PARAM_0x4004_OI 0x4004
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

    typedef struct DLT_698_PARAM_0x4004
    {
        /*属性1*/
        struct
        {
            uint8_t len;
            oop_octet_string data[64];
        } logic_name;
        /*属性2*/
        struct
        {
            struct
            {
                oop_enum dir;
                oop_unsigned degree;
                oop_unsigned minute;
                oop_unsigned second;
            } longitude;
            struct
            {
                oop_enum dir;
                oop_unsigned degree;
                oop_unsigned minute;
                oop_unsigned second;
            } latitude;
            oop_double_long_unsigned height;
        } coordinate;
    } dlt_698_param_0x4004_t;


    static inline int16_t dlt_698_param_0x4004_encode(dlt_698_param_0x4004_t *data, uint8_t att, uint8_t att_index, uint8_t att_len, uint8_t *des_ptr, uint16_t des_len)
    {
        struct Encode
        {
            /*属性1*/
            struct
            {
                oop_octet_string logic_name[66];
            } att_1;
            /*属性2*/
            struct
            {
                struct
                {
                    uint8_t type;
                    uint8_t cnt;
                    struct
                    {
                        uint8_t type;
                        uint8_t cnt;
                        uint8_t type_dir;
                        oop_enum dir;
                        uint8_t type_degree;
                        oop_unsigned degree;
                        uint8_t type_minute;
                        oop_unsigned minute;
                        uint8_t type_second;
                        oop_unsigned second;
                    } longitude;
                    struct
                    {
                        uint8_t type;
                        uint8_t cnt;
                        uint8_t type_dir;
                        oop_enum dir;
                        uint8_t type_degree;
                        oop_unsigned degree;
                        uint8_t type_minute;
                        oop_unsigned minute;
                        uint8_t type_second;
                        oop_unsigned second;
                    } latitude;
                    uint8_t type_height;
                    oop_double_long_unsigned height;
                } coordinate;
            } att_2;
        } apdu;


        /*属性1*/
        int16_t logic_name_len = dlt_698_encode_octet_string(data->logic_name.data, data->logic_name.len, true, apdu.att_1.logic_name, sizeof(apdu.att_1.logic_name));
        /*属性2*/
        apdu.att_2.coordinate.type = DLT_698_TYPE_OOP_STRUCT;
        apdu.att_2.coordinate.cnt = 3;
        apdu.att_2.coordinate.longitude.type = DLT_698_TYPE_OOP_STRUCT;
        apdu.att_2.coordinate.longitude.cnt = 4;
        apdu.att_2.coordinate.longitude.type_dir = DLT_698_TYPE_OOP_ENUM;
        apdu.att_2.coordinate.longitude.dir = data->coordinate.longitude.dir;
        apdu.att_2.coordinate.longitude.type_degree = DLT_698_TYPE_OOP_UNSIGNED;
        apdu.att_2.coordinate.longitude.degree = data->coordinate.longitude.degree;
        apdu.att_2.coordinate.longitude.type_minute = DLT_698_TYPE_OOP_UNSIGNED;
        apdu.att_2.coordinate.longitude.minute = data->coordinate.longitude.minute;
        apdu.att_2.coordinate.longitude.type_second = DLT_698_TYPE_OOP_UNSIGNED;
        apdu.att_2.coordinate.longitude.second = data->coordinate.longitude.second;
        apdu.att_2.coordinate.latitude.type = DLT_698_TYPE_OOP_STRUCT;
        apdu.att_2.coordinate.latitude.cnt = 4;
        apdu.att_2.coordinate.latitude.type_dir = DLT_698_TYPE_OOP_ENUM;
        apdu.att_2.coordinate.latitude.dir = data->coordinate.latitude.dir;
        apdu.att_2.coordinate.latitude.type_degree = DLT_698_TYPE_OOP_UNSIGNED;
        apdu.att_2.coordinate.latitude.degree = data->coordinate.latitude.degree;
        apdu.att_2.coordinate.latitude.type_minute = DLT_698_TYPE_OOP_UNSIGNED;
        apdu.att_2.coordinate.latitude.minute = data->coordinate.latitude.minute;
        apdu.att_2.coordinate.latitude.type_second = DLT_698_TYPE_OOP_UNSIGNED;
        apdu.att_2.coordinate.latitude.second = data->coordinate.latitude.second;
        apdu.att_2.coordinate.type_height = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
        dlt_698_big_endian(&apdu.att_2.coordinate.height, &data->coordinate.height, sizeof(data->coordinate.height));

        const struct DLT_698_CLASS_INFO dlt_698_class_tb[] = {
            {(uint16_t)(logic_name_len), 0, offsetof(struct Encode, att_1)},
            {(uint16_t)(sizeof(apdu.att_2)), 0, offsetof(struct Encode, att_2)},
        };
        return dlt_698_apdu_encoder(dlt_698_class_tb, &apdu, att, att_index, att_len, des_ptr, des_len);
    }

#pragma pack()
#ifdef __cplusplus
}
#endif
#endif