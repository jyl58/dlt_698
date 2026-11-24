#include "dlt_698_test_encode.h"
#include "dlt_698_demand_0x1000.h"
#include "dlt_698_energy_0x0000.h"
#include "dlt_698_param_0x4101.h"
#include "dlt_698_param_0x4100.h"
#include "dlt_698_param_0x410B.h"
#include "dlt_698_param_0x4004.h"
#include "dlt_698_param_0x4106.h"
#include "dlt_698_var_0x2015.h"
#include "dlt_698_power_0x2004.h"
#include "dlt_698_phase_0x2000.h"
#include "dlt_698_pulse_0x2401.h"
#include "dlt_698_harmonic_0x200d.h"
#include "dlt_698_esam_F100.h"
#include "dlt_698_utl_tools.h"

void dlt_698_encode_type(dlt_698_parser *parser)
{
    uint8_t ctrl = DLT_698_FROM_CLIENT | DLT_698_CLIENT_LAUNCH | DLT_698_SUBFRAME_NO | DLT_698_DISTURB_NO | RM_698_FRAME_FUN_3;
    uint8_t frame[1024] = {0};
    uint8_t apdu[1024] = {0};
    int16_t ret = 0;
    int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x10100200);
    oop_bool val = true;
    pos += dlt_698_encode_bool(val, true, apdu + pos, sizeof(apdu) - pos);

    // oop_double_long val=34;
    // pos+=dlt_698_encode_double_long(val, true, apdu+pos,sizeof(apdu)-pos);
    // oop_double_long_unsigned val=34;
    // pos+=dlt_698_encode_double_long_unsigned(val, true, apdu+pos,sizeof(apdu)-pos);
    // oop_integer val=34;
    // pos+=dlt_698_encode_integer(val, true, apdu+pos,sizeof(apdu)-pos);
    // oop_long val=34;
    // pos+=dlt_698_encode_long(val, true, apdu+pos,sizeof(apdu)-pos);
    // oop_unsigned val=34;
    // pos+=dlt_698_encode_unsigned(val, true, apdu+pos,sizeof(apdu)-pos);

    // oop_long_unsigned val=2900;
    // pos+=dlt_698_encode_long_unsigned(val, true, apdu+pos,sizeof(apdu)-pos);
    // oop_long64 val=2900;
    // pos+=dlt_698_encode_long64(val, true, apdu+pos,sizeof(apdu)-pos);
    // oop_long64_unsigned val=2900;
    // pos+=dlt_698_encode_long64_unsigned(val, true, apdu+pos,sizeof(apdu)-pos);
    // oop_enum val=3;
    // pos+=dlt_698_encode_enum(val, true, apdu+pos,sizeof(apdu)-pos);
    // oop_float32 val=12.5;
    // pos+=dlt_698_encode_float32(val, true, apdu+pos,sizeof(apdu)-pos);
    // oop_float64 val=12.5;
    // pos+=dlt_698_encode_float64(val, true, apdu+pos,sizeof(apdu)-pos);
    // oop_time ti={1,2,3};
    // pos+=dlt_698_encode_time(ti, true, apdu+pos,sizeof(apdu)-pos);
    // oop_date dt = {2025,4,25,5};
    // pos+=dlt_698_encode_date(dt, true, apdu+pos,sizeof(apdu)-pos);
    // oop_date_time dt = {2025,4,25,5,15,44,45,200};
    // pos+=dlt_698_encode_date_time(dt, true, apdu+pos,sizeof(apdu)-pos);
    // oop_ti ti = {1,60};
    // pos+=dlt_698_encode_ti(ti, true, apdu+pos,sizeof(apdu)-pos);
    // oop_comdcb com= {6,2,8,1,0};
    // pos+=dlt_698_encode_comdcb(com, true, apdu+pos,sizeof(apdu)-pos);
    apdu[pos++] = 0x00;
    apdu[pos++] = 0x00;
    ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame) / sizeof(frame[0]));
    printData("test=", frame, ret);
}
void dlt_698_encode_demand(dlt_698_parser *parser)
{
    uint8_t ctrl = DLT_698_FROM_CLIENT | DLT_698_CLIENT_LAUNCH | DLT_698_SUBFRAME_NO | DLT_698_DISTURB_NO | RM_698_FRAME_FUN_3;
    uint8_t frame[1024] = {0};
    uint8_t apdu[1024] = {0};

    dlt_698_demand_0x1000_t test_demand;
    int16_t ret = 0;
    // 属性1测试
    {
        uint8_t name[] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36};
        test_demand.logic_name.len = sizeof(name);
        memcpy(test_demand.logic_name.data, name, test_demand.logic_name.len);

        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x10100100);
        ret = dlt_698_demand_0x1000_encode(&test_demand, 1, 1, 1, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            ret = dlt_698_encode_null(apdu + pos, sizeof(apdu) - pos);
            if (ret < 0)
            {
                return;
            }
            pos += ret;
            ret = dlt_698_encode_null(apdu + pos, sizeof(apdu) - pos);
            if (ret < 0)
            {
                return;
            }
            pos += ret;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame));

            printData("demand att1 frame=", frame, ret);
        }
    }
    // 属性2测试
    {
        oop_double_long_unsigned engery = 221;
        for (size_t i = 0; i < sizeof(test_demand.demand) / sizeof(test_demand.demand[0]); i++)
        {
            test_demand.demand[i].energy = engery + i;
            time_t t = time(NULL) + i;
            dlt_698_convert_dts(t, &test_demand.demand[i].time);
        }

        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x10100200);
        ret = dlt_698_demand_0x1000_encode(&test_demand, 2, 2, 3, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame) / sizeof(frame[0]));
            printData("demand att2 frame=", frame, ret);
        }
    }
    // 属性3测试
    {
        test_demand.su_std.scaler = 10;
        test_demand.su_std.unit = 5;
        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x10100300);
        ret = dlt_698_demand_0x1000_encode(&test_demand, 3, 2, 2, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;

            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame));
            printData("demand att3 frame=", frame, ret);
        }
    }
}

