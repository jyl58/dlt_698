/**
 * @file dlt_698_harmonic_0x200d.h
 * @brief 谐波变量类组帧
 * @details 谐波变量类组帧
 * @date 2025-04-25
 * @version 1.0
 */
#ifndef DLT_698_HARMONIC_0x200d_H_
#define DLT_698_HARMONIC_0x200d_H_
#include "dlt_698_class.h"
#include "dlt_698_utl_tools.h"
#define DLT_698_HARMONIC_0x200d_OI 0x200d
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

    typedef struct DLT_698_HARMONIC_0x200d
    {
        /*属性1*/
        struct
        {
            uint8_t len;
            oop_octet_string data[64];
        } logic_name;
        /*属性2*/
        oop_long harm_A[56];
        /*属性3*/
        oop_long harm_B[56];
        /*属性4*/
        oop_long harm_C[56];
        /*属性5*/
        oop_unsigned max_harm;
        /*属性6*/
        oop_scaler_unit su_std;
    } dlt_698_harmonic_0x200d_t;


    static inline int16_t dlt_698_harmonic_0x200d_encode(dlt_698_harmonic_0x200d_t *data, uint8_t att, uint8_t att_index, uint8_t att_len, uint8_t *des_ptr, uint16_t des_len)
    {
        struct Encode
        {
            /*属性1*/
            struct
            {
                oop_octet_string logic_name[67];
            } att_1;
            /*属性2*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_long value;
                } harm_A[56];
            } att_2;
            /*属性3*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_long value;
                } harm_B[56];
            } att_3;
            /*属性4*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_long value;
                } harm_C[56];
            } att_4;
            /*属性5*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_unsigned value;
                } max_harm;
            } att_5;
            /*属性6*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_scaler_unit value;
                } su_std;
            } att_6;
        } apdu;


        /*属性1*/
        int16_t logic_name_len = dlt_698_encode_octet_string(data->logic_name.data, data->logic_name.len, true, apdu.att_1.logic_name, sizeof(apdu.att_1.logic_name));
        /*属性2*/
        for (int i = 0; i < 56; i++)
        {
            apdu.att_2.harm_A[i].type = DLT_698_TYPE_OOP_LONG;
            dlt_698_big_endian(&apdu.att_2.harm_A[i].value, &data->harm_A[i], sizeof(data->harm_A[i]));
        }
        /*属性3*/
        for (int i = 0; i < 56; i++)
        {
            apdu.att_3.harm_B[i].type = DLT_698_TYPE_OOP_LONG;
            dlt_698_big_endian(&apdu.att_3.harm_B[i].value, &data->harm_B[i], sizeof(data->harm_B[i]));
        }
        /*属性4*/
        for (int i = 0; i < 56; i++)
        {
            apdu.att_4.harm_C[i].type = DLT_698_TYPE_OOP_LONG;
            dlt_698_big_endian(&apdu.att_4.harm_C[i].value, &data->harm_C[i], sizeof(data->harm_C[i]));
        }
        /*属性5*/
        apdu.att_5.max_harm.type = DLT_698_TYPE_OOP_UNSIGNED;
        apdu.att_5.max_harm.value = data->max_harm;
        /*属性6*/
        apdu.att_6.su_std.type = DLT_698_TYPE_OOP_SCALER_UNIT;
        apdu.att_6.su_std.value = data->su_std;

        const struct DLT_698_CLASS_INFO dlt_698_class_tb[] = {
            {logic_name_len, 0, offsetof(struct Encode, att_1)},
            {sizeof(apdu.att_2.harm_A[0]), 56, offsetof(struct Encode, att_2)},
            {sizeof(apdu.att_3.harm_B[0]), 56, offsetof(struct Encode, att_3)},
            {sizeof(apdu.att_4.harm_C[0]), 56, offsetof(struct Encode, att_4)},
            {sizeof(apdu.att_5), 0, offsetof(struct Encode, att_5)},
            {sizeof(apdu.att_6), 0, offsetof(struct Encode, att_6)},
        };
        return dlt_698_apdu_encoder(dlt_698_class_tb, &apdu, att, att_index, att_len, des_ptr, des_len);
    }

#pragma pack()
#ifdef __cplusplus
}
#endif
#endif