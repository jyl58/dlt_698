#include "dlt_698_class.h"
#include "dlt_698_utl_tools.h"
static bool verify_buff_len(uint16_t data_len, bool tag, uint16_t des_len)
{
    if (tag)
    {
        data_len += 1;
    }
    if (data_len > des_len)
    {
        return false;
    }
    return true;
}

int16_t dlt_698_apdu_encoder(const struct DLT_698_CLASS_INFO *if_tb, void *data, uint8_t att, uint8_t att_index, uint8_t att_len, uint8_t *des_ptr, uint16_t des_len)
{
    if ((NULL == if_tb) || (NULL == data) || (NULL == des_ptr))
    {
        return DLT_698_ERR_EMPTY_PTR;
    }

    int len = 0;
    /*是一个数组变量*/
    if (if_tb[att - 1].arry > 0)
    {
        if (att_index == 0 || att_len == 0 || att_index + att_len - 1 > if_tb[att - 1].arry)
        {
            return DLT_698_ERR_INVALID;
        }
        uint16_t total_len = att_len * if_tb[att - 1].len;
        if (att_len > 1)
        {
            total_len += 2;
        }
        if (total_len > des_len)
        {
            return DLT_698_ERR_OVER;
        }

        if (att_len > 1)
        {
            // 表征是数组
            des_ptr[len++] = DLT_698_TYPE_OOP_ARRAY;
            // 数组成员个数
            des_ptr[len++] = att_len;
        }
        // 数组个数
        for (int i = att_index - 1; i < att_index + att_len - 1; i++)
        {
            // 单个数据
            for (int j = 0; j < if_tb[att - 1].len; j++)
            {
                des_ptr[len++] = *((uint8_t *)data + if_tb[att - 1].offset + i * if_tb[att - 1].len + j);
            }
        }
    }
    else
    {
        if (if_tb[att - 1].len > des_len)
        {
            return DLT_698_ERR_OVER;
        }
        /*非数组变量*/
        for (int i = 0; i < if_tb[att - 1].len; i++)
        {
            des_ptr[len++] = *((uint8_t *)data + if_tb[att - 1].offset + i);
        }
    }
    return len;
}

int16_t dlt_698_encode_header_get(bool req, enum DLT_698_GET_METHOD method, uint8_t piid, uint8_t *des)
{
    if (NULL == des)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    int16_t pos = 0;
    if (req)    /// 请求帧
    {
        des[pos++] = DLT_698_FRAME_TYPE_GET_REQ;
    }
    else    /// 应答帧
    {
        des[pos++] = DLT_698_FRAME_TYPE_GET_RES;
    }
    des[pos++] = method;
    des[pos++] = piid;
    return pos;
}
int16_t dlt_698_encode_header_set(bool req, enum DLT_698_SET_METHOD method, uint8_t piid, uint8_t *des)
{
    if (NULL == des)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    int16_t pos = 0;
    if (req)    /// 请求帧
    {
        des[pos++] = DLT_698_FRAME_TYPE_SET_REQ;
    }
    else    /// 应答帧
    {
        des[pos++] = DLT_698_FRAME_TYPE_SET_RES;
    }
    des[pos++] = method;
    des[pos++] = piid;
    return pos;
}
int16_t dlt_698_encode_header_act(bool req, enum DLT_698_ACT_METHOD method, uint8_t piid, uint8_t *des)
{
    if (NULL == des)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    int16_t pos = 0;
    if (req)    /// 请求帧
    {
        des[pos++] = DLT_698_FRAME_TYPE_ACT_REQ;
    }
    else    /// 应答帧
    {
        des[pos++] = DLT_698_FRAME_TYPE_ACT_RES;
    }
    des[pos++] = method;
    des[pos++] = piid;
    return pos;
}
int16_t dlt_698_encode_header_report(bool report, enum DLT_698_ACT_METHOD method, uint8_t piid, uint8_t *des)
{
    if (NULL == des)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    int16_t pos = 0;
    if (report)    /// 通知上报
    {
        des[pos++] = DLT_698_FRAME_TYPE_REP_REQ;
    }
    else    /// 响应上报
    {
        des[pos++] = DLT_698_FRAME_TYPE_ACT_RES;
    }
    des[pos++] = method;
    des[pos++] = piid;
    return pos;
}

int16_t dlt_698_encode_null(uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 判断总长度是否超过缓冲区长度
    if (1 > des_len)
    {
        return DLT_698_ERR_OVER;
    }
    int pos = 0;
    des_ptr[pos++] = 0x00;
    return pos;
}

int16_t dlt_698_encode_array(uint8_t cnt, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 判断总长度是否超过缓冲区长度
    if (2 > des_len)
    {
        return DLT_698_ERR_OVER;
    }
    int pos = 0;
    des_ptr[pos++] = DLT_698_TYPE_OOP_ARRAY;
    des_ptr[pos++] = cnt;
    return pos;
}