void dlt_698_encode_energy(dlt_698_parser *parser)
{
    uint8_t ctrl = DLT_698_FROM_CLIENT | DLT_698_CLIENT_LAUNCH | DLT_698_SUBFRAME_NO | DLT_698_DISTURB_NO | RM_698_FRAME_FUN_3;
    uint8_t frame[1024] = {0};
    uint8_t apdu[1024] = {0};
    dlt_698_energy_0x0000_t test_energy;
    int16_t ret = 0;
    {
        oop_double_long_unsigned engery = 221;
        for (size_t i = 0; i < sizeof(test_energy.energy_std) / sizeof(test_energy.energy_std[0]); i++)
        {
            test_energy.energy_std[i] = engery + i;
        }

        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x00100200);
        int16_t ret = dlt_698_energy_0x0000_encode(&test_energy, 2, 2, 2, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame));
            printData("energy att2 frame=", frame, ret);
        }
    }
    {
        test_energy.su_std.scaler = 10;
        test_energy.su_std.unit = 5;

        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x00000300);
        ret = dlt_698_energy_0x0000_encode(&test_energy, 3, 1, 1, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;

            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame));
            printData("energy att3 frame=", frame, ret);
        }
    }
    {
        oop_long64_unsigned engery = 221;
        for (size_t i = 0; i < sizeof(test_energy.energy_hig) / sizeof(test_energy.energy_hig[0]); i++)
        {
            test_energy.energy_hig[i] = engery + i;
        }
        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x00100400);
        ret = dlt_698_energy_0x0000_encode(&test_energy, 4, 2, 3, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame));
            printData("energy att4 frame=", frame, ret);
        }
    }
}

