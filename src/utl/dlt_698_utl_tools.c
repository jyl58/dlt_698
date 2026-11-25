#include "dlt_698_utl_tools.h"
#include "dlt_698_utl_take.h"
#include "dlt_698_parser_private.h"
#include "dlt_698_utl_print.h"

int16_t dlt_698_get_data_arry(dlt_698_parser *parser, dlt_698_data_t *data_ptr, uint8_t *arry_ptr, int arry_len)
{
    if ((NULL == parser) || (NULL == parser->_ins) || (NULL == data_ptr) || (NULL == arry_ptr))
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    if (arry_len < data_ptr->len)
    {
        return DLT_698_ERR_OVER;
    }
    if (ins_ptr->_payld_len < (data_ptr->index + data_ptr->len))
    {
        return DLT_698_ERR_TAKE;
    }
    for (int i = 0; i < data_ptr->len; i++)
    {
        arry_ptr[i] = ins_ptr->_payld_ptr[data_ptr->index + i];
    }
    return DLT_698_ERR_NONE;
}
void *dlt_698_get_child_ptr(dlt_698_parser *parser, uint16_t child_index)
{
    if ((NULL == parser) || (NULL == parser->_ins))
    {
        return NULL;
    }
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    void *child_ptr = NULL;
    if (child_index > 0)
    {
        child_ptr = (void *)(ins_ptr->_mem.start + child_index);
    }
    return child_ptr;
}
void *dlt_698_get_next_ptr(dlt_698_parser *parser, uint16_t next_index)
{
    if ((NULL == parser) || (NULL == parser->_ins))
    {
        return NULL;
    }
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    void *next_ptr = NULL;
    if (next_index > 0)
    {
        next_ptr = (void *)(ins_ptr->_mem.start + next_index);
    }
    return next_ptr;
}
int dlt_698_get_data_children_cnt(dlt_698_parser *parser, dlt_698_data_t *parent_ptr)
{
    if ((NULL == parser) || (NULL == parser->_ins))
    {
        return 0;
    }
    int cnt = 0;
    if (parent_ptr && parent_ptr->child_index > 0)
    {
        dlt_698_data_t *child_ptr = (dlt_698_data_t *)dlt_698_get_child_ptr(parser, parent_ptr->child_index);
        while (child_ptr)
        {
            cnt++;
            child_ptr = (dlt_698_data_t *)dlt_698_get_next_ptr(parser, child_ptr->next_index);
        }
    }
    return cnt;
}
int dlt_698_get_data_sibling_cnt(dlt_698_parser *parser, dlt_698_data_t *data_ptr)
{
    if ((NULL == parser) || (NULL == parser->_ins))
    {
        return 0;
    }
    int cnt = 0;
    while (data_ptr)
    {
        cnt++;
        data_ptr = (dlt_698_data_t *)dlt_698_get_next_ptr(parser, data_ptr->next_index);
    }
    return cnt;
}
int dlt_698_get_common_sibling_cnt(dlt_698_parser *parser, void *data_ptr, uint16_t offset)
{
    if ((NULL == parser) || (NULL == parser->_ins))
    {
        return 0;
    }
    int cnt = 0;
    while (data_ptr)
    {
        cnt++;
        uint16_t next_index; /* memcpy 读取: 节点来自内存池, 成员可能落在非对齐地址, 直接解引用是未定义行为 */
        memcpy(&next_index, (const uint8_t *)data_ptr + offset, sizeof(next_index));
        if (next_index > 0)
        {
            data_ptr = dlt_698_get_next_ptr(parser, next_index);
        }
        else
        {
            data_ptr = NULL;
        }
    }
    return cnt;
}
int16_t dlt_698_equal_data(dlt_698_parser *parser, dlt_698_data_t *data_ptr, enum DLT_698_DATA_TYPE data_type, uint8_t *arry_ptr, uint16_t arry_len)
{
    if ((NULL == parser) || (NULL == parser->_ins) || (NULL == data_ptr) || (NULL == arry_ptr))
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    uint8_t temp_data[1024] = {0};
    if (data_type != data_ptr->type)
    {
        return DLT_698_ERR_TYPE;
    }
    else if (arry_len != data_ptr->len)
    {
        return DLT_698_ERR_LEN;
    }
    else
    {
        int16_t res = dlt_698_get_data_arry(parser, data_ptr, temp_data, sizeof(temp_data) / sizeof(temp_data[0]));
        if (res != DLT_698_ERR_NONE)
        {
            return res;
        }
        if (0 == memcmp(temp_data, arry_ptr, arry_len))
        {
            return DLT_698_ERR_NONE;
        }
    }

    return DLT_698_ERR_DATA;
}

int16_t dlt_698_find_data(dlt_698_parser *parser, dlt_698_data_t *data_ptr, dlt_698_data_t **node_ptr, enum DLT_698_DATA_TYPE data_type, uint8_t *arry_ptr, uint16_t arry_len)
{
    *node_ptr = NULL;
    if ((NULL == parser) || (NULL == parser->_ins) || (NULL == data_ptr) || (NULL == arry_ptr))
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    int16_t res = dlt_698_equal_data(parser, data_ptr, data_type, arry_ptr, arry_len);
    if (res == DLT_698_ERR_NONE)    ///< 一致
    {
        *node_ptr = data_ptr;
        return DLT_698_ERR_NONE;
    }

    dlt_698_data_t *child_ptr = dlt_698_get_child_ptr(parser, data_ptr->child_index);
    if (child_ptr)
    {
        res = dlt_698_find_data(parser, child_ptr, node_ptr, data_type, arry_ptr, arry_len);
        if (res == DLT_698_ERR_NONE)
        {
            return DLT_698_ERR_NONE;
        }
    }

    dlt_698_data_t *next_ptr = dlt_698_get_next_ptr(parser, data_ptr->next_index);
    if (next_ptr)
    {
        res = dlt_698_find_data(parser, next_ptr, node_ptr, data_type, arry_ptr, arry_len);
        if (res == DLT_698_ERR_NONE)
        {
            return DLT_698_ERR_NONE;
        }
    }


    return DLT_698_ERR_FIND;
}

///< 判断是否为小端模式
int is_little_endian()
{
    uint16_t val = 0x0001;
    uint8_t *uc = (uint8_t *)&val;
    return (*uc == 0x01);
}
///< u16转换为大端数据
uint16_t dlt_698_to_big_endian_u16(uint16_t val)
{
    if (is_little_endian())
    {
        val = (val >> 8) | (val << 8);
    }
    return val;
}
///< u32转换为大端数据
uint32_t dlt_698_to_big_endian_u32(uint32_t val)
{
    if (is_little_endian())
    {
        val = ((val & 0xFF000000) >> 24) | ((val & 0x00FF0000) >> 8) | ((val & 0x0000FF00) << 8) | ((val & 0x000000FF) << 24);
    }
    return val;
}
int16_t dlt_698_big_endian(void *dst_ptr, void *src_ptr, int src_size)
{
    if (dst_ptr == NULL || src_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    if (is_little_endian())
    {
        uint8_t *src_data = src_ptr;
        uint8_t *dst_data = dst_ptr;
        for (int i = 0; i < src_size; i++)
        {
            dst_data[i] = src_data[src_size - 1 - i];
        }
    }
    return DLT_698_ERR_NONE;
}
int16_t dlt_698_big_reverse(void *data_ptr, int size)
{
    if (data_ptr == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    if (is_little_endian())
    {
        uint8_t *val_ptr = data_ptr;
        for (int i = 0; i < size / 2; i++)
        {
            uint8_t temp = val_ptr[i];
            val_ptr[i] = val_ptr[size - 1 - i];
            val_ptr[size - 1 - i] = temp;
        }
    }
    return DLT_698_ERR_NONE;
}

int16_t dlt_698_bit_string_to_hex(uint8_t *bit_ptr, int bit_len, uint8_t *hex_ptr)
{
    if ((NULL == bit_ptr) || (bit_len == 0) || (NULL == hex_ptr))
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    int16_t byteLen = (bit_len + 8 - 1) / 8;    // 每8个二进制位对应1个字节
    for (size_t i = 0; i < byteLen; ++i)
    {
        uint8_t byte = 0;
        for (size_t j = 0, pos = i * 8; j < 8 && pos < bit_len; j++, pos++)
        {
            if (bit_ptr[pos] == 1)
            {
                byte |= (1 << (7 - j));
            }
        }
        hex_ptr[i] = byte;
    }
    return byteLen;
}
void dlt_698_str_to_dts(const char *ti, oop_date_time_s *dts)
{
    if (!ti || !dts)
    {
        return;
    }
    struct tm dateime = {0};
    sscanf(ti, "%d-%d-%d %d:%d:%d", &dateime.tm_year, &dateime.tm_mon, &dateime.tm_mday, &dateime.tm_hour, &dateime.tm_min, &dateime.tm_sec);
    dts->year = dateime.tm_year;
    dts->month = dateime.tm_mon;
    dts->day = dateime.tm_mday;
    dts->hour = dateime.tm_hour;
    dts->minute = dateime.tm_min;
    dts->second = dateime.tm_sec;
}
void dlt_698_convert_dts(const time_t ti, oop_date_time_s *dts)
{
    if (NULL == dts)
    {
        return;
    }
    struct tm *timeinfo = localtime(&ti);
    dts->year = timeinfo->tm_year + 1900;
    dts->month = timeinfo->tm_mon + 1;
    dts->day = timeinfo->tm_mday;
    dts->hour = timeinfo->tm_hour;
    dts->minute = timeinfo->tm_min;
    dts->second = timeinfo->tm_sec;
}
