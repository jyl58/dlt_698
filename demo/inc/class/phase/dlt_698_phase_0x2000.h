/**
 * @file dlt_698_phase_0x2000.h
 * @brief 分项变量类组帧
 * @details 分项变量类组帧
 * @date 2025-04-25
 * @version 1.0
 */
#ifndef DLT_698_PHASE_0x2000_H_
#define DLT_698_PHASE_0x2000_H_
#include "dlt_698_class.h"
#include "dlt_698_utl_tools.h"
#define DLT_698_PHASE_0x2000_OI 0x2000
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

    typedef struct DLT_698_PHASE_0x2000
    {
        /*属性1*/
        struct
        {
            uint8_t len;
            oop_octet_string data[64];
        } logic_name;
        /*属性2*/
        oop_long_unsigned voltage[3];
        /*属性3*/
        oop_scaler_unit su_std;
        /*属性4*/
        oop_double_long_unsigned hig_voltage;
    } dlt_698_phase_0x2000_t;


    static inline int16_t dlt_698_phase_0x2000_encode(dlt_698_phase_0x2000_t *data, uint8_t att, uint8_t att_index, uint8_t att_len, uint8_t *des_ptr, uint16_t des_len)
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
                    oop_long_unsigned value;
                } voltage[3];
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
                    oop_double_long_unsigned value;
                } hig_voltage;
            } att_4;
        } apdu;


        /*属性1*/
        int16_t logic_name_len = dlt_698_encode_octet_string(data->logic_name.data, data->logic_name.len, true, apdu.att_1.logic_name, sizeof(apdu.att_1.logic_name));
        /*属性2*/
        for (int i = 0; i < 3; i++)
        {
            apdu.att_2.voltage[i].type = DLT_698_TYPE_OOP_LONG_UNSIGNED;
            dlt_698_big_endian(&apdu.att_2.voltage[i].value, &data->voltage[i], sizeof(data->voltage[i]));
        }
        /*属性3*/
        apdu.att_3.su_std.type = DLT_698_TYPE_OOP_SCALER_UNIT;
        apdu.att_3.su_std.value = data->su_std;
        /*属性4*/
        apdu.att_4.hig_voltage.type = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
        dlt_698_big_endian(&apdu.att_4.hig_voltage.value, &data->hig_voltage, sizeof(data->hig_voltage));

        const struct DLT_698_CLASS_INFO dlt_698_class_tb[] = {
            {logic_name_len, 0, offsetof(struct Encode, att_1)},
            {sizeof(apdu.att_2.voltage[0]), 3, offsetof(struct Encode, att_2)},
            {sizeof(apdu.att_3), 0, offsetof(struct Encode, att_3)},
            {sizeof(apdu.att_4), 0, offsetof(struct Encode, att_4)},
        };
        return dlt_698_apdu_encoder(dlt_698_class_tb, &apdu, att, att_index, att_len, des_ptr, des_len);
    }

#pragma pack()
#ifdef __cplusplus
}
#endif
#endif