void dlt_698_encode_param(dlt_698_parser *parser)
{
    uint8_t ctrl = DLT_698_FROM_CLIENT | DLT_698_CLIENT_LAUNCH | DLT_698_SUBFRAME_NO | DLT_698_DISTURB_NO | RM_698_FRAME_FUN_3;
    uint8_t frame[1024] = {0};
    uint8_t apdu[1024] = {0};
    int16_t ret = 0;
    {
        dlt_698_param_0x4101_t slide;
        slide.slide_time = 1;

        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x41010200);
        ret = dlt_698_param_0x4101_encode(&slide, 2, 1, 1, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame));
            printData("param slide time frame=", frame, ret);
        }
    }
    {
        dlt_698_param_0x4100_t demand;
        demand.demand_period = 15;

        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x41000200);
        ret = dlt_698_param_0x4100_encode(&demand, 2, 1, 1, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame));
            printData("param slide period frame=", frame, ret);
        }
    }
    {
        dlt_698_param_0x410B_t meter;
        char *type = "DTZ1710";
        meter.meter_type.len = strlen(type);    // 固定visible-string(SIZE(32))
        strcpy(meter.meter_type.data, type);
        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x410B0200);
        ret = dlt_698_param_0x410B_encode(&meter, 2, 1, 1, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame) / sizeof(frame[0]));
            printData("param meter type frame=", frame, ret);
        }
    }
    {
        dlt_698_param_0x4004_t position;
        position.coordinate.longitude.dir = 0;
        position.coordinate.longitude.degree = 101;
        position.coordinate.longitude.minute = 102;
        position.coordinate.longitude.second = 103;

        position.coordinate.latitude.dir = 0;
        position.coordinate.latitude.degree = 201;
        position.coordinate.latitude.minute = 202;
        position.coordinate.latitude.second = 203;
        position.coordinate.height = 301;

        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x40040200);
        ret = dlt_698_param_0x4004_encode(&position, 2, 1, 1, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame));
            printData("param coordinate frame=", frame, ret);
        }
    }
    // 计量规格 max_current
    {
        dlt_698_param_0x4106_t current;
        memset(current.max_current.data, 0, sizeof(current.max_current.data));    // 初始化
        current.max_current.len = 6;                                              // 固定visible-string(SIZE(6))
        strcpy(current.max_current.data, "1.2A");

        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x41060200);
        ret = dlt_698_param_0x4106_encode(&current, 2, 1, 1, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame));
            printData("param max_current frame=", frame, ret);
        }
    }
    // 计量规格 min_current
    {
        dlt_698_param_0x4106_t current;

        memset(current.min_current.data, 0, sizeof(current.min_current.data));
        char *min_current = "0.003A";
        strcpy(current.min_current.data, min_current);
        current.min_current.len = strlen(min_current);    //=visible-string(SIZE(2…32))

        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x41060300);
        ret = dlt_698_param_0x4106_encode(&current, 3, 1, 1, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame) / sizeof(frame[0]));
            printData("param min_current frame=", frame, ret);
        }
    }
    // 计量规格 breakover_current
    {
        dlt_698_param_0x4106_t current;
        memset(current.breakover_current.data, 0, sizeof(current.breakover_current.data));
        char *breakover_current = "0.015A";
        strcpy(current.breakover_current.data, breakover_current);
        current.breakover_current.len = strlen(breakover_current);    //=visible-string(SIZE(2…32))

        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x41060400);
        ret = dlt_698_param_0x4106_encode(&current, 4, 1, 1, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame) / sizeof(frame[0]));
            printData("param breakover_current frame=", frame, ret);
        }
    }
}
void dlt_698_encode_var(dlt_698_parser *parser)
{
    uint8_t ctrl = DLT_698_FROM_CLIENT | DLT_698_CLIENT_LAUNCH | DLT_698_SUBFRAME_NO | DLT_698_DISTURB_NO | RM_698_FRAME_FUN_3;
    uint8_t frame[256] = {0};
    uint8_t apdu[256] = {0};
    int16_t ret = 0;
    {
        dlt_698_var_0x2015_t meter;
        uint8_t logic[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 1, 2, 3, 4, 5, 6, 7, 8, 9, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 13, 1, 2, 3, 4, 5, 6, 7, 8, 9, 14};

        meter.logic_name.len = sizeof(logic);
        memcpy(meter.logic_name.data, logic, meter.logic_name.len);
        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x20150100);
        ret = dlt_698_var_0x2015_encode(&meter, 1, 1, 1, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            pos += dlt_698_encode_null(apdu + pos, sizeof(apdu) - pos);

            pos += dlt_698_encode_null(apdu + pos, sizeof(apdu) - pos);
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame) / sizeof(frame[0]));
            printData("var meter report tag frame=", frame, ret);
        }
    }
    {
        dlt_698_var_0x2015_t meter;
        memset(&meter, 0, sizeof(meter));
        uint8_t tag[] = {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1};
        memcpy(meter.report_tag, tag, sizeof(tag));

        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x20150200);
        ret = dlt_698_var_0x2015_encode(&meter, 2, 1, 1, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            pos += dlt_698_encode_null(apdu + pos, sizeof(apdu) - pos);    // 填充数据
            pos += dlt_698_encode_null(apdu + pos, sizeof(apdu) - pos);
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame) / sizeof(frame[0]));
            printData("var meter report tag frame=", frame, ret);
        }
    }
}

void dlt_698_encode_power(dlt_698_parser *parser)
{
    uint8_t ctrl = DLT_698_FROM_CLIENT | DLT_698_CLIENT_LAUNCH | DLT_698_SUBFRAME_NO | DLT_698_DISTURB_NO | RM_698_FRAME_FUN_3;
    uint8_t frame[1024] = {0};
    uint8_t apdu[1024] = {0};
    int16_t ret = 0;
    {
        dlt_698_power_0x2004_t power;
        power.valid_power[0] = 201 * 10;
        power.valid_power[1] = 202 * 10;
        ;
        power.valid_power[2] = 203 * 10;
        ;
        power.valid_power[3] = 204 * 10;
        ;
        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x20040200);
        ret = dlt_698_power_0x2004_encode(&power, 2, 1, 4, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame) / sizeof(frame[0]));
            printData("param power frame=", frame, ret);
        }
    }
}