int16_t dlt_698_encode_struct(uint8_t cnt, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 判断总长度是否超过缓冲区长度
    if (2 > des_len)
    {
        return DLT_698_ERR_OVER;
    }
    int pos = 0;
    des_ptr[pos++] = DLT_698_TYPE_OOP_STRUCT;
    des_ptr[pos++] = cnt;
    return pos;
}

int16_t dlt_698_encode_bool(oop_bool val, bool tag, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(sizeof(val), tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }

    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_BOOL;
    }
    dlt_698_big_reverse(&val, sizeof(val));
    memcpy(des_ptr + pos, &val, sizeof(val));
    pos += sizeof(val);
    return pos;
}

int16_t dlt_698_encode_bit_string(oop_bit_string *bit_ptr, uint16_t bit_len, bool tag, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }

    // 计算长度域实际占用字节数
    uint8_t len_arr[3] = {0};
    int16_t real_size = dlt_698_set_axdr_len(bit_len, len_arr);
    // 计算占用字节长度
    int16_t byete_len = (bit_len + 7) / 8;
    int16_t total_len = byete_len + real_size;

    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(total_len, tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }

    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_BIT_STRING;
    }
    memcpy(des_ptr + pos, len_arr, real_size);
    pos += real_size;
    int16_t real_len = dlt_698_bit_string_to_hex(bit_ptr, bit_len, des_ptr + pos);
    pos += real_len;
    return pos;
}

int16_t dlt_698_encode_double_long(oop_double_long val, bool tag, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(sizeof(val), tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }

    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_DOUBLE_LONG;
    }
    dlt_698_big_reverse(&val, sizeof(val));
    memcpy(des_ptr + pos, &val, sizeof(val));
    pos += sizeof(val);
    return pos;
}

int16_t dlt_698_encode_double_long_unsigned(oop_double_long_unsigned val, bool tag, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(sizeof(val), tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }

    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
    }
    dlt_698_big_reverse(&val, sizeof(val));
    memcpy(des_ptr + pos, &val, sizeof(val));
    pos += sizeof(val);
    return pos;
}

int16_t dlt_698_encode_octet_string(oop_octet_string *octet_ptr, uint16_t octet_len, bool tag, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }

    // 计算长度域实际占用字节数
    uint8_t len_arr[3] = {0};
    int16_t real_size = dlt_698_set_axdr_len(octet_len, len_arr);
    int16_t total_len = octet_len + real_size;
    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(total_len, tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }

    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_OCTET_STRING;
    }
    memcpy(des_ptr + pos, len_arr, real_size);
    pos += real_size;
    memcpy(des_ptr + pos, octet_ptr, octet_len);
    pos += octet_len;
    return pos;
}

int16_t dlt_698_encode_visible_string(oop_visible_string *visible_ptr, uint16_t visible_len, bool tag, void *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }

    // 计算长度域实际占用字节数
    uint8_t len_arr[3] = {0};
    int16_t real_size = dlt_698_set_axdr_len(visible_len, len_arr);
    int16_t total_len = visible_len + real_size;
    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(total_len, tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }

    uint8_t *data_ptr = (uint8_t *)des_ptr;
    int16_t pos = 0;
    if (tag)
    {
        data_ptr[pos++] = DLT_698_TYPE_OOP_VISIBLE_STRING;
    }
    memcpy(data_ptr + pos, len_arr, real_size);
    pos += real_size;
    memcpy(data_ptr + pos, visible_ptr, visible_len);
    pos += visible_len;
    return pos;
}

int16_t dlt_698_encode_utf8_string(oop_utf8_string *utf8_ptr, uint16_t utf8_len, bool tag, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }

    // 计算长度域实际占用字节数
    uint8_t len_arr[3] = {0};
    int16_t real_size = dlt_698_set_axdr_len(utf8_len, len_arr);
    int16_t total_len = utf8_len + real_size;
    // 带数据标签域，总长度+1
    if (tag)
    {
        total_len += 1;
    }
    // 判断总长度是否超过缓冲区长度
    if (total_len > des_len)
    {
        return DLT_698_ERR_OVER;
    }

    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_UTF8_STRING;
    }
    memcpy(des_ptr + pos, len_arr, real_size);
    pos += real_size;
    memcpy(des_ptr + pos, utf8_ptr, utf8_len);
    pos += utf8_len;
    return pos;
}

int16_t dlt_698_encode_integer(oop_integer val, bool tag, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(sizeof(val), tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }

    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_INTEGER;
    }
    dlt_698_big_reverse(&val, sizeof(val));
    memcpy(des_ptr + pos, &val, sizeof(val));
    pos += sizeof(val);
    return pos;
}

