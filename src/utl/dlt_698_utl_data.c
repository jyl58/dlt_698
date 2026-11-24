#include "dlt_698_utl_data.h"
#include "dlt_698_utl_tools.h"
#include "dlt_698_parser_private.h"
#include "dlt_698_parser_widget.h"

bool dlt_698_get_bool(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_bool *val_ptr)
{
    bool result = false;
    if (!parser || !data_ptr || !val_ptr)
    {
        return result;
    }
    if (data_ptr->type == DLT_698_TYPE_OOP_BOOL)
    {
        int16_t ret = dlt_698_get_data_arry(parser, data_ptr, val_ptr, sizeof(oop_bool));
        if (ret == DLT_698_ERR_NONE)
        {
            result = true;
        }
    }
    return result;
}

bool dlt_698_get_bit_string(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_bit_string *bit_ptr, uint16_t bit_size, uint16_t *real_size)
{
    bool result = false;
    if (!parser || !data_ptr || !bit_ptr || bit_size == 0)    // 指针为空或缓冲区空间不足
    {
        return result;
    }
    memset(bit_ptr, 0, bit_size);    // 清空数据
    *real_size = 0;

    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    if (data_ptr->type == DLT_698_TYPE_OOP_BIT_STRING)
    {
        uint16_t field_len = 0;      // 长度域大小
        uint16_t content_len = 0;    // 数据域大小
        dlt_698_parse_axdr_len(ins_ptr->_payld_ptr + data_ptr->index, &field_len, &content_len);
        if (content_len < bit_size)
        {
            result = true;
            *real_size = content_len;
            uint16_t byte_cnt = (content_len + 7) / 8;    // 计算字节数
            for (uint16_t i = 0; i < byte_cnt; i++)
            {
                uint8_t num = ins_ptr->_payld_ptr[data_ptr->index + field_len + i];
                for (int j = 0; j < 8 && i * 8 + j < content_len; j++)
                {
                    // 计算对应的位
                    bit_ptr[i * 8 + j] = ((num >> (7 - j)) & 0x01);
                }
            }
        }
    }
    return result;
}

bool dlt_698_get_double_long(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_double_long *val_ptr)
{
    bool result = false;
    if (!parser || !data_ptr || !val_ptr)
    {
        return result;
    }
    if (data_ptr->type == DLT_698_TYPE_OOP_DOUBLE_LONG)
    {
        int16_t ret = dlt_698_get_data_arry(parser, data_ptr, (uint8_t *)val_ptr, sizeof(*val_ptr));
        if (ret == DLT_698_ERR_NONE)
        {
            result = true;
            dlt_698_big_reverse(val_ptr, sizeof(*val_ptr));
        }
    }
    return result;
}

bool dlt_698_get_double_long_unsigned(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_double_long_unsigned *val_ptr)
{
    bool result = false;
    if (!parser || !data_ptr || !val_ptr)
    {
        return result;
    }
    if (data_ptr->type == DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED)
    {
        int16_t ret = dlt_698_get_data_arry(parser, data_ptr, (uint8_t *)val_ptr, sizeof(*val_ptr));
        if (ret == DLT_698_ERR_NONE)
        {
            result = true;
            dlt_698_big_reverse(val_ptr, sizeof(*val_ptr));
        }
    }
    return result;
}

bool dlt_698_get_octet_string(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_octet_string *octet_ptr, uint16_t octet_size, uint16_t *real_size)
{
    bool result = false;
    if (!parser || !data_ptr || !octet_ptr || octet_size == 0)    // 指针为空或缓冲区空间不足
    {
        return result;
    }
    memset(octet_ptr, 0, octet_size);    // 清空数据
    *real_size = 0;

    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    if (data_ptr->type == DLT_698_TYPE_OOP_OCTET_STRING)
    {
        uint16_t field_len = 0;      // 长度域大小
        uint16_t content_len = 0;    // 数据域大小
        dlt_698_parse_axdr_len(ins_ptr->_payld_ptr + data_ptr->index, &field_len, &content_len);
        if (content_len < octet_size)
        {
            result = true;
            *real_size = content_len;
            for (uint16_t i = 0; i < content_len; i++)
            {
                octet_ptr[i] = ins_ptr->_payld_ptr[data_ptr->index + field_len + i];
            }
        }
    }
    return result;
}

