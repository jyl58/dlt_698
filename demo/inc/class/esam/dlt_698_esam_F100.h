/**
 * @file dlt_698_esam_F100.h
 * @brief ESAM接口类组帧
 * @details ESAM接口类组帧
 * @date 2025-04-25
 * @version 1.0
 */
#ifndef DLT_698_ESAM_F100_H_
#define DLT_698_ESAM_F100_H_
#include "dlt_698_class.h"
#include "dlt_698_utl_tools.h"
#define DLT_698_ESAM_F100_OI F100
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

    typedef struct DLT_698_ESAM_F100
    {
        /*属性1*/
        struct
        {
            uint8_t len;
            oop_octet_string data[32];
        } logic_name;
        /*属性2*/
        struct
        {
            uint8_t len;
            oop_octet_string data[32];
        } seri_num;
        /*属性3*/
        struct
        {
            uint8_t len;
            oop_octet_string data[32];
        } esam_version;
        /*属性4*/
        struct
        {
            uint8_t len;
            oop_octet_string data[32];
        } key_version;
        /*属性5*/
        oop_double_long_unsigned talk_time_thr;
        /*属性6*/
        oop_double_long_unsigned talk_time_remain;
        /*属性7*/
        struct
        {
            oop_double_long_unsigned app_counter;
            oop_double_long_unsigned report_counter;
            oop_double_long_unsigned talk_num;
        } counter;
        /*属性8*/
        struct
        {
            struct
            {
                uint8_t len;
                oop_octet_string data[15];
            } terminal_version;
            struct
            {
                uint8_t len;
                oop_octet_string data[18];
            } primary_station_version;
        } certificate;
        /*属性9*/
        struct
        {
            uint8_t len;
            oop_octet_string data[20];
        } terminal_certificate_num;
        /*属性10*/
        struct
        {
            uint8_t len;
            oop_octet_string data[16];
        } terminal_certificate;
        /*属性11*/
        struct
        {
            uint8_t len;
            oop_octet_string data[23];
        } primary_station_num;
        /*属性12*/
        struct
        {
            uint8_t len;
            oop_octet_string data[5];
        } primary_station_certificate;
        /*属性13*/
        oop_oad esam_object[3];
        /*属性14*/
        oop_double_long_unsigned infrared_time_thr;
        /*属性15*/
        oop_double_long_unsigned infrared_time_remain;
    } dlt_698_esam_F100_t;


    static inline int16_t dlt_698_esam_F100_encode(dlt_698_esam_F100_t *data, uint8_t att, uint8_t att_index, uint8_t att_len, uint8_t *des_ptr, uint16_t des_len)
    {
        struct Encode
        {
            /*属性1*/
            struct
            {
                oop_octet_string logic_name[35];
            } att_1;
            /*属性2*/
            struct
            {
                oop_octet_string seri_num[35];
            } att_2;
            /*属性3*/
            struct
            {
                oop_octet_string esam_version[35];
            } att_3;
            /*属性4*/
            struct
            {
                oop_octet_string key_version[35];
            } att_4;
            /*属性5*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_double_long_unsigned value;
                } talk_time_thr;
            } att_5;
            /*属性6*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_double_long_unsigned value;
                } talk_time_remain;
            } att_6;
            /*属性7*/
            struct
            {
                struct
                {
                    uint8_t type;
                    uint8_t cnt;
                    uint8_t type_app_counter;
                    oop_double_long_unsigned app_counter;
                    uint8_t type_report_counter;
                    oop_double_long_unsigned report_counter;
                    uint8_t type_talk_num;
                    oop_double_long_unsigned talk_num;
                } counter;
            } att_7;
            /*属性8*/
            struct
            {
                uint8_t type;
                uint8_t cnt;
                oop_octet_string certificate[41];
            } att_8;
            /*属性9*/
            struct
            {
                oop_octet_string terminal_certificate_num[4];
            } att_9;
            /*属性10*/
            struct
            {
                oop_octet_string terminal_certificate[19];
            } att_10;
            /*属性11*/
            struct
            {
                oop_octet_string primary_station_num[26];
            } att_11;
            /*属性12*/
            struct
            {
                oop_octet_string primary_station_certificate[8];
            } att_12;
            /*属性13*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_oad value;
                } esam_object[3];
            } att_13;
            /*属性14*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_double_long_unsigned value;
                } infrared_time_thr;
            } att_14;
            /*属性15*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_double_long_unsigned value;
                } infrared_time_remain;
            } att_15;
        } apdu;


        /*属性1*/
        int16_t logic_name_len = dlt_698_encode_octet_string(data->logic_name.data, data->logic_name.len, true, apdu.att_1.logic_name, sizeof(apdu.att_1.logic_name));
        /*属性2*/
        int16_t seri_num_len = dlt_698_encode_octet_string(data->seri_num.data, data->seri_num.len, true, apdu.att_2.seri_num, sizeof(apdu.att_2.seri_num));
        /*属性3*/
        int16_t esam_version_len = dlt_698_encode_octet_string(data->esam_version.data, data->esam_version.len, true, apdu.att_3.esam_version, sizeof(apdu.att_3.esam_version));
        /*属性4*/
        int16_t key_version_len = dlt_698_encode_octet_string(data->key_version.data, data->key_version.len, true, apdu.att_4.key_version, sizeof(apdu.att_4.key_version));
        /*属性5*/
        apdu.att_5.talk_time_thr.type = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
        dlt_698_big_endian(&apdu.att_5.talk_time_thr.value, &data->talk_time_thr, sizeof(data->talk_time_thr));
        /*属性6*/
        apdu.att_6.talk_time_remain.type = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
        dlt_698_big_endian(&apdu.att_6.talk_time_remain.value, &data->talk_time_remain, sizeof(data->talk_time_remain));
        /*属性7*/
        apdu.att_7.counter.type = DLT_698_TYPE_OOP_STRUCT;
        apdu.att_7.counter.cnt = 3;
        apdu.att_7.counter.type_app_counter = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
        dlt_698_big_endian(&apdu.att_7.counter.app_counter, &data->counter.app_counter, sizeof(data->counter.app_counter));
        apdu.att_7.counter.type_report_counter = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
        dlt_698_big_endian(&apdu.att_7.counter.report_counter, &data->counter.report_counter, sizeof(data->counter.report_counter));
        apdu.att_7.counter.type_talk_num = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
        dlt_698_big_endian(&apdu.att_7.counter.talk_num, &data->counter.talk_num, sizeof(data->counter.talk_num));
        /*属性8*/
        apdu.att_8.type = DLT_698_TYPE_OOP_STRUCT;
        apdu.att_8.cnt = 2;
        int16_t start = 1;
        int16_t terminal_version_len =
            dlt_698_encode_octet_string(data->certificate.terminal_version.data, data->certificate.terminal_version.len, true, apdu.att_8.certificate + start, sizeof(apdu.att_8.certificate) - start);
        int16_t primary_station_version_len = dlt_698_encode_octet_string(data->certificate.primary_station_version.data, data->certificate.primary_station_version.len, true,
                                                                      apdu.att_8.certificate + start + terminal_version_len, sizeof(apdu.att_8.certificate) - start - terminal_version_len);
        int16_t certificate_len = start + terminal_version_len + primary_station_version_len;
        /*属性9*/
        int16_t terminal_certificate_num_len = dlt_698_encode_octet_string(data->terminal_certificate_num.data, data->terminal_certificate_num.len, true, apdu.att_9.terminal_certificate_num,
                                                                       sizeof(apdu.att_9.terminal_certificate_num));
        /*属性10*/
        int16_t terminal_certificate_len =
            dlt_698_encode_octet_string(data->terminal_certificate.data, data->terminal_certificate.len, true, apdu.att_10.terminal_certificate, sizeof(apdu.att_10.terminal_certificate));
        /*属性11*/
        int16_t primary_station_num_len =
            dlt_698_encode_octet_string(data->primary_station_num.data, data->primary_station_num.len, true, apdu.att_11.primary_station_num, sizeof(apdu.att_11.primary_station_num));
        /*属性12*/
        int16_t primary_station_certificate_len = dlt_698_encode_octet_string(data->primary_station_certificate.data, data->primary_station_certificate.len, true, apdu.att_12.primary_station_certificate,
                                                                          sizeof(apdu.att_12.primary_station_certificate));
        /*属性13*/
        for (int i = 0; i < 3; i++)
        {
            apdu.att_13.esam_object[i].type = DLT_698_TYPE_OOP_OAD;
            apdu.att_13.esam_object[i].value = data->esam_object[i];
            dlt_698_big_endian(&apdu.att_13.esam_object[i].value, &data->esam_object[i], sizeof(data->esam_object[i]));
        }
        /*属性14*/
        apdu.att_14.infrared_time_thr.type = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
        dlt_698_big_endian(&apdu.att_14.infrared_time_thr.value, &data->infrared_time_thr, sizeof(data->infrared_time_thr));
        /*属性15*/
        apdu.att_15.infrared_time_remain.type = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
        dlt_698_big_endian(&apdu.att_15.infrared_time_remain.value, &data->infrared_time_remain, sizeof(data->infrared_time_remain));

        const struct DLT_698_CLASS_INFO dlt_698_class_tb[] = {
            {logic_name_len, 0, offsetof(struct Encode, att_1)},
            {seri_num_len, 0, offsetof(struct Encode, att_2)},
            {esam_version_len, 0, offsetof(struct Encode, att_3)},
            {key_version_len, 0, offsetof(struct Encode, att_4)},
            {sizeof(apdu.att_5), 0, offsetof(struct Encode, att_5)},
            {sizeof(apdu.att_6), 0, offsetof(struct Encode, att_6)},
            {sizeof(apdu.att_7), 0, offsetof(struct Encode, att_7)},
            {certificate_len, 0, offsetof(struct Encode, att_8)},
            {terminal_certificate_num_len, 0, offsetof(struct Encode, att_9)},
            {terminal_certificate_len, 0, offsetof(struct Encode, att_10)},
            {primary_station_num_len, 0, offsetof(struct Encode, att_11)},
            {primary_station_certificate_len, 0, offsetof(struct Encode, att_12)},
            {sizeof(apdu.att_13.esam_object[0]), 3, offsetof(struct Encode, att_13)},
            {sizeof(apdu.att_14), 0, offsetof(struct Encode, att_14)},
            {sizeof(apdu.att_15), 0, offsetof(struct Encode, att_15)},
        };
        return dlt_698_apdu_encoder(dlt_698_class_tb, &apdu, att, att_index, att_len, des_ptr, des_len);
    }

#pragma pack()
#ifdef __cplusplus
}
#endif
#endif