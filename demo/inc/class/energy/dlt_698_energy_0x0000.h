/**
 * @file dlt_698_energy_0x0000.h
 * @brief 电能量组帧
 * @details 电能量组帧
 * @date 2025-04-27
 * @version 1.0
 */
#ifndef DLT_698_ENERGY_0x0000_H_
#define DLT_698_ENERGY_0x0000_H_
#include "dlt_698_class.h"
#include "dlt_698_utl_tools.h"
#define DLT_698_ENERGY_0x0000_OI 0x0000
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

    typedef struct DLT_698_ENERGY_0x0000
    {
        /*属性1*/
        struct
        {
            uint8_t len;
            oop_octet_string data[64];
        } logic_name;
        /*属性2*/
        oop_double_long_unsigned energy_std[5];
        /*属性3*/
        oop_scaler_unit su_std;
        /*属性4*/
        oop_long64_unsigned energy_hig[5];
        /*属性5*/
        oop_scaler_unit su_hig;
    } dlt_698_energy_0x0000_t;


    static inline int16_t dlt_698_energy_0x0000_encode(dlt_698_energy_0x0000_t *data, uint8_t att, uint8_t att_index, uint8_t att_len, uint8_t *des_ptr, uint16_t des_len)
    {
        struct Encode
        {
            /*属性1*/
            struct
            {
                oop_octet_string logic_name[65];
            } att_1;
            /*属性2*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_double_long_unsigned value;
                } energy_std[5];
            } att_2;
            /*属性3*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_scaler_unit value;
                } su_std;
            } att_3;
            /*属性4*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_long64_unsigned value;
                } energy_hig[5];
            } att_4;
            /*属性5*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_scaler_unit value;
                } su_hig;
            } att_5;
        } apdu;


        /*属性1*/
        int16_t logic_name_len = dlt_698_encode_octet_string(data->logic_name.data, data->logic_name.len, true, apdu.att_1.logic_name, sizeof(apdu.att_1.logic_name));
        /*属性2*/
        for (int i = 0; i < 5; i++)
        {
            apdu.att_2.energy_std[i].type = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
            dlt_698_big_endian(&apdu.att_2.energy_std[i].value, &data->energy_std[i], sizeof(data->energy_std[i]));
        }
        /*属性3*/
        apdu.att_3.su_std.type = DLT_698_TYPE_OOP_SCALER_UNIT;
        apdu.att_3.su_std.value = data->su_std;
        /*属性4*/
        for (int i = 0; i < 5; i++)
        {
            apdu.att_4.energy_hig[i].type = DLT_698_TYPE_OOP_LONG64_UNSIGNED;
            dlt_698_big_endian(&apdu.att_4.energy_hig[i].value, &data->energy_hig[i], sizeof(data->energy_hig[i]));
        }
        /*属性5*/
        apdu.att_5.su_hig.type = DLT_698_TYPE_OOP_SCALER_UNIT;
        apdu.att_5.su_hig.value = data->su_hig;

        const struct DLT_698_CLASS_INFO dlt_698_class_tb[] = {
            {(uint16_t)(logic_name_len), 0, offsetof(struct Encode, att_1)},     {(uint16_t)(sizeof(apdu.att_2.energy_std[0])), 5, offsetof(struct Encode, att_2)},
            {(uint16_t)(sizeof(apdu.att_3)), 0, offsetof(struct Encode, att_3)}, {(uint16_t)(sizeof(apdu.att_4.energy_hig[0])), 5, offsetof(struct Encode, att_4)},
            {(uint16_t)(sizeof(apdu.att_5)), 0, offsetof(struct Encode, att_5)},
        };
        return dlt_698_apdu_encoder(dlt_698_class_tb, &apdu, att, att_index, att_len, des_ptr, des_len);
    }

#pragma pack()
#ifdef __cplusplus
}
#endif
#endif