bool dlt_698_get_visible_string(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_visible_string *visible_ptr, uint16_t visible_size, uint16_t *real_size)
{
    bool result = false;
    if (!parser || !data_ptr || !visible_ptr || visible_size == 0)    // 指针为空或缓冲区空间不足
    {
        return result;
    }
    memset(visible_ptr, 0, visible_size);    // 清空数据
    *real_size = 0;
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    if (data_ptr->type == DLT_698_TYPE_OOP_VISIBLE_STRING)
    {
        uint16_t field_len = 0;      // 长度域大小
        uint16_t content_len = 0;    // 数据域大小
        dlt_698_parse_axdr_len(ins_ptr->_payld_ptr + data_ptr->index, &field_len, &content_len);
        if (content_len < visible_size)
        {
            result = true;
            *real_size = content_len;
            for (uint16_t i = 0; i < content_len; i++)
            {
                visible_ptr[i] = (oop_visible_string)ins_ptr->_payld_ptr[data_ptr->index + field_len + i];
            }
        }
    }
    return result;
}
bool dlt_698_get_utf8_string(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_utf8_string *utf8_ptr, uint16_t utf8_size, uint16_t *real_size)
{
    bool result = false;
    if (!parser || !data_ptr || !utf8_ptr || utf8_size == 0)    // 指针为空或缓冲区空间不足
    {
        return result;
    }
    memset(utf8_ptr, 0, utf8_size);    // 清空数据
    *real_size = 0;

    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    if (data_ptr->type == DLT_698_TYPE_OOP_OCTET_STRING)
    {
        uint16_t field_len = 0;      // 长度域大小
        uint16_t content_len = 0;    // 数据域大小
        dlt_698_parse_axdr_len(ins_ptr->_payld_ptr + data_ptr->index, &field_len, &content_len);
        if (content_len < utf8_size)
        {
            result = true;
            *real_size = content_len;
            for (uint16_t i = 0; i < content_len; i++)
            {
                utf8_ptr[i] = (oop_visible_string)ins_ptr->_payld_ptr[data_ptr->index + field_len + i];
            }
        }
    }
    return result;
}
bool dlt_698_get_integer(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_integer *val_ptr)
{
    bool result = false;
    if (!parser || !data_ptr || !val_ptr)
    {
        return result;
    }
    if (data_ptr->type == DLT_698_TYPE_OOP_INTEGER)
    {
        int16_t ret = dlt_698_get_data_arry(parser, data_ptr, (uint8_t *)val_ptr, sizeof(*val_ptr));
        if (ret == DLT_698_ERR_NONE)
        {
            result = true;
            dlt_698_big_reverse(val_ptr, sizeof(*val_ptr));
        }
    }
    return result;
}
bool dlt_698_get_long(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_long *val_ptr)
{
    bool result = false;
    if (!parser || !data_ptr || !val_ptr)
    {
        return result;
    }
    if (data_ptr->type == DLT_698_TYPE_OOP_LONG)
    {
        int16_t ret = dlt_698_get_data_arry(parser, data_ptr, (uint8_t *)val_ptr, sizeof(*val_ptr));
        if (ret == DLT_698_ERR_NONE)
        {
            result = true;
            dlt_698_big_reverse(val_ptr, sizeof(*val_ptr));
        }
    }
    return result;
}
bool dlt_698_get_unsigned(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_unsigned *val_ptr)
{
    bool result = false;
    if (!parser || !data_ptr || !val_ptr)
    {
        return result;
    }
    if (data_ptr->type == DLT_698_TYPE_OOP_UNSIGNED)
    {
        int16_t ret = dlt_698_get_data_arry(parser, data_ptr, (uint8_t *)val_ptr, sizeof(*val_ptr));
        if (ret == DLT_698_ERR_NONE)
        {
            result = true;
            dlt_698_big_reverse(val_ptr, sizeof(*val_ptr));
        }
    }
    return result;
}
bool dlt_698_get_long_unsigned(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_long_unsigned *val_ptr)
{
    bool result = false;
    if (!parser || !data_ptr || !val_ptr)
    {
        return result;
    }
    if (data_ptr->type == DLT_698_TYPE_OOP_LONG_UNSIGNED)
    {
        int16_t ret = dlt_698_get_data_arry(parser, data_ptr, (uint8_t *)val_ptr, sizeof(*val_ptr));
        if (ret == DLT_698_ERR_NONE)
        {
            result = true;
            dlt_698_big_reverse(val_ptr, sizeof(*val_ptr));
        }
    }
    return result;
}
bool dlt_698_get_long64(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_long64 *val_ptr)
{
    bool result = false;
    if (!parser || !data_ptr || !val_ptr)
    {
        return result;
    }
    if (data_ptr->type == DLT_698_TYPE_OOP_LONG64)
    {
        int16_t ret = dlt_698_get_data_arry(parser, data_ptr, (uint8_t *)val_ptr, sizeof(*val_ptr));
        if (ret == DLT_698_ERR_NONE)
        {
            result = true;
            dlt_698_big_reverse(val_ptr, sizeof(*val_ptr));
        }
    }
    return result;
}
bool dlt_698_get_long64_unsigned(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_long64_unsigned *val_ptr)
{
    bool result = false;
    if (!parser || !data_ptr || !val_ptr)
    {
        return result;
    }
    if (data_ptr->type == DLT_698_TYPE_OOP_LONG64_UNSIGNED)
    {
        int16_t ret = dlt_698_get_data_arry(parser, data_ptr, (uint8_t *)val_ptr, sizeof(*val_ptr));
        if (ret == DLT_698_ERR_NONE)
        {
            result = true;
            dlt_698_big_reverse(val_ptr, sizeof(*val_ptr));
        }
    }
    return result;
}
bool dlt_698_get_enum(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_enum *val_ptr)
{
    bool result = false;
    if (!parser || !data_ptr || !val_ptr)
    {
        return result;
    }
    if (data_ptr->type == DLT_698_TYPE_OOP_ENUM)
    {
        int16_t ret = dlt_698_get_data_arry(parser, data_ptr, (uint8_t *)val_ptr, sizeof(*val_ptr));
        if (ret == DLT_698_ERR_NONE)
        {
            result = true;
            dlt_698_big_reverse(val_ptr, sizeof(*val_ptr));
        }
    }
    return result;
}

bool dlt_698_get_float32(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_float32 *val_ptr)
{
    bool result = false;
    if (!parser || !data_ptr || !val_ptr)
    {
        return result;
    }
    if (data_ptr->type == DLT_698_TYPE_OOP_FLOAT32)
    {
        int16_t ret = dlt_698_get_data_arry(parser, data_ptr, (uint8_t *)val_ptr, sizeof(*val_ptr));
        if (ret == DLT_698_ERR_NONE)
        {
            result = true;
            dlt_698_big_reverse(val_ptr, sizeof(*val_ptr));
        }
    }
    return result;
}

bool dlt_698_get_float64(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_float64 *val_ptr)
{
    bool result = false;
    if (!parser || !data_ptr || !val_ptr)
    {
        return result;
    }
    if (data_ptr->type == DLT_698_TYPE_OOP_FLOAT64)
    {
        int16_t ret = dlt_698_get_data_arry(parser, data_ptr, (uint8_t *)val_ptr, sizeof(*val_ptr));
        if (ret == DLT_698_ERR_NONE)
        {
            result = true;
            dlt_698_big_reverse(val_ptr, sizeof(*val_ptr));
        }
    }
    return result;
}

bool dlt_698_get_date_time(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_date_time *val_ptr)
{
    bool result = false;
    if (!parser || !data_ptr || !val_ptr)
    {
        return result;
    }
    if (data_ptr->type == DLT_698_TYPE_OOP_DATE_TIME)
    {
        int16_t ret = dlt_698_get_data_arry(parser, data_ptr, (uint8_t *)val_ptr, sizeof(*val_ptr));
        if (ret == DLT_698_ERR_NONE)
        {
            result = true;
            dlt_698_big_reverse(&val_ptr->year, sizeof(val_ptr->year));
            dlt_698_big_reverse(&val_ptr->millisecond, sizeof(val_ptr->millisecond));
        }
    }
    return result;
}
bool dlt_698_get_date(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_date *val_ptr)
{
    bool result = false;
    if (!parser || !data_ptr || !val_ptr)
    {
        return result;
    }
    if (data_ptr->type == DLT_698_TYPE_OOP_DATE)
    {
        int16_t ret = dlt_698_get_data_arry(parser, data_ptr, (uint8_t *)val_ptr, sizeof(*val_ptr));
        if (ret == DLT_698_ERR_NONE)
        {
            result = true;
            dlt_698_big_reverse(&val_ptr->year, sizeof(val_ptr->year));
        }
    }
    return result;
}

bool dlt_698_get_time(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_time *val_ptr)
{
    bool result = false;
    if (!parser || !data_ptr || !val_ptr)
    {
        return result;
    }
    if (data_ptr->type == DLT_698_TYPE_OOP_TIME)
    {
        int16_t ret = dlt_698_get_data_arry(parser, data_ptr, (uint8_t *)val_ptr, sizeof(*val_ptr));
        if (ret == DLT_698_ERR_NONE)
        {
            result = true;
        }
    }
    return result;
}
bool dlt_698_get_date_time_s(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_date_time_s *val_ptr)
{
    bool result = false;
    if (!parser || !data_ptr || !val_ptr)
    {
        return result;
    }
    if (data_ptr->type == DLT_698_TYPE_OOP_DATE_TIME_S)
    {
        int16_t ret = dlt_698_get_data_arry(parser, data_ptr, (uint8_t *)val_ptr, sizeof(*val_ptr));
        if (ret == DLT_698_ERR_NONE)
        {
            result = true;
            dlt_698_big_reverse(&val_ptr->year, sizeof(val_ptr->year));
        }
    }
    return result;
}
bool dlt_698_get_oi(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_oi *val_ptr)
{
    bool result = false;
    if (!parser || !data_ptr || !val_ptr)
    {
        return result;
    }
    if (data_ptr->type == DLT_698_TYPE_OOP_OI)
    {
        int16_t ret = dlt_698_get_data_arry(parser, data_ptr, (uint8_t *)val_ptr, sizeof(*val_ptr));
        if (ret == DLT_698_ERR_NONE)
        {
            result = true;
            dlt_698_big_reverse(val_ptr, sizeof(*val_ptr));
        }
    }
    return result;
}
bool dlt_698_get_oad(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_oad *val_ptr)
{
    bool result = false;
    if (!parser || !data_ptr || !val_ptr)
    {
        return result;
    }
    if (data_ptr->type == DLT_698_TYPE_OOP_OAD)
    {
        int16_t ret = dlt_698_get_data_arry(parser, data_ptr, (uint8_t *)val_ptr, sizeof(*val_ptr));
        if (ret == DLT_698_ERR_NONE)
        {
            result = true;
            dlt_698_big_reverse(val_ptr, sizeof(*val_ptr));
        }
    }
    return result;
}

bool dlt_698_get_omd(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_omd *val_ptr)
{
    bool result = false;
    if (!parser || !data_ptr || !val_ptr)
    {
        return result;
    }
    if (data_ptr->type == DLT_698_TYPE_OOP_OMD)
    {
        int16_t ret = dlt_698_get_data_arry(parser, data_ptr, (uint8_t *)val_ptr, sizeof(*val_ptr));
        if (ret == DLT_698_ERR_NONE)
        {
            result = true;
            dlt_698_big_reverse(val_ptr, sizeof(*val_ptr));
        }
    }
    return result;
}

bool dlt_698_get_ti(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_ti *val_ptr)
{
    bool result = false;
    if (!parser || !data_ptr || !val_ptr)
    {
        return result;
    }
    if (data_ptr->type == DLT_698_TYPE_OOP_TI)
    {
        int16_t ret = dlt_698_get_data_arry(parser, data_ptr, (uint8_t *)val_ptr, sizeof(*val_ptr));
        if (ret == DLT_698_ERR_NONE)
        {
            result = true;
            dlt_698_big_reverse(&val_ptr->interval, sizeof(val_ptr->interval));
        }
    }
    return result;
}

bool dlt_698_get_scaler_unit(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_scaler_unit *val_ptr)
{
    bool result = false;
    if (!parser || !data_ptr || !val_ptr)
    {
        return result;
    }
    if (data_ptr->type == DLT_698_TYPE_OOP_SCALER_UNIT)
    {
        int16_t ret = dlt_698_get_data_arry(parser, data_ptr, (uint8_t *)val_ptr, sizeof(*val_ptr));
        if (ret == DLT_698_ERR_NONE)
        {
            result = true;
        }
    }
    return result;
}

bool dlt_698_get_comdcb(dlt_698_parser *parser, dlt_698_data_t *data_ptr, oop_comdcb *val_ptr)
{

    bool result = false;
    if (!parser || !data_ptr || !val_ptr)
    {
        return result;
    }
    if (data_ptr->type == DLT_698_TYPE_OOP_COMDCB)
    {
        int16_t ret = dlt_698_get_data_arry(parser, data_ptr, (uint8_t *)val_ptr, sizeof(*val_ptr));
        if (ret == DLT_698_ERR_NONE)
        {
            result = true;
        }
    }
    return result;
}