void dlt_698_encode_phase(dlt_698_parser *parser)
{
    uint8_t ctrl = DLT_698_FROM_CLIENT | DLT_698_CLIENT_LAUNCH | DLT_698_SUBFRAME_NO | DLT_698_DISTURB_NO | RM_698_FRAME_FUN_3;
    uint8_t frame[1024] = {0};
    uint8_t apdu[1024] = {0};
    int16_t ret = 0;
    {
        dlt_698_phase_0x2000_t pahse;
        pahse.voltage[0] = 201 * 10;
        pahse.voltage[1] = 202 * 10;
        pahse.voltage[2] = 203 * 10;
        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x20000200);
        ret = dlt_698_phase_0x2000_encode(&pahse, 2, 1, 3, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame) / sizeof(frame[0]));
            printData("param phase voltage frame=", frame, ret);
        }
    }
    {
        dlt_698_phase_0x2000_t pahse;
        pahse.hig_voltage = 201;
        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x20000400);
        ret = dlt_698_phase_0x2000_encode(&pahse, 4, 1, 1, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame) / sizeof(frame[0]));
            printData("param phase high voltage frame=", frame, ret);
        }
    }
}

void dlt_698_encode_pulse(dlt_698_parser *parser)
{
    uint8_t ctrl = DLT_698_FROM_CLIENT | DLT_698_CLIENT_LAUNCH | DLT_698_SUBFRAME_NO | DLT_698_DISTURB_NO | RM_698_FRAME_FUN_3;
    uint8_t frame[1024] = {0};
    uint8_t apdu[1024] = {0};
    int16_t ret = 0;
    {
        dlt_698_pulse_0x2401_t pulse;
        pulse.ratio.pt = 201;
        pulse.ratio.ct = 202;
        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x24010300);
        ret = dlt_698_pulse_0x2401_encode(&pulse, 3, 1, 1, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame) / sizeof(frame[0]));
            printData("param pulse ratio frame=", frame, ret);
        }
    }
    {
        dlt_698_pulse_0x2401_t pulse;
        for (size_t i = 0; i < 2; i++)
        {
            pulse.pluse_cfg[i].oad.st.oi = 0x2001 + i;
            pulse.pluse_cfg[i].oad.st.att_tag = 0x02;
            pulse.pluse_cfg[i].oad.st.att_index = 0x00;
            pulse.pluse_cfg[i].att = 1;
            pulse.pluse_cfg[i].constant = 201 + i;
        }

        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x24010400);
        ret = dlt_698_pulse_0x2401_encode(&pulse, 4, 1, 2, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame) / sizeof(frame[0]));
            printData("param pulse config frame=", frame, ret);
        }
    }
    {
        dlt_698_pulse_0x2401_t pulse;
        pulse.valid_power = 201;

        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x24010500);
        ret = dlt_698_pulse_0x2401_encode(&pulse, 5, 1, 1, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame) / sizeof(frame[0]));
            printData("param pulse valid power frame=", frame, ret);
        }
    }
    {
        dlt_698_pulse_0x2401_t pulse;
        int size = sizeof(pulse.current_day_pos_valid) / sizeof(pulse.current_day_pos_valid[0]);
        for (int i = 0; i < size; i++)
        {
            pulse.current_day_pos_valid[i] = 201 + i;
        }

        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x24010700);
        ret = dlt_698_pulse_0x2401_encode(&pulse, 7, 1, size, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame) / sizeof(frame[0]));
            printData("param pulse current_day_pos_valid power frame=", frame, ret);
        }
    }
}

