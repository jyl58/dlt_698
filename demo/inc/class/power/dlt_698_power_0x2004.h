/**
 * @file dlt_698_power_0x2004.h
 * @brief 组帧
 * @details 组帧
 * @date 2025-04-25
 * @version 1.0
 */
#ifndef DLT_698_POWER_0x2004_H_
#define DLT_698_POWER_0x2004_H_
#include "dlt_698_class.h"
#include "dlt_698_utl_tools.h"
#define DLT_698_POWER_0x2004_OI 0x2004
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

    typedef struct DLT_698_POWER_0x2004
    {
        /*属性1*/
        struct
        {
            uint8_t len;
            oop_octet_string data[64];
        } logic_name;
        /*属性2*/
        oop_double_long valid_power[4];
        /*属性3*/
        oop_scaler_unit su_std;
    } dlt_698_power_0x2004_t;


    static inline int16_t dlt_698_power_0x2004_encode(dlt_698_power_0x2004_t *data, uint8_t att, uint8_t att_index, uint8_t att_len, uint8_t *des_ptr, uint16_t des_len)
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
                    oop_double_long value;
                } valid_power[4];
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
        } apdu;


        /*属性1*/
        int16_t logic_name_len = dlt_698_encode_octet_string(data->logic_name.data, data->logic_name.len, true, apdu.att_1.logic_name, sizeof(apdu.att_1.logic_name));
        /*属性2*/
        for (int i = 0; i < 4; i++)
        {
            apdu.att_2.valid_power[i].type = DLT_698_TYPE_OOP_DOUBLE_LONG;
            dlt_698_big_endian(&apdu.att_2.valid_power[i].value, &data->valid_power[i], sizeof(data->valid_power[i]));
        }
        /*属性3*/
        apdu.att_3.su_std.type = DLT_698_TYPE_OOP_SCALER_UNIT;
        apdu.att_3.su_std.value = data->su_std;

        const struct DLT_698_CLASS_INFO dlt_698_class_tb[] = {
            {logic_name_len, 0, offsetof(struct Encode, att_1)},
            {sizeof(apdu.att_2.valid_power[0]), 4, offsetof(struct Encode, att_2)},
            {sizeof(apdu.att_3), 0, offsetof(struct Encode, att_3)},
        };
        return dlt_698_apdu_encoder(dlt_698_class_tb, &apdu, att, att_index, att_len, des_ptr, des_len);
    }

#pragma pack()
#ifdef __cplusplus
}
#endif
#endif