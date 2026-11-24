/**
 * @file dlt_698_param_0x4101.h
 * @brief 滑差时间组帧
 * @details 滑差时间组帧
 * @date 2025-04-25
 * @version 1.0
 */
#ifndef DLT_698_PARAM_0x4101_H_
#define DLT_698_PARAM_0x4101_H_
#include "dlt_698_class.h"
#include "dlt_698_utl_tools.h"
#define DLT_698_PARAM_0x4101_OI 0x4101
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

    typedef struct DLT_698_PARAM_0x4101
    {
        /*属性1*/
        struct
        {
            uint8_t len;
            oop_octet_string data[64];
        } logic_name;
        /*属性2*/
        oop_unsigned slide_time;
    } dlt_698_param_0x4101_t;


    static inline int16_t dlt_698_param_0x4101_encode(dlt_698_param_0x4101_t *data, uint8_t att, uint8_t att_index, uint8_t att_len, uint8_t *des_ptr, uint16_t des_len)
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
                    oop_unsigned value;
                } slide_time;
            } att_2;
        } apdu;


        /*属性1*/
        int16_t logic_name_len = dlt_698_encode_octet_string(data->logic_name.data, data->logic_name.len, true, apdu.att_1.logic_name, sizeof(apdu.att_1.logic_name));
        /*属性2*/
        apdu.att_2.slide_time.type = DLT_698_TYPE_OOP_UNSIGNED;
        apdu.att_2.slide_time.value = data->slide_time;

        const struct DLT_698_CLASS_INFO dlt_698_class_tb[] = {
            {logic_name_len, 0, offsetof(struct Encode, att_1)},
            {sizeof(apdu.att_2), 0, offsetof(struct Encode, att_2)},
        };
        return dlt_698_apdu_encoder(dlt_698_class_tb, &apdu, att, att_index, att_len, des_ptr, des_len);
    }

#pragma pack()
#ifdef __cplusplus
}
#endif
#endif