int16_t dlt_698_encode_long(oop_long val, bool tag, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(sizeof(val), tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }

    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_LONG;
    }
    dlt_698_big_reverse(&val, sizeof(val));
    memcpy(des_ptr + pos, &val, sizeof(val));
    pos += sizeof(val);
    return pos;
}

int16_t dlt_698_encode_unsigned(oop_unsigned val, bool tag, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(sizeof(val), tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }

    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_UNSIGNED;
    }
    dlt_698_big_reverse(&val, sizeof(val));
    memcpy(des_ptr + pos, &val, sizeof(val));
    pos += sizeof(val);
    return pos;
}

int16_t dlt_698_encode_long_unsigned(oop_long_unsigned val, bool tag, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(sizeof(val), tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }

    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_LONG_UNSIGNED;
    }
    dlt_698_big_reverse(&val, sizeof(val));
    memcpy(des_ptr + pos, &val, sizeof(val));
    pos += sizeof(val);
    return pos;
}

int16_t dlt_698_encode_long64(oop_long64 val, bool tag, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }

    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(sizeof(val), tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }

    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_LONG64;
    }
    dlt_698_big_reverse(&val, sizeof(val));
    memcpy(des_ptr + pos, &val, sizeof(val));
    pos += sizeof(val);
    return pos;
}

int16_t dlt_698_encode_long64_unsigned(oop_long64_unsigned val, bool tag, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(sizeof(val), tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }

    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_LONG64_UNSIGNED;
    }
    dlt_698_big_reverse(&val, sizeof(val));
    memcpy(des_ptr + pos, &val, sizeof(val));
    pos += sizeof(val);
    return pos;
}

int16_t dlt_698_encode_enum(oop_enum val, bool tag, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(sizeof(val), tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }

    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_ENUM;
    }

    memcpy(des_ptr + pos, &val, sizeof(oop_enum));
    pos += sizeof(oop_enum);
    return pos;
}

int16_t dlt_698_encode_float32(oop_float32 val, bool tag, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(sizeof(val), tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }
    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_FLOAT32;
    }
    dlt_698_big_reverse(&val, sizeof(oop_float32));
    memcpy(des_ptr + pos, &val, sizeof(oop_float32));
    pos += sizeof(oop_float32);
    return pos;
}

int16_t dlt_698_encode_float64(oop_float64 val, bool tag, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(sizeof(val), tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }

    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_FLOAT64;
    }
    dlt_698_big_reverse(&val, sizeof(oop_float64));
    memcpy(des_ptr + pos, &val, sizeof(oop_float64));
    pos += sizeof(oop_float64);
    return pos;
}

int16_t dlt_698_encode_oad(oop_oad oad, bool tag, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(sizeof(oad), tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }
    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_OAD;
    }
    dlt_698_big_reverse(&oad, sizeof(oad));
    memcpy(des_ptr + pos, &oad, sizeof(oad));
    pos += sizeof(oad);
    return pos;
}
int16_t dlt_698_encode_omd(oop_omd omd, bool tag, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(sizeof(omd), tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }

    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_OMD;
    }
    dlt_698_big_reverse(&omd, sizeof(oop_omd));
    memcpy(des_ptr + pos, &omd, sizeof(oop_omd));
    pos += sizeof(oop_omd);
    return pos;
}

int16_t dlt_698_encode_date_time(oop_date_time dt, bool tag, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(sizeof(dt), tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }

    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_DATE_TIME;
    }
    dlt_698_big_reverse(&dt.year, sizeof(dt.year));
    dlt_698_big_reverse(&dt.millisecond, sizeof(dt.millisecond));
    memcpy(des_ptr + pos, &dt, sizeof(oop_date_time));
    pos += sizeof(oop_date_time);
    return pos;
}

int16_t dlt_698_encode_date(oop_date dt, bool tag, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(sizeof(dt), tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }

    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_DATE;
    }
    dlt_698_big_reverse(&dt.year, sizeof(dt.year));
    memcpy(des_ptr + pos, &dt, sizeof(oop_date));
    pos += sizeof(oop_date);
    return pos;
}

int16_t dlt_698_encode_time(oop_time ti, bool tag, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(sizeof(ti), tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }

    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_TIME;
    }

    memcpy(des_ptr + pos, &ti, sizeof(oop_time));
    pos += sizeof(oop_time);
    return pos;
}