void dlt_698_encode_esam(dlt_698_parser *parser)
{
    printf("dlt_698_encode_esam-----------\n");
    uint8_t ctrl = DLT_698_FROM_CLIENT | DLT_698_CLIENT_LAUNCH | DLT_698_SUBFRAME_NO | DLT_698_DISTURB_NO | RM_698_FRAME_FUN_3;
    uint8_t frame[1024] = {0};
    uint8_t apdu[1024] = {0};
    int16_t ret = 0;
    {
        dlt_698_esam_F100_t esam;
        esam.talk_time_thr = 30;

        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0xF1000500);
        ret = dlt_698_esam_F100_encode(&esam, 5, 1, 1, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame) / sizeof(frame[0]));
            printData("param att5 talk_time_thr frame=", frame, ret);
        }
    }
    {
        dlt_698_esam_F100_t esam;
        esam.talk_time_remain = 30;

        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0xF1000600);
        ret = dlt_698_esam_F100_encode(&esam, 6, 1, 1, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame) / sizeof(frame[0]));
            printData("param att6 talk_time_remain frame=", frame, ret);
        }
    }
    {
        dlt_698_esam_F100_t esam;
        esam.counter.app_counter = 201;
        esam.counter.report_counter = 202;
        esam.counter.talk_num = 10;

        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0xF1000700);
        ret = dlt_698_esam_F100_encode(&esam, 7, 1, 1, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame) / sizeof(frame[0]));
            printData("param att7 counter frame=", frame, ret);
        }
    }
    {
        dlt_698_esam_F100_t esam;
        memset(&esam.certificate.terminal_version, 0, sizeof(esam.certificate.terminal_version));
        uint8_t version[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
        esam.certificate.terminal_version.len = sizeof(version);
        memcpy(esam.certificate.terminal_version.data, version, sizeof(version));

        memset(&esam.certificate.primary_station_version, 0, sizeof(esam.certificate.primary_station_version));
        esam.certificate.primary_station_version.len = sizeof(version);
        memcpy(esam.certificate.primary_station_version.data, version, sizeof(version));

        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0xF1000800);
        ret = dlt_698_esam_F100_encode(&esam, 8, 1, 1, apdu + pos, sizeof(apdu) - pos);
        printf("ret=%d\n", ret);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame) / sizeof(frame[0]));
            printData("param att8 certificate frame=", frame, ret);
        }
    }
    {
        dlt_698_esam_F100_t esam;
        for (int i = 0; i < 3; i++)
        {
            esam.esam_object[i].st.oi = 0x2001 + i;
            esam.esam_object[i].st.att_tag = 0x02;
            esam.esam_object[i].st.att_index = 0x00;
        }

        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0xF1000D00);
        ret = dlt_698_esam_F100_encode(&esam, 13, 1, 3, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame) / sizeof(frame[0]));
            printData("param att13 esam_object frame=", frame, ret);
        }
    }
}

void dlt_698_encode_harmonic(dlt_698_parser *parser)
{
    uint8_t ctrl = DLT_698_FROM_CLIENT | DLT_698_CLIENT_LAUNCH | DLT_698_SUBFRAME_NO | DLT_698_DISTURB_NO | RM_698_FRAME_FUN_3;
    uint8_t frame[1024] = {0};
    uint8_t apdu[1024] = {0};
    int16_t ret = 0;
    {
        dlt_698_harmonic_0x200d_t harmonic;
        int size = sizeof(harmonic.harm_A) / sizeof(harmonic.harm_A[0]);
        for (int i = 0; i < size; i++)
        {
            harmonic.harm_A[i] = 201 + i;
        }

        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x200d0200);
        ret = dlt_698_harmonic_0x200d_encode(&harmonic, 2, 1, 4, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame) / sizeof(frame[0]));
            printData("harmonic att2 A=", frame, ret);
        }
    }
    {
        dlt_698_harmonic_0x200d_t harmonic;
        harmonic.max_harm = 201;

        int pos = dlt_698_init_apdu(apdu, sizeof(apdu), 2, 0x200d0500);
        ret = dlt_698_harmonic_0x200d_encode(&harmonic, 5, 1, 1, apdu + pos, sizeof(apdu) - pos);
        if (ret > 0)
        {
            pos += ret;
            apdu[pos++] = 0x00;
            apdu[pos++] = 0x00;
            ret = dlt_698_encode(parser, ctrl, apdu, pos, frame, sizeof(frame) / sizeof(frame[0]));
            printData("harmonic att5 max_harm=", frame, ret);
        }
    }
}

void dlt_698_test_get_normal_req(dlt_698_parser *parser)
{
    uint8_t frame[1024] = {0};
    oop_oad oad;
    oad.val = 0x43000300;
    time_t t = time(NULL);
    oop_date_time_s dts;
    dlt_698_convert_dts(t, &dts);
    int16_t ret = dlt_698_encode_get_normal_req(parser, 1, &oad, 1, &dts, frame, 1024);
    printData("get req=", frame, ret);
}

void printData(char *title, uint8_t *frame_ptr, int16_t frame_len)
{
    printf("%s", title);
    for (int i = 0; i < frame_len; i++)
    {
        printf("%02X ", frame_ptr[i]);
    }

    printf("\n");
}
