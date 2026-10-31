/**
 * @file dlt_698_demand_0x1000.h
 * @brief 最大需量组帧
 * @details 最大需量组帧
 * @date 2025-04-25
 * @version 1.0
 */
#ifndef DLT_698_DEMAND_0x1000_H_
#define DLT_698_DEMAND_0x1000_H_
#include "dlt_698_class.h"
#include "dlt_698_utl_tools.h"
#define DLT_698_DEMAND_0x1000_OI 0x1000
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

    typedef struct DLT_698_DEMAND_0x1000
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
            oop_double_long_unsigned energy;
            oop_date_time_s time;
        } demand[5];
        /*属性3*/
        oop_scaler_unit su_std;
        /*属性4*/
        oop_unsigned key1[6];
        /*属性5*/
        oop_unsigned key2;
    } dlt_698_demand_0x1000_t;


    static inline int16_t dlt_698_demand_0x1000_encode(dlt_698_demand_0x1000_t *data, uint8_t att, uint8_t att_index, uint8_t att_len, uint8_t *des_ptr, uint16_t des_len)
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
                    uint8_t cnt;
                    uint8_t type_energy;
                    oop_double_long_unsigned energy;
                    uint8_t type_time;
                    oop_date_time_s time;
                } demand[5];
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
                    oop_unsigned value;
                } key1[6];
            } att_4;
            /*属性5*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_unsigned value;
                } key2;
            } att_5;
        } apdu;


        /*属性1*/
        int16_t logic_name_len = dlt_698_encode_octet_string(data->logic_name.data, data->logic_name.len, true, apdu.att_1.logic_name, sizeof(apdu.att_1.logic_name));
        /*属性2*/
        for (int i = 0; i < 5; i++)
        {
            apdu.att_2.demand[i].type = DLT_698_TYPE_OOP_STRUCT;
            apdu.att_2.demand[i].cnt = 2;
            apdu.att_2.demand[i].type_energy = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
            dlt_698_big_endian(&apdu.att_2.demand[i].energy, &data->demand[i].energy, sizeof(data->demand[i].energy));
            apdu.att_2.demand[i].type_time = DLT_698_TYPE_OOP_DATE_TIME_S;
            apdu.att_2.demand[i].time = data->demand[i].time;
            dlt_698_big_endian(&apdu.att_2.demand[i].time.year, &data->demand[i].time.year, sizeof(data->demand[i].time.year));
        }
        /*属性3*/
        apdu.att_3.su_std.type = DLT_698_TYPE_OOP_SCALER_UNIT;
        apdu.att_3.su_std.value = data->su_std;
        /*属性4*/
        for (int i = 0; i < 6; i++)
        {
            apdu.att_4.key1[i].type = DLT_698_TYPE_OOP_UNSIGNED;
            apdu.att_4.key1[i].value = data->key1[i];
        }
        /*属性5*/
        apdu.att_5.key2.type = DLT_698_TYPE_OOP_UNSIGNED;
        apdu.att_5.key2.value = data->key2;

        const struct DLT_698_CLASS_INFO dlt_698_class_tb[] = {
            {logic_name_len, 0, offsetof(struct Encode, att_1)},     {sizeof(apdu.att_2.demand[0]), 5, offsetof(struct Encode, att_2)},
            {sizeof(apdu.att_3), 0, offsetof(struct Encode, att_3)}, {sizeof(apdu.att_4.key1[0]), 6, offsetof(struct Encode, att_4)},
            {sizeof(apdu.att_5), 0, offsetof(struct Encode, att_5)},
        };
        return dlt_698_apdu_encoder(dlt_698_class_tb, &apdu, att, att_index, att_len, des_ptr, des_len);
    }

#pragma pack()
#ifdef __cplusplus
}
#endif
#endif