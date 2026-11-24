/**
 * @file dlt_698_var_0x2015.h
 * @brief 电能表跟随上报状态字组帧
 * @details 电能表跟随上报状态字组帧
 * @date 2025-04-28
 * @version 1.0
 */
#ifndef DLT_698_VAR_0x2015_H_
#define DLT_698_VAR_0x2015_H_
#include "dlt_698_class.h"
#include "dlt_698_utl_tools.h"
#define DLT_698_VAR_0x2015_OI 0x2015
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

    typedef struct DLT_698_VAR_0x2015
    {
        /*属性1*/
        struct
        {
            uint8_t len;
            oop_octet_string data[64];
        } logic_name;
        /*属性2*/
        oop_bit_string report_tag[32];
        /*属性3*/
        oop_scaler_unit su_std;
    } dlt_698_var_0x2015_t;


    static inline int16_t dlt_698_var_0x2015_encode(dlt_698_var_0x2015_t *data, uint8_t att, uint8_t att_index, uint8_t att_len, uint8_t *des_ptr, uint16_t des_len)
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
                uint8_t report_tag[6];
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
        int16_t report_tag_len = dlt_698_encode_bit_string(data->report_tag, sizeof(data->report_tag), true, apdu.att_2.report_tag, sizeof(apdu.att_2.report_tag));
        /*属性3*/
        apdu.att_3.su_std.type = DLT_698_TYPE_OOP_SCALER_UNIT;
        apdu.att_3.su_std.value = data->su_std;

        const struct DLT_698_CLASS_INFO dlt_698_class_tb[] = {
            {(uint16_t)(logic_name_len), 0, offsetof(struct Encode, att_1)},
            {(uint16_t)(report_tag_len), 0, offsetof(struct Encode, att_2)},
            {(uint16_t)(sizeof(apdu.att_3)), 0, offsetof(struct Encode, att_3)},
        };
        return dlt_698_apdu_encoder(dlt_698_class_tb, &apdu, att, att_index, att_len, des_ptr, des_len);
    }

#pragma pack()
#ifdef __cplusplus
}
#endif
#endif