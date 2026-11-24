/**
 * @file dlt_698_pulse_0x2401.h
 * @brief 脉冲计量类组帧
 * @details 脉冲计量类组帧
 * @date 2025-04-25
 * @version 1.0
 */
#ifndef DLT_698_PULSE_0x2401_H_
#define DLT_698_PULSE_0x2401_H_
#include "dlt_698_class.h"
#include "dlt_698_utl_tools.h"
#define DLT_698_PULSE_0x2401_OI 0x2401
#ifdef __cplusplus
extern "C"
{
#endif
#pragma pack(1)

    typedef struct DLT_698_PULSE_0x2401
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
            oop_octet_string data[6];
        } addrs;
        /*属性3*/
        struct
        {
            oop_long_unsigned pt;
            oop_long_unsigned ct;
        } ratio;
        /*属性4*/
        struct
        {
            oop_oad oad;
            oop_enum att;
            oop_long_unsigned constant;
        } pluse_cfg[2];
        /*属性5*/
        oop_double_long valid_power;
        /*属性6*/
        oop_double_long invalid_power;
        /*属性7*/
        oop_double_long_unsigned current_day_pos_valid[5];
        /*属性8*/
        oop_double_long_unsigned current_month_pos_valid[5];
        /*属性9*/
        oop_double_long_unsigned current_day_neg_valid[5];
        /*属性10*/
        oop_double_long_unsigned current_month_neg_valid[5];
        /*属性11*/
        oop_double_long_unsigned current_day_pos_invalid[5];
        /*属性12*/
        oop_double_long_unsigned current_month_pos_invalid[5];
        /*属性13*/
        oop_double_long_unsigned current_day_neg_invalid[5];
        /*属性14*/
        oop_double_long_unsigned current_month_neg_invalid[5];
        /*属性15*/
        oop_double_long_unsigned pos_valid_show[5];
        /*属性16*/
        oop_double_long_unsigned pos_invalid_show[5];
        /*属性17*/
        oop_double_long_unsigned neg_valid_show[5];
        /*属性18*/
        oop_scaler_unit su_std[14];
    } dlt_698_pulse_0x2401_t;


    static inline int16_t dlt_698_pulse_0x2401_encode(dlt_698_pulse_0x2401_t *data, uint8_t att, uint8_t att_index, uint8_t att_len, uint8_t *des_ptr, uint16_t des_len)
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
                oop_octet_string addrs[9];
            } att_2;
            /*属性3*/
            struct
            {
                struct
                {
                    uint8_t type;
                    uint8_t cnt;
                    uint8_t type_pt;
                    oop_long_unsigned pt;
                    uint8_t type_ct;
                    oop_long_unsigned ct;
                } ratio;
            } att_3;
            /*属性4*/
            struct
            {
                struct
                {
                    uint8_t type;
                    uint8_t cnt;
                    uint8_t type_oad;
                    oop_oad oad;
                    uint8_t type_att;
                    oop_enum att;
                    uint8_t type_constant;
                    oop_long_unsigned constant;
                } pluse_cfg[2];
            } att_4;
            /*属性5*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_double_long value;
                } valid_power;
            } att_5;
            /*属性6*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_double_long value;
                } invalid_power;
            } att_6;
            /*属性7*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_double_long_unsigned value;
                } current_day_pos_valid[5];
            } att_7;
            /*属性8*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_double_long_unsigned value;
                } current_month_pos_valid[5];
            } att_8;
            /*属性9*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_double_long_unsigned value;
                } current_day_neg_valid[5];
            } att_9;
            /*属性10*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_double_long_unsigned value;
                } current_month_neg_valid[5];
            } att_10;
            /*属性11*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_double_long_unsigned value;
                } current_day_pos_invalid[5];
            } att_11;
            /*属性12*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_double_long_unsigned value;
                } current_month_pos_invalid[5];
            } att_12;
            /*属性13*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_double_long_unsigned value;
                } current_day_neg_invalid[5];
            } att_13;
            /*属性14*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_double_long_unsigned value;
                } current_month_neg_invalid[5];
            } att_14;
            /*属性15*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_double_long_unsigned value;
                } pos_valid_show[5];
            } att_15;
            /*属性16*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_double_long_unsigned value;
                } pos_invalid_show[5];
            } att_16;
            /*属性17*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_double_long_unsigned value;
                } neg_valid_show[5];
            } att_17;
            /*属性18*/
            struct
            {
                struct
                {
                    uint8_t type;
                    oop_scaler_unit value;
                } su_std[14];
            } att_18;
        } apdu;


        /*属性1*/
        int16_t logic_name_len = dlt_698_encode_octet_string(data->logic_name.data, data->logic_name.len, true, apdu.att_1.logic_name, sizeof(apdu.att_1.logic_name));
        /*属性2*/
        int16_t addrs_len = dlt_698_encode_octet_string(data->addrs.data, data->addrs.len, true, apdu.att_2.addrs, sizeof(apdu.att_2.addrs));
        /*属性3*/
        apdu.att_3.ratio.type = DLT_698_TYPE_OOP_STRUCT;
        apdu.att_3.ratio.cnt = 2;
        apdu.att_3.ratio.type_pt = DLT_698_TYPE_OOP_LONG_UNSIGNED;
        dlt_698_big_endian(&apdu.att_3.ratio.pt, &data->ratio.pt, sizeof(data->ratio.pt));
        apdu.att_3.ratio.type_ct = DLT_698_TYPE_OOP_LONG_UNSIGNED;
        dlt_698_big_endian(&apdu.att_3.ratio.ct, &data->ratio.ct, sizeof(data->ratio.ct));
        /*属性4*/
        for (int i = 0; i < 2; i++)
        {
            apdu.att_4.pluse_cfg[i].type = DLT_698_TYPE_OOP_STRUCT;
            apdu.att_4.pluse_cfg[i].cnt = 3;
            apdu.att_4.pluse_cfg[i].type_oad = DLT_698_TYPE_OOP_OAD;
            apdu.att_4.pluse_cfg[i].oad = data->pluse_cfg[i].oad;
            dlt_698_big_endian(&apdu.att_4.pluse_cfg[i].oad, &data->pluse_cfg[i].oad, sizeof(data->pluse_cfg[i].oad));
            apdu.att_4.pluse_cfg[i].type_att = DLT_698_TYPE_OOP_ENUM;
            apdu.att_4.pluse_cfg[i].att = data->pluse_cfg[i].att;
            apdu.att_4.pluse_cfg[i].type_constant = DLT_698_TYPE_OOP_LONG_UNSIGNED;
            dlt_698_big_endian(&apdu.att_4.pluse_cfg[i].constant, &data->pluse_cfg[i].constant, sizeof(data->pluse_cfg[i].constant));
        }
        /*属性5*/
        apdu.att_5.valid_power.type = DLT_698_TYPE_OOP_DOUBLE_LONG;
        dlt_698_big_endian(&apdu.att_5.valid_power.value, &data->valid_power, sizeof(data->valid_power));
        /*属性6*/
        apdu.att_6.invalid_power.type = DLT_698_TYPE_OOP_DOUBLE_LONG;
        dlt_698_big_endian(&apdu.att_6.invalid_power.value, &data->invalid_power, sizeof(data->invalid_power));
        /*属性7*/
        for (int i = 0; i < 5; i++)
        {
            apdu.att_7.current_day_pos_valid[i].type = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
            dlt_698_big_endian(&apdu.att_7.current_day_pos_valid[i].value, &data->current_day_pos_valid[i], sizeof(data->current_day_pos_valid[i]));
        }
        /*属性8*/
        for (int i = 0; i < 5; i++)
        {
            apdu.att_8.current_month_pos_valid[i].type = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
            dlt_698_big_endian(&apdu.att_8.current_month_pos_valid[i].value, &data->current_month_pos_valid[i], sizeof(data->current_month_pos_valid[i]));
        }
        /*属性9*/
        for (int i = 0; i < 5; i++)
        {
            apdu.att_9.current_day_neg_valid[i].type = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
            dlt_698_big_endian(&apdu.att_9.current_day_neg_valid[i].value, &data->current_day_neg_valid[i], sizeof(data->current_day_neg_valid[i]));
        }
        /*属性10*/
        for (int i = 0; i < 5; i++)
        {
            apdu.att_10.current_month_neg_valid[i].type = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
            dlt_698_big_endian(&apdu.att_10.current_month_neg_valid[i].value, &data->current_month_neg_valid[i], sizeof(data->current_month_neg_valid[i]));
        }
        /*属性11*/
        for (int i = 0; i < 5; i++)
        {
            apdu.att_11.current_day_pos_invalid[i].type = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
            dlt_698_big_endian(&apdu.att_11.current_day_pos_invalid[i].value, &data->current_day_pos_invalid[i], sizeof(data->current_day_pos_invalid[i]));
        }
        /*属性12*/
        for (int i = 0; i < 5; i++)
        {
            apdu.att_12.current_month_pos_invalid[i].type = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
            dlt_698_big_endian(&apdu.att_12.current_month_pos_invalid[i].value, &data->current_month_pos_invalid[i], sizeof(data->current_month_pos_invalid[i]));
        }
        /*属性13*/
        for (int i = 0; i < 5; i++)
        {
            apdu.att_13.current_day_neg_invalid[i].type = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
            dlt_698_big_endian(&apdu.att_13.current_day_neg_invalid[i].value, &data->current_day_neg_invalid[i], sizeof(data->current_day_neg_invalid[i]));
        }
        /*属性14*/
        for (int i = 0; i < 5; i++)
        {
            apdu.att_14.current_month_neg_invalid[i].type = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
            dlt_698_big_endian(&apdu.att_14.current_month_neg_invalid[i].value, &data->current_month_neg_invalid[i], sizeof(data->current_month_neg_invalid[i]));
        }
        /*属性15*/
        for (int i = 0; i < 5; i++)
        {
            apdu.att_15.pos_valid_show[i].type = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
            dlt_698_big_endian(&apdu.att_15.pos_valid_show[i].value, &data->pos_valid_show[i], sizeof(data->pos_valid_show[i]));
        }
        /*属性16*/
        for (int i = 0; i < 5; i++)
        {
            apdu.att_16.pos_invalid_show[i].type = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
            dlt_698_big_endian(&apdu.att_16.pos_invalid_show[i].value, &data->pos_invalid_show[i], sizeof(data->pos_invalid_show[i]));
        }
        /*属性17*/
        for (int i = 0; i < 5; i++)
        {
            apdu.att_17.neg_valid_show[i].type = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
            dlt_698_big_endian(&apdu.att_17.neg_valid_show[i].value, &data->neg_valid_show[i], sizeof(data->neg_valid_show[i]));
        }
        /*属性18*/
        for (int i = 0; i < 14; i++)
        {
            apdu.att_18.su_std[i].type = DLT_698_TYPE_OOP_SCALER_UNIT;
            apdu.att_18.su_std[i].value = data->su_std[i];
        }

        const struct DLT_698_CLASS_INFO dlt_698_class_tb[] = {
            {logic_name_len, 0, offsetof(struct Encode, att_1)},
            {addrs_len, 0, offsetof(struct Encode, att_2)},
            {sizeof(apdu.att_3), 0, offsetof(struct Encode, att_3)},
            {sizeof(apdu.att_4.pluse_cfg[0]), 2, offsetof(struct Encode, att_4)},
            {sizeof(apdu.att_5), 0, offsetof(struct Encode, att_5)},
            {sizeof(apdu.att_6), 0, offsetof(struct Encode, att_6)},
            {sizeof(apdu.att_7.current_day_pos_valid[0]), 5, offsetof(struct Encode, att_7)},
            {sizeof(apdu.att_8.current_month_pos_valid[0]), 5, offsetof(struct Encode, att_8)},
            {sizeof(apdu.att_9.current_day_neg_valid[0]), 5, offsetof(struct Encode, att_9)},
            {sizeof(apdu.att_10.current_month_neg_valid[0]), 5, offsetof(struct Encode, att_10)},
            {sizeof(apdu.att_11.current_day_pos_invalid[0]), 5, offsetof(struct Encode, att_11)},
            {sizeof(apdu.att_12.current_month_pos_invalid[0]), 5, offsetof(struct Encode, att_12)},
            {sizeof(apdu.att_13.current_day_neg_invalid[0]), 5, offsetof(struct Encode, att_13)},
            {sizeof(apdu.att_14.current_month_neg_invalid[0]), 5, offsetof(struct Encode, att_14)},
            {sizeof(apdu.att_15.pos_valid_show[0]), 5, offsetof(struct Encode, att_15)},
            {sizeof(apdu.att_16.pos_invalid_show[0]), 5, offsetof(struct Encode, att_16)},
            {sizeof(apdu.att_17.neg_valid_show[0]), 5, offsetof(struct Encode, att_17)},
            {sizeof(apdu.att_18.su_std[0]), 14, offsetof(struct Encode, att_18)},
        };
        return dlt_698_apdu_encoder(dlt_698_class_tb, &apdu, att, att_index, att_len, des_ptr, des_len);
    }

#pragma pack()
#ifdef __cplusplus
}
#endif
#endif