int16_t dlt_698_encode_date_time_s(oop_date_time_s dts, bool tag, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(sizeof(dts), tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }

    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_DATE_TIME_S;
    }
    dlt_698_big_reverse(&dts.year, sizeof(dts.year));
    memcpy(des_ptr + pos, &dts, sizeof(oop_date_time_s));
    pos += sizeof(oop_date_time_s);
    return pos;
}
int16_t dlt_698_encode_ti(oop_ti ti, bool tag, uint8_t *des_ptr, uint16_t des_len)
{
    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(sizeof(ti), tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }

    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_TI;
    }
    dlt_698_big_reverse(&ti.interval, sizeof(ti.interval));
    memcpy(des_ptr + pos, &ti, sizeof(oop_ti));
    pos += sizeof(oop_ti);
    return pos;
}
int16_t dlt_698_encode_comdcb(oop_comdcb com, bool tag, uint8_t *des_ptr, uint16_t des_len)
{

    if (des_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    // 判断总长度是否超过缓冲区长度
    if (false == verify_buff_len(sizeof(com), tag, des_len))
    {
        return DLT_698_ERR_OVER;
    }

    int16_t pos = 0;
    if (tag)
    {
        des_ptr[pos++] = DLT_698_TYPE_OOP_COMDCB;
    }

    memcpy(des_ptr + pos, &com, sizeof(oop_comdcb));
    pos += sizeof(oop_comdcb);
    return pos;
}
int16_t dlt_698_set_axdr_len(uint16_t len, uint8_t *des_ptr)
{
    int pos = 0;
    if (0 <= len && len < 128)    // 1个字节
    {
        des_ptr[pos++] = len;
    }
    else if (len >= 128 && len < 256)
    {
        des_ptr[pos++] = 0x81;
        des_ptr[pos++] = len;
    }
    else if (len >= 128)    // 2个字节
    {
        des_ptr[pos++] = 0x82;
        des_ptr[pos++] = len >> 8;
        des_ptr[pos++] = len;
    }
    return pos;
}
int16_t dlt_698_encode_get_normal_req(dlt_698_parser *parser, uint8_t piid, oop_oad *oad_ptr, uint8_t oad_cnt, oop_date_time_s *dts_ptr, uint8_t *dlt_ptr, uint16_t dlt_size)
{
    uint8_t ctrl = DLT_698_FROM_CLIENT | DLT_698_CLIENT_LAUNCH | DLT_698_SUBFRAME_NO | DLT_698_DISTURB_NO | RM_698_FRAME_FUN_3;
    if (NULL == dlt_ptr || NULL == oad_ptr || oad_cnt == 0)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    uint8_t apdu[512] = {0};
    int pos = 0;
    apdu[pos++] = DLT_698_FRAME_TYPE_GET_REQ;
    if (oad_cnt == 1)
    {
        apdu[pos++] = DLT_698_GET_METHOD_NOR;
        apdu[pos++] = piid;
    }
    else
    {
        apdu[pos++] = DLT_698_GET_METHOD_NOR_LIST;
        apdu[pos++] = piid;
        apdu[pos++] = oad_cnt;
    }
    for (int i = 0; i < oad_cnt; i++)
    {
        /*每个OAD占4字节，编码前先检查剩余空间，并检查返回值防止pos回退为负*/
        if (pos + 4 > (int)sizeof(apdu))
        {
            return DLT_698_ERR_OVER;
        }
        int16_t oad_ret = dlt_698_encode_oad(oad_ptr[i], false, apdu + pos, (uint16_t)(sizeof(apdu) - pos));
        if (oad_ret < 0)
        {
            return oad_ret;
        }
        pos += oad_ret;
    }
    if (dts_ptr)
    {
        /*时间标签域标志1字节+时间标签7字节*/
        if (pos + 8 > (int)sizeof(apdu))
        {
            return DLT_698_ERR_OVER;
        }
        apdu[pos++] = 0x01;    // 有时间标签域
        int16_t dts_ret = dlt_698_encode_date_time_s(*dts_ptr, false, apdu + pos, (uint16_t)(sizeof(apdu) - pos));
        if (dts_ret < 0)
        {
            return dts_ret;
        }
        pos += dts_ret;
    }
    else
    {
        if (pos + 1 > (int)sizeof(apdu))
        {
            return DLT_698_ERR_OVER;
        }
        apdu[pos++] = 0x00;    // 无时间标签域
    }
    int32_t ret = dlt_698_encode(parser, ctrl, apdu, pos, dlt_ptr, dlt_size);
    return ret;
}

int16_t dlt_698_init_apdu(uint8_t *apdu_ptr, uint16_t apdu_len, uint8_t piid, uint32_t oad)
{
    if (NULL == apdu_ptr || apdu_len < 7)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    memset(apdu_ptr, 0, apdu_len);
    int pos = 0;
    pos += dlt_698_encode_header_get(0, DLT_698_GET_METHOD_NOR, piid, apdu_ptr + pos);

    apdu_ptr[pos++] = oad >> 24;
    apdu_ptr[pos++] = oad >> 16;
    apdu_ptr[pos++] = oad >> 8;
    apdu_ptr[pos++] = oad;

    apdu_ptr[pos++] = 0x01;
    return pos;
}