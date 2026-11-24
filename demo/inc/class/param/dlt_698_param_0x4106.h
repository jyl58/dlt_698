/**
 * @file dlt_698_param_0x4106.h
 * @brief 计量规格组帧
 * @details 计量规格组帧
 * @date 2025-04-25
 * @version 1.0
 */
#ifndef DLT_698_PARAM_0x4106_H_
#define DLT_698_PARAM_0x4106_H_
#include "dlt_698_class.h"
#include "dlt_698_utl_tools.h"
#define DLT_698_PARAM_0x4106_OI 0x4106
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

    typedef struct DLT_698_PARAM_0x4106
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
            uint8_t len;
            oop_visible_string data[6];
        } max_current;
        /*属性3*/
        struct
        {
            uint8_t len;
            oop_visible_string data[32];
        } min_current;
        /*属性4*/
        struct
        {
            uint8_t len;
            oop_visible_string data[32];
        } breakover_current;
    } dlt_698_param_0x4106_t;


    static inline int16_t dlt_698_param_0x4106_encode(dlt_698_param_0x4106_t *data, uint8_t att, uint8_t att_index, uint8_t att_len, uint8_t *des_ptr, uint16_t des_len)
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
                oop_visible_string max_current[9];
            } att_2;
            /*属性3*/
            struct
            {
                oop_visible_string min_current[35];
            } att_3;
            /*属性4*/
            struct
            {
                oop_visible_string breakover_current[35];
            } att_4;
        } apdu;


        /*属性1*/
        int16_t logic_name_len = dlt_698_encode_octet_string(data->logic_name.data, data->logic_name.len, true, apdu.att_1.logic_name, sizeof(apdu.att_1.logic_name));
        /*属性2*/
        int16_t max_current_len = dlt_698_encode_visible_string(data->max_current.data, data->max_current.len, true, apdu.att_2.max_current, sizeof(apdu.att_2.max_current));
        /*属性3*/
        int16_t min_current_len = dlt_698_encode_visible_string(data->min_current.data, data->min_current.len, true, apdu.att_3.min_current, sizeof(apdu.att_3.min_current));
        /*属性4*/
        int16_t breakover_current_len = dlt_698_encode_visible_string(data->breakover_current.data, data->breakover_current.len, true, apdu.att_4.breakover_current, sizeof(apdu.att_4.breakover_current));

        const struct DLT_698_CLASS_INFO dlt_698_class_tb[] = {
            {logic_name_len, 0, offsetof(struct Encode, att_1)},
            {max_current_len, 0, offsetof(struct Encode, att_2)},
            {min_current_len, 0, offsetof(struct Encode, att_3)},
            {breakover_current_len, 0, offsetof(struct Encode, att_4)},
        };
        return dlt_698_apdu_encoder(dlt_698_class_tb, &apdu, att, att_index, att_len, des_ptr, des_len);
    }

#pragma pack()
#ifdef __cplusplus
}
#endif
#endif