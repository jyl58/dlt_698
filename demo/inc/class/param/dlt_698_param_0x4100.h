/**
 * @file dlt_698_param_0x4100.h
 * @brief 最大需量周期组帧
 * @details 最大需量周期组帧
 * @date 2025-04-25
 * @version 1.0
 */
#ifndef DLT_698_PARAM_0x4100_H_
#define DLT_698_PARAM_0x4100_H_
#include "dlt_698_class.h"
#include "dlt_698_utl_tools.h"
#define DLT_698_PARAM_0x4100_OI 0x4100
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

    typedef struct DLT_698_PARAM_0x4100
    {
        /*属性1*/
        struct
        {
            uint8_t len;
            oop_octet_string data[64];
        } logic_name;
        /*属性2*/
        oop_unsigned demand_period;
    } dlt_698_param_0x4100_t;


    static inline int16_t dlt_698_param_0x4100_encode(dlt_698_param_0x4100_t *data, uint8_t att, uint8_t att_index, uint8_t att_len, uint8_t *des_ptr, uint16_t des_len)
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
                } demand_period;
            } att_2;
        } apdu;


        /*属性1*/
        int16_t logic_name_len = dlt_698_encode_octet_string(data->logic_name.data, data->logic_name.len, true, apdu.att_1.logic_name, sizeof(apdu.att_1.logic_name));
        /*属性2*/
        apdu.att_2.demand_period.type = DLT_698_TYPE_OOP_UNSIGNED;
        apdu.att_2.demand_period.value = data->demand_period;

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