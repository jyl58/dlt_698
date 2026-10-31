/**
 * @file dlt_698_param_0x410B.h
 * @brief 电能表型号组帧
 * @details 电能表型号组帧
 * @date 2025-04-25
 * @version 1.0
 */
#ifndef DLT_698_PARAM_0x410B_H_
#define DLT_698_PARAM_0x410B_H_
#include "dlt_698_class.h"
#include "dlt_698_utl_tools.h"
#define DLT_698_PARAM_0x410B_OI 0x410B
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

    typedef struct DLT_698_PARAM_0x410B
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
            oop_visible_string data[32];
        } meter_type;
    } dlt_698_param_0x410B_t;


    static inline int16_t dlt_698_param_0x410B_encode(dlt_698_param_0x410B_t *data, uint8_t att, uint8_t att_index, uint8_t att_len, uint8_t *des_ptr, uint16_t des_len)
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
                oop_visible_string meter_type[35];
            } att_2;
        } apdu;


        /*属性1*/
        int16_t logic_name_len = dlt_698_encode_octet_string(data->logic_name.data, data->logic_name.len, true, apdu.att_1.logic_name, sizeof(apdu.att_1.logic_name));
        /*属性2*/
        int16_t meter_type_len = dlt_698_encode_visible_string(data->meter_type.data, data->meter_type.len, true, apdu.att_2.meter_type, sizeof(apdu.att_2.meter_type));

        const struct DLT_698_CLASS_INFO dlt_698_class_tb[] = {
            {logic_name_len, 0, offsetof(struct Encode, att_1)},
            {meter_type_len, 0, offsetof(struct Encode, att_2)},
        };
        return dlt_698_apdu_encoder(dlt_698_class_tb, &apdu, att, att_index, att_len, des_ptr, des_len);
    }

#pragma pack()
#ifdef __cplusplus
}
#endif
#endif