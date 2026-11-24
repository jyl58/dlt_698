#include "dlt_698_parser_widget.h"
#include "dlt_698_parser.h"
typedef int16_t (*dlt_698_data_handle)(struct DLT_698_PRIVATE *, dlt_698_data_t *);
// /*698规范：7章定义的每个数据类型的处理函数*/
static const dlt_698_data_handle dlt_698_data_handle_tb[] = {
    dlt_698_parse_null,                    // NULL
    dlt_698_parse_arry,                    //[1]数组内元素长度需要实际解析
    dlt_698_parse_struct,                  //[2]结构内元素长度需要实际解析
    dlt_698_parse_bool,                    //[3]bool
    dlt_698_parse_bit_string,              //[4]位串：目前按后第一个字节表示位串类型，第二个字节是长度
    dlt_698_parse_double_long,             //[5]，确定的值，无需跟长度
    dlt_698_parse_double_long_unsigned,    //[6]，确定的值，无需跟长度
    NULL,                                  //[7]保留
    NULL,                                  //[8]保留
    dlt_698_parse_octet_string,            //[9]字节串，需要根据内容解析,后边需跟着一个长度值
    dlt_698_parse_visible_string,          //[10]字符串，需要根据内容解析,后边需跟着一个长度值
    NULL,                                  //[11]保留
    dlt_698_parse_octet_utf8_string,       //[12]UTF8字符串,后边需跟着一个长度值
    NULL,                                  //[13]保留
    NULL,                                  //[14]保留
    dlt_698_parse_integer,                 //[15]8位整数
    dlt_698_parse_long,                    //[16]16位整数
    dlt_698_parse_unsigned,                //[17] unsigned==uint8_t,  确定的值，无需跟长度
    dlt_698_parse_long_unsigned,           //[18]16位正整数，确定的值，无需跟长度
    NULL,                                  //[19]保留
    dlt_698_parse_long64,                  //[20]64位整数
    dlt_698_parse_long64_unsigned,         //[21]64位正整数，确定的值，无需跟长度
    dlt_698_parse_enum,                    //[22] //enum==u8枚举的元素在对象属性或方法的描述中定义，确定的值，无需跟长度
    dlt_698_parse_float32,                 //[23]32位浮点数，确定的值，无需跟长度
    dlt_698_parse_float64,                 //[24]64位浮点数，确定的值，无需跟长度
    dlt_698_parse_date_time,               //[25]date_time    25    octet-string（SIZE（10）），确定的值，无需跟长度
    dlt_698_parse_date,                    //[26]date    26    octet-string（SIZE（5）），确定的值，无需跟长度
    dlt_698_parse_time,                    //[27]time    27    octet-string（SIZE（3）），确定的值，无需跟长度
    dlt_698_parse_date_time_s,             //[28]date_time_s    28    octet-string（SIZE（7）），确定的值，无需跟长度
    NULL,                                  //[29]--[79]保留
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,    //[39]保留
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,    //[50]保留
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,    //[60]保留
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,    //[68]保留
    NULL,
    NULL,    //[70]保留
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,                         //[79]保留
    dlt_698_parse_oi,             //[80]OI，确定的值，无需跟长度
    dlt_698_parse_oad,            //[81]OAD，确定的值，无需跟长度
    dlt_698_parse_road,           //[82]
    dlt_698_parse_omd,            //[83]
    dlt_698_parse_ti,             //[84]    TI{单位 :ENUMERATED{秒:0;分:1;时:2;日:3月:4;年:5}，间隔值  long-unsigned}}
    dlt_698_parse_tsa,            //[85]   TSA∷=octet-string(SIZE(2…17));需要根据内容解析,后边需跟着一个长度值
    dlt_698_parse_mac,            //[86]   MAC∷=octet-string 需要根据内容解析,后边需跟着一个长度值
    dlt_698_parse_rn,             //[87]    RN∷=octet-string
    dlt_698_parse_region,         //[88] Region 见7.3.13　
    dlt_698_parse_scaler_unit,    //[89]Scaler_Unit
    dlt_698_parse_rsd,            //[90]  RSD
    dlt_698_parse_csd,            //[91]   需要根据后边跟的数据类型进行解析实际长度；CSD∷=CHOICE{对象属性描述符  [0] OAD，记录型对象属性描述符 [1] ROAD}
    dlt_698_parse_ms,             //[92]    见7.3.17　
    dlt_698_parse_sid,            //[93] //SID 见7.3.18　
    dlt_698_parse_sid_mac,        //[94] SID_MAC见7.3.19　
    dlt_698_parse_comdcb,         //[95] COMDCB
    dlt_698_parse_rcsd,           //[96]
};
void dlt_698_append_childNode(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *fatherNode, uint16_t child_index)
{
    if (fatherNode->child_index == 0)
    {
        fatherNode->child_index = child_index;
        return;
    }
    dlt_698_data_t *node = (dlt_698_data_t *)(ins_ptr->_mem.start + fatherNode->child_index);
    while (node->next_index != 0)
    {
        node = (dlt_698_data_t *)(ins_ptr->_mem.start + node->next_index);
    }
    node->next_index = child_index;
}
int16_t dlt_698_parse_data(struct DLT_698_PRIVATE *ins_ptr, uint8_t data_type, dlt_698_data_t *data_ptr)
{
    if (data_type < sizeof(dlt_698_data_handle_tb) / sizeof(dlt_698_data_handle_tb[0]))
    {
        if (NULL != dlt_698_data_handle_tb[data_type])
        {
            return dlt_698_data_handle_tb[data_type](ins_ptr, data_ptr);
        }
        else
        {
            return DLT_698_ERR_INVALID;
        }
    }
    else
    {
        return DLT_698_ERR_INVALID;
    }
    return DLT_698_ERR_NONE;
}
int16_t dlt_698_parse_null(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_NULL;
    data_ptr->len = 0;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
int16_t dlt_698_parse_arry(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    // 先拿到数组个数数据
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_ARRAY;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    if (dlt_698_payld_remain(ins_ptr) < 1)
    {
        return DLT_698_ERR_OVER;
    }
    uint16_t arry_cnt = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    // 挨着解析每个数组元素，
    for (int i = 0; i < arry_cnt; i++)
    {
        uint16_t child_index = ins_ptr->_mem.alloc_mempool_size;
        dlt_698_data_t *node_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
        if (node_ptr == NULL)
        {
            return DLT_698_ERR_MEM;
        }
        dlt_698_append_childNode(ins_ptr, data_ptr, child_index);
        if (dlt_698_payld_remain(ins_ptr) < 1)
        {
            return DLT_698_ERR_OVER;
        }
        uint8_t data_type = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
        int16_t ret = dlt_698_parse_data(ins_ptr, data_type, node_ptr);
        if (ret != DLT_698_ERR_NONE)
        {
            return ret;
        }
    }
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    return DLT_698_ERR_NONE;
}
int16_t dlt_698_parse_struct(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    int16_t ret = dlt_698_parse_arry(ins_ptr, data_ptr);
    data_ptr->type = DLT_698_TYPE_OOP_STRUCT;
    return ret;
}
int16_t dlt_698_parse_bool(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->type = DLT_698_TYPE_OOP_BOOL;
    data_ptr->index = ins_ptr->_payld_index;
    if (sizeof(oop_bool) > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += sizeof(oop_bool);
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**解析Bit string数据结构 */
int16_t dlt_698_parse_bit_string(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->type = DLT_698_TYPE_OOP_BIT_STRING;
    data_ptr->index = ins_ptr->_payld_index;
    uint16_t field_len = 0;
    uint16_t content_len = 0;
    int16_t ret = dlt_698_parse_axdr_len(ins_ptr->_payld_ptr + ins_ptr->_payld_index, dlt_698_payld_remain(ins_ptr), &field_len, &content_len);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    uint16_t byte_len = (uint16_t)(field_len + (content_len + 7) / 8);
    if (byte_len > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += byte_len;
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**解析double-long */
int16_t dlt_698_parse_double_long(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_DOUBLE_LONG;
    if (sizeof(oop_double_long) > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += sizeof(oop_double_long);
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**解析double-long-unsigned */
int16_t dlt_698_parse_double_long_unsigned(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_DOUBLE_LONG_UNSIGNED;
    if (sizeof(oop_double_long_unsigned) > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += sizeof(oop_double_long_unsigned);
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**
 * 8位字节串
 */
int16_t dlt_698_parse_octet_string(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    // 返回携带的数据长度值，并前移一个字节
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_OCTET_STRING;
    uint16_t field_len = 0;
    uint16_t content_len = 0;
    int16_t ret = dlt_698_parse_axdr_len(ins_ptr->_payld_ptr + ins_ptr->_payld_index, dlt_698_payld_remain(ins_ptr), &field_len, &content_len);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    uint16_t data_len = (uint16_t)(field_len + content_len);
    if (data_len > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += data_len;
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**
 * ASCII字符串
 */
int16_t dlt_698_parse_visible_string(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    // 返回携带的数据长度值，并前移一个字节
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_VISIBLE_STRING;
    uint16_t field_len = 0;
    uint16_t content_len = 0;
    int16_t ret = dlt_698_parse_axdr_len(ins_ptr->_payld_ptr + ins_ptr->_payld_index, dlt_698_payld_remain(ins_ptr), &field_len, &content_len);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    uint16_t data_len = (uint16_t)(field_len + content_len);
    if (data_len > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += data_len;
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**
 * UTF-8字符串
 */
int16_t dlt_698_parse_octet_utf8_string(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    // 返回携带的数据长度值，并前移一个字节
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_UTF8_STRING;
    uint16_t field_len = 0;
    uint16_t content_len = 0;
    int16_t ret = dlt_698_parse_axdr_len(ins_ptr->_payld_ptr + ins_ptr->_payld_index, dlt_698_payld_remain(ins_ptr), &field_len, &content_len);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    uint16_t data_len = (uint16_t)(field_len + content_len);
    if (data_len > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += data_len;
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**8位整数 */
int16_t dlt_698_parse_integer(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_INTEGER;
    if (sizeof(oop_integer) > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += sizeof(oop_integer);
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**解析long数据结构 */
int16_t dlt_698_parse_long(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_LONG;
    if (sizeof(oop_long) > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += sizeof(oop_long);
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**8位正整数 */
int16_t dlt_698_parse_unsigned(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_UNSIGNED;
    if (sizeof(oop_unsigned) > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += sizeof(oop_unsigned);
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**
 * long_unsigned
 */
int16_t dlt_698_parse_long_unsigned(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_LONG_UNSIGNED;
    if (sizeof(oop_long_unsigned) > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += sizeof(oop_long_unsigned);
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**解析long64数据结构 */
int16_t dlt_698_parse_long64(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_LONG64;
    if (sizeof(oop_long64) > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += sizeof(oop_long64);
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**解析long64-unsigned数据结构 */
int16_t dlt_698_parse_long64_unsigned(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_LONG64_UNSIGNED;
    if (sizeof(oop_long64_unsigned) > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += sizeof(oop_long64_unsigned);
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**
 * 枚举的元素在对象属性或方法的描述中定义
 */
int16_t dlt_698_parse_enum(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_ENUM;
    if (sizeof(oop_enum) > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += sizeof(oop_enum);
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**解析float32数据结构 */
int16_t dlt_698_parse_float32(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_FLOAT32;
    if (sizeof(oop_float32) > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += sizeof(oop_float32);
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**解析float64数据结构 */
int16_t dlt_698_parse_float64(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_FLOAT64;
    if (sizeof(oop_float64) > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += sizeof(oop_float64);
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}

/**
 * date_time∷=SEQUENCE
 *{
 *  year          long-unsigned，
 *  month         unsigned，
 *  day_of_month  unsigned，
 *  day_of_week   unsigned，
 *  hour          unsigned，
 *  minute        unsigned，
 *  second        unsigned，
 *  milliseconds  long-unsigned
 *}
 *
 */
int16_t dlt_698_parse_date_time(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    // date_time占10个字节
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_DATE_TIME;
    if (sizeof(oop_date_time) > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += sizeof(oop_date_time);
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**
 * date∷=SEQUENCE
 *{
 *  year          long-unsigned，
 *  month         unsigned，
 *  day_of_month  unsigned，
 *  day_of_week   unsigned
 *}
 */
int16_t dlt_698_parse_date(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    // time占5个字节
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_DATE;
    if (sizeof(oop_date) > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += sizeof(oop_date);
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**
 * time∷=SEQUENCE
 *{
 *  hour          unsigned，
 *  minute        unsigned，
 *  second        unsigned
 *}
 */
int16_t dlt_698_parse_time(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    // time占3个字节
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_TIME;
    if (sizeof(oop_time) > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += sizeof(oop_time);
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**
 * date_time_s∷=SEQUENCE
 * {
 *   year          long-unsigned，
 *   month         unsigned，
 *   day           unsigned，
 *   hour          unsigned，
 *   minute        unsigned，
 *   second        unsigned
 * }
 */
int16_t dlt_698_parse_date_time_s(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    // date_time_s占7个字节
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_DATE_TIME_S;
    if (sizeof(oop_date_time_s) > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += sizeof(oop_date_time_s);
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**
 * OI∷=long-unsigned
 */
int16_t dlt_698_parse_oi(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_OI;
    if (sizeof(oop_oi) > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += sizeof(oop_oi);
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**
 * OAD∷=SEQUENCE
 * {
 * 对象标识          OI，
 * 属性标识及其特征   unsigned，
 * 属性内元素索引     unsigned（1…255）
 * }
 */
int16_t dlt_698_parse_oad(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_OAD;
    if (sizeof(oop_oad) > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += sizeof(oop_oad);
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**
 * ROAD∷=SEQUENCE
 * {
 * 对象属性描述符      OAD，
 * 关联对象属性描述符  SEQUENCE OF OAD
 * }
 */
int16_t dlt_698_parse_road(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_ROAD;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    dlt_698_data_t *oad_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (oad_ptr== NULL)
    {
        return DLT_698_ERR_MEM;
    }
    uint16_t child_index = ins_ptr->_mem.alloc_mempool_size - sizeof(dlt_698_data_t);
    dlt_698_append_childNode(ins_ptr, data_ptr, child_index);
    int16_t ret = dlt_698_parse_oad(ins_ptr, oad_ptr);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    if (dlt_698_payld_remain(ins_ptr) < 1)
    {
        return DLT_698_ERR_OVER;
    }
    uint8_t oad_cnt = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    for (int i = 0; i < oad_cnt; i++)
    {
        uint16_t child_index = ins_ptr->_mem.alloc_mempool_size;
        dlt_698_data_t *node_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
        if (node_ptr == NULL)
        {
            return DLT_698_ERR_MEM;
        }
        dlt_698_append_childNode(ins_ptr, data_ptr, child_index);
        ret = dlt_698_parse_oad(ins_ptr, node_ptr);
        if (ret != DLT_698_ERR_NONE)
        {
            return ret;
        }
    }
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    return DLT_698_ERR_NONE;
}
/**
 * OMD∷=SEQUENCE
 * {
 * 对象标识  OI，
 * 方法标识  unsigned（1…255），
 * 操作模式  unsigned（0）
 * }
 *
 */
int16_t dlt_698_parse_omd(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    // OI
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_OMD;
    if (sizeof(oop_omd) > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += sizeof(oop_omd);
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**
 * TI∷=SEQUENCE
 * {
 * 单位  ENUMERATED
 * {
 * 秒      （0），
 * 分      （1），
 * 时      （2），
 * 日      （3），
 * 月      （4），
 * 年      （5）
 * }，
 * 间隔值  long-unsigned
 * }
 */
int16_t dlt_698_parse_ti(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    // TI数据结构相对简单，不在分开处理[单位，间隔值]
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_TI;
    if (sizeof(oop_ti) > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += sizeof(oop_ti);
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**
 * TSA∷=octet-string(SIZE(2…17))
 */
int16_t dlt_698_parse_tsa(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_TSA;
    if (dlt_698_payld_remain(ins_ptr) < 1)
    {
        return DLT_698_ERR_OVER;
    }
    uint8_t tsa_len = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    if (dlt_698_payld_remain(ins_ptr) < tsa_len)
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += tsa_len;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    return DLT_698_ERR_NONE;
}
/**
 * MAC∷=octet-string
 */
int16_t dlt_698_parse_mac(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_MAC;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    if (dlt_698_payld_remain(ins_ptr) < 1)
    {
        return DLT_698_ERR_OVER;
    }
    uint8_t len = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    if (dlt_698_payld_remain(ins_ptr) < len)
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += len;
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    return DLT_698_ERR_NONE;
}
/**
 * RN∷=octet-string
 */
int16_t dlt_698_parse_rn(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    // RN数据结构相对简单，不在分开处理
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_RN;
    if (dlt_698_payld_remain(ins_ptr) < 1)
    {
        return DLT_698_ERR_OVER;
    }
    uint8_t data_len = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    if (dlt_698_payld_remain(ins_ptr) < data_len)
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += data_len;
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**
 * Region∷=SEQUENCE
 * {
 * 单位  ENUMERATED
 * {
 * 前闭后开    （0），
 * 前开后闭    （1），
 * 前闭后闭    （2），
 * 前开后开    （3）
 * }，
 * 起始值  Data，
 * 结束值  Data
 * }
 *
 */
int16_t dlt_698_parse_region(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_REGION;

    // 单位  ENUMERATED
    uint16_t child_index = ins_ptr->_mem.alloc_mempool_size;
    dlt_698_data_t *node1_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (node1_ptr == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, data_ptr, child_index);
    int16_t ret = dlt_698_parse_enum(ins_ptr, node1_ptr);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }

    // 起始值  Data
    child_index = ins_ptr->_mem.alloc_mempool_size;
    dlt_698_data_t *node2_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (node2_ptr == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, data_ptr, child_index);
    if (dlt_698_payld_remain(ins_ptr) < 1)
    {
        return DLT_698_ERR_OVER;
    }
    uint8_t data_type = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    ret = dlt_698_parse_data(ins_ptr, data_type, node2_ptr);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }

    // 结束值  Data
    child_index = ins_ptr->_mem.alloc_mempool_size;
    dlt_698_data_t *node3_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (node3_ptr == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, data_ptr, child_index);
    if (dlt_698_payld_remain(ins_ptr) < 1)
    {
        return DLT_698_ERR_OVER;
    }
    uint8_t data_type2 = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    ret = dlt_698_parse_data(ins_ptr, data_type2, node3_ptr);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    return DLT_698_ERR_NONE;
}
/**
 * Scaler_Unit∷=SEQUENCE
 * {
 * 换算  integer，
 * 单位  ENUMERATED
 * }
 */
int16_t dlt_698_parse_scaler_unit(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_SCALER_UNIT;
    if (sizeof(oop_scaler_unit) > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += sizeof(oop_scaler_unit);
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**解析RSD数据结构 */
int16_t dlt_698_parse_rsd(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_RSD;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    if (dlt_698_payld_remain(ins_ptr) < 1)
    {
        return DLT_698_ERR_OVER;
    }
    uint8_t selector = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    int16_t res = DLT_698_ERR_NONE;
    switch (selector)
    {
        case 0:
        {
            res = dlt_698_parse_rsd_sel0(ins_ptr, data_ptr);
        }
        break;
        case 1:
        {
            res = dlt_698_parse_rsd_sel1(ins_ptr, data_ptr);
        }
        break;
        case 2:
        {
            res = dlt_698_parse_rsd_sel2(ins_ptr, data_ptr);
        }
        break;
        case 3:
        {
            res = dlt_698_parse_rsd_sel3(ins_ptr, data_ptr);
        }
        break;
        case 4:
        {
            res = dlt_698_parse_rsd_sel4(ins_ptr, data_ptr);
        }
        break;
        case 5:
        {
            res = dlt_698_parse_rsd_sel5(ins_ptr, data_ptr);
        }
        break;
        case 6:
        {
            res = dlt_698_parse_rsd_sel6(ins_ptr, data_ptr);
        }
        break;
        case 7:
        {
            res = dlt_698_parse_rsd_sel7(ins_ptr, data_ptr);
        }
        break;
        case 8:
        {
            res = dlt_698_parse_rsd_sel8(ins_ptr, data_ptr);
        }
        break;
        case 9:
        {
            res = dlt_698_parse_rsd_sel9(ins_ptr, data_ptr);
        }
        break;
        case 10:
        {
            res = dlt_698_parse_rsd_sel10(ins_ptr, data_ptr);
        }
        break;
        default:
            res = DLT_698_ERR_PARSE;
            break;
    }


    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;

    return res;
}
/**
 * CSD∷=CHOICE
 * {
 * 对象属性描述符      [0] OAD，
 * 记录型对象属性描述符 [1] ROAD
 * }
 */
int16_t dlt_698_parse_csd(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_CSD;
    if (dlt_698_payld_remain(ins_ptr) < 1)
    {
        return DLT_698_ERR_OVER;
    }
    uint8_t csd_type = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    int16_t ret = DLT_698_ERR_NONE;
    uint16_t child_index = ins_ptr->_mem.alloc_mempool_size;
    dlt_698_data_t *node_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (node_ptr == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, data_ptr, child_index);
    switch (csd_type)
    {
        case 0:
            ret = dlt_698_parse_oad(ins_ptr, node_ptr);
            break;
        case 1:
            ret = dlt_698_parse_road(ins_ptr, node_ptr);
            break;
        default:
            break;
    }
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }

    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    return DLT_698_ERR_NONE;
}
/**
 * MS∷=CHOICE
 * {
 *  无表计                [0]，
 *  全部用户地址          [1]，
 *  一组用户类型          [2] SEQUENCE OF unsigned，
 *  一组用户地址          [3] SEQUENCE OF TSA，
 *  一组配置序号          [4] SEQUENCE OF long-unsigned，
 *  一组用户类型区间    [5] SEQUENCE OF Region，
 *  一组用户地址区间    [6] SEQUENCE OF Region，
 *  一组配置序号区间    [7] SEQUENCE OF Region
 * }
 */
int16_t dlt_698_parse_ms(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    // MS 数据项内容
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_MS;
    if (dlt_698_payld_remain(ins_ptr) < 1)
    {
        return DLT_698_ERR_OVER;
    }
    uint8_t ms_item_type = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    int16_t ret = DLT_698_ERR_NONE;
    switch (ms_item_type)
    {
        case 0:    // 无表计[0]，
            break;
        case 1:    // 全部用户地址      [1]，
            break;
        case 2:    // SEQUENCE OF unsigned
        {
            if (dlt_698_payld_remain(ins_ptr) < 1)
            {
                return DLT_698_ERR_OVER;
            }
            uint8_t u8_cnt = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
            for (int i = 0; i < u8_cnt; i++)
            {
                uint16_t child_index = ins_ptr->_mem.alloc_mempool_size;
                dlt_698_data_t *node1_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
                if (node1_ptr == NULL)
                {
                    return DLT_698_ERR_MEM;
                }
                dlt_698_append_childNode(ins_ptr, data_ptr, child_index);
                ret = dlt_698_parse_unsigned(ins_ptr, node1_ptr);
                if (ret != DLT_698_ERR_NONE)
                {
                    return ret;
                }
            }
        }
        break;
        case 3:    // SEQUENCE OF TSA；TSA序列，需要包括一个长度
        {
            if (dlt_698_payld_remain(ins_ptr) < 1)
            {
                return DLT_698_ERR_OVER;
            }
            uint8_t tas_cnt = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
            for (int i = 0; i < tas_cnt; i++)
            {
                uint16_t child_index = ins_ptr->_mem.alloc_mempool_size;
                dlt_698_data_t *node1_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
                if (node1_ptr == NULL)
                {
                    return DLT_698_ERR_MEM;
                }
                dlt_698_append_childNode(ins_ptr, data_ptr, child_index);
                ret = dlt_698_parse_tsa(ins_ptr, node1_ptr);
                if (ret != DLT_698_ERR_NONE)
                {
                    return ret;
                }
            }
        }
        break;
        case 4:    // SEQUENCE OF long-unsigned
        {
            if (dlt_698_payld_remain(ins_ptr) < 1)
            {
                return DLT_698_ERR_OVER;
            }
            uint8_t u16_cnt = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
            for (int i = 0; i < u16_cnt; i++)
            {
                uint16_t child_index = ins_ptr->_mem.alloc_mempool_size;
                dlt_698_data_t *node1_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
                if (node1_ptr == NULL)
                {
                    return DLT_698_ERR_MEM;
                }
                dlt_698_append_childNode(ins_ptr, data_ptr, child_index);
                ret = dlt_698_parse_long_unsigned(ins_ptr, node1_ptr);
                if (ret != DLT_698_ERR_NONE)
                {
                    return ret;
                }
            }
        }
        break;
        case 5:    // SEQUENCE OF Region,
        case 6:    // SEQUENCE OF Region,
        case 7:    // SEQUENCE OF Region,
        {
            if (dlt_698_payld_remain(ins_ptr) < 1)
            {
                return DLT_698_ERR_OVER;
            }
            uint8_t region_cnt = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
            for (int i = 0; i < region_cnt; i++)
            {
                uint16_t child_index = ins_ptr->_mem.alloc_mempool_size;
                dlt_698_data_t *node1_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
                if (node1_ptr == NULL)
                {
                    return DLT_698_ERR_MEM;
                }
                dlt_698_append_childNode(ins_ptr, data_ptr, child_index);
                ret = dlt_698_parse_region(ins_ptr, node1_ptr);
                if (ret != DLT_698_ERR_NONE)
                {
                    return ret;
                }
            }
        }
        break;
        default:
            break;
    }
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    return DLT_698_ERR_NONE;
}
/**
 * SID∷=SEQUENCE
 * {
 * 标识       double-long-unsigned，
 * 附加数据   octet-string
 * }
 */
int16_t dlt_698_parse_sid(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    /*SID 标识(4)+LEN(1)+附加数据(N)*/
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_SID;
    int16_t ret = DLT_698_ERR_NONE;
    uint16_t child_index = ins_ptr->_mem.alloc_mempool_size;
    dlt_698_data_t *node1_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (!node1_ptr)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, data_ptr, child_index);
    ret = dlt_698_parse_double_long_unsigned(ins_ptr, node1_ptr);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }

    child_index = ins_ptr->_mem.alloc_mempool_size;
    dlt_698_data_t *node2_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (!node2_ptr)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, data_ptr, child_index);
    ret = dlt_698_parse_octet_string(ins_ptr, node2_ptr);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }

    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    return DLT_698_ERR_NONE;
}
/**
 * SID_MAC∷=SEQUENCE
 * {
 * 安全标识      SID，
 * 消息鉴别码    MAC
 * }
 */
int16_t dlt_698_parse_sid_mac(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    /*SID 标识(4)+LEN(1)+MAC*/
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_SID_MAC;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    int16_t ret = DLT_698_ERR_NONE;
    uint16_t child_index = ins_ptr->_mem.alloc_mempool_size;
    dlt_698_data_t *node1_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (!node1_ptr)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, data_ptr, child_index);
    ret = dlt_698_parse_sid(ins_ptr, node1_ptr);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }

    child_index = ins_ptr->_mem.alloc_mempool_size;
    dlt_698_data_t *node2_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (!node2_ptr)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, data_ptr, child_index);
    ret = dlt_698_parse_mac(ins_ptr, node2_ptr);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    return DLT_698_ERR_NONE;
}
/**
 * COMDCB∷=SEQUENCE
 * {
 * 波特率  ENUMERATED
 * {
 * 300bps（0），   600bps（1），     1200bps（2），
 * 2400bps（3），  4800bps（4），    7200bps（5），
 * 9600bps（6），  19200bps（7），   38400bps（8），
 * 57600bps（9）， 115200bps（10）， 自适应（255）
 * }，
 * 校验位  ENUMERATED {无校验（0），奇校验（1），偶校验（2）}，
 * 数据位  ENUMERATED {5（5），6（6），7（7），8（8）}，
 * 停止位  ENUMERATED {1（1），2（2）}，
 * 流控    ENUMERATED {无(0)，硬件(1)，软件(2)}
 * }
 */
int16_t dlt_698_parse_comdcb(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_COMDCB;
    if (sizeof(oop_comdcb) > dlt_698_payld_remain(ins_ptr))
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index += sizeof(oop_comdcb);
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
/**
 * RCSD∷=SEQUENCE OF CSD
 */
int16_t dlt_698_parse_rcsd(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = DLT_698_TYPE_OOP_RCSD;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    if (dlt_698_payld_remain(ins_ptr) < 1)
    {
        return DLT_698_ERR_OVER;
    }
    uint8_t csd_cnt = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    int16_t ret = DLT_698_ERR_NONE;
    for (int i = 0; i < csd_cnt; i++)
    {
        uint16_t child_index = ins_ptr->_mem.alloc_mempool_size;
        dlt_698_data_t *node1_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
        if (node1_ptr == NULL)
        {
            return DLT_698_ERR_MEM;
        }
        dlt_698_append_childNode(ins_ptr, data_ptr, child_index);
        ret = dlt_698_parse_csd(ins_ptr, node1_ptr);
        if (ret != DLT_698_ERR_NONE)
        {
            return ret;
        }
    }

    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    return DLT_698_ERR_NONE;
}

int16_t dlt_698_parse_axdr_len(const uint8_t *pData, uint16_t remain, uint16_t *pFieldLen, uint16_t *pContentLen)
{
    uint16_t pos = 0;
    *pFieldLen = 0;
    *pContentLen = 0;
    if (pData == NULL || remain < 1)
    {
        return DLT_698_ERR_OVER;
    }
    uint8_t first_byte = pData[pos++];
    /*0x80 是 A-XDR 的不定长标记，DL/T 698 不使用。此前被当成"长度域1字节、内容0字节"悄悄接受，
     * 会让后续域整体错位(如 TimeTag 读到别处)，这里按非法长度编码拒绝*/
    if (first_byte == 0x80)
    {
        return DLT_698_ERR_PARSE;
    }
    if (first_byte & 0x80)    // 长度不固定  有长度域
    {
        // 长度域字节个数，协议规定最多0x82即2字节，超出按非法处理
        uint16_t len_bytes = (uint16_t)(first_byte & 0x7F);
        if (len_bytes > 2)
        {
            return DLT_698_ERR_PARSE;
        }
        if ((uint16_t)(len_bytes + 1) > remain)    // 长度域本身超出载荷
        {
            return DLT_698_ERR_OVER;
        }
        for (uint16_t i = 0; i < len_bytes; i++)
        {
            *pContentLen = (uint16_t)((*pContentLen << 8) | pData[pos++]);
        }
        *pFieldLen = (uint16_t)(len_bytes + 1);
    }
    else    // 长度固定  第一个字节就是长度
    {
        *pContentLen = first_byte;
        *pFieldLen = 1;
    }
    return DLT_698_ERR_NONE;
}
/**
 * DAR∷=ENUMERATED
 * {
 * 成功                 （0），
 * 硬件失效             （1），
 * 暂时失效             （2），
 * 拒绝读写             （3），
 * 对象未定义           （4），
 * 对象接口类不符合     （5），
 * 对象不存在           （6），
 * 类型不匹配           （7），
 * 越界                 （8），
 * 数据块不可用         （9），
 * 分帧传输已取消       （10），
 * 不处于分帧传输状态   （11），
 * 块写取消             （12），
 * 不存在块写状态       （13），
 * 数据块序号无效       （14），
 * 密码错/未授权        （15），
 * 通信速率不能更改     （16），
 * 年时区数超           （17），
 * 日时段数超           （18），
 * 费率数超             （19），
 * 安全认证不匹配       （20），
 * 重复充值             （21），
 * ESAM验证失败        （22），
 * 安全认证失败         （23），
 * 客户编号不匹配       （24），
 * 充值次数错误         （25），
 * 购电超囤积           （26），
 * 地址异常             （27），
 * 对称解密错误         （28），
 * 非对称解密错误       （29），
 * 签名错误             （30），
 * 电能表挂起           （31），
 * 时间标签无效          (32)，
 * 请求超时             （33），
 * ESAM的P1P2不正确    （34），
 * ESAM的LC错误        （35），
 * 其它                 （255）
 * }
 */
int16_t dlt_698_parse_dr(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *data_ptr)
{
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = 0;
    if (dlt_698_payld_remain(ins_ptr) < 1)
    {
        return DLT_698_ERR_OVER;
    }
    ins_ptr->_payld_index++;
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    return DLT_698_ERR_NONE;
}
int16_t dlt_698_parse_TimeTag(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t **tag_ptr)
{

    if (dlt_698_payld_remain(ins_ptr) < 1)
    {
        return DLT_698_ERR_OVER;
    }
    uint8_t timeTagOptional = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    if (timeTagOptional == 0)    // 无时间标签
    {
        return DLT_698_ERR_NONE;
    }

    int16_t ret = DLT_698_ERR_NONE;
    dlt_698_data_t *data_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (data_ptr== NULL)
    {
        return DLT_698_ERR_MEM;
    }
    *tag_ptr = data_ptr;
    data_ptr->index = ins_ptr->_payld_index;
    data_ptr->type = 2;
    data_ptr->child_index = 0;
    data_ptr->next_index = 0;
    uint16_t child_index = ins_ptr->_mem.alloc_mempool_size;
    dlt_698_data_t *dts = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (dts == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, data_ptr, child_index);
    ret = dlt_698_parse_date_time_s(ins_ptr, dts);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }

    child_index = ins_ptr->_mem.alloc_mempool_size;
    dlt_698_data_t *ti = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (ti == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, data_ptr, child_index);
    ret = dlt_698_parse_ti(ins_ptr, ti);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    data_ptr->len = ins_ptr->_payld_index - data_ptr->index;
    return DLT_698_ERR_NONE;
}
int16_t dlt_698_parse_FollowReportTag(struct DLT_698_PRIVATE *ins_ptr, dlt_698_follow_report_t **follow_ptr)
{
    if (dlt_698_payld_remain(ins_ptr) < 1)
    {
        return DLT_698_ERR_OVER;
    }
    uint8_t timeTagOptional = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    if (timeTagOptional == 0)    // 无跟随上报域
    {
        return DLT_698_ERR_NONE;
    }
    dlt_698_follow_report_t *data_ptr = (dlt_698_follow_report_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_follow_report_t));
    if (data_ptr==NULL)
    {
        return DLT_698_ERR_MEM;
    }
    *follow_ptr = data_ptr;
    if (dlt_698_payld_remain(ins_ptr) < 1)
    {
        return DLT_698_ERR_OVER;
    }
    data_ptr->follow_type = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    if (dlt_698_payld_remain(ins_ptr) < 1)
    {
        return DLT_698_ERR_OVER;
    }
    int cnt = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    data_ptr->data.normal_ptr = NULL;
    if (data_ptr->follow_type == 1)
    {
        data_ptr->data.normal_ptr = NULL;
        struct DLT_698_Result_Normal **node_father = &data_ptr->data.normal_ptr;
        // 循环解析每一个数据块信息
        for (int i = 0; i < cnt; i++)
        {
            uint16_t next_index = ins_ptr->_mem.alloc_mempool_size;
            struct DLT_698_Result_Normal *node_ptr = (struct DLT_698_Result_Normal *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_Result_Normal));
            if (node_ptr==NULL)
            {
                return DLT_698_ERR_MEM;
            }
            DLT_698_append_next(struct DLT_698_Result_Normal, ins_ptr->_mem.start, node_father, next_index);
            int16_t ret = dlt_698_parse_result_normal(ins_ptr, node_ptr);

            if (ret != DLT_698_ERR_NONE)
            {
                return ret;
            }
        }
    }
    else if (data_ptr->follow_type == 2)
    {
        data_ptr->data.result_ptr = NULL;
        struct DLT_698_RESULT_RECORD **node_father = &data_ptr->data.result_ptr;
        // 循环解析每一个数据块信息
        for (int i = 0; i < cnt; i++)
        {
            uint16_t next_index = ins_ptr->_mem.alloc_mempool_size;
            struct DLT_698_RESULT_RECORD *node_ptr = (struct DLT_698_RESULT_RECORD *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_RESULT_RECORD));
            if (node_ptr==NULL)
            {
                return DLT_698_ERR_MEM;
            }
            DLT_698_append_next(struct DLT_698_RESULT_RECORD, ins_ptr->_mem.start, node_father, next_index);
            int16_t ret = dlt_698_parse_get_res_record_result(ins_ptr, node_ptr);
            if (ret != DLT_698_ERR_NONE)
            {
                return ret;
            }
        }
    }
    return DLT_698_ERR_NONE;
}
int16_t dlt_698_parse_result_normal(struct DLT_698_PRIVATE *ins_ptr, struct DLT_698_Result_Normal *result_normal)
{
    int16_t ret = dlt_698_parse_oad(ins_ptr, &result_normal->oad);
    if (ret == DLT_698_ERR_NONE)
    {
        ret = dlt_698_parse_get_result(ins_ptr, &result_normal->get_result);
    }
    result_normal->next_index = 0;
    return ret;
}
int16_t dlt_698_parse_get_result(struct DLT_698_PRIVATE *ins_ptr, struct DLT_698_Get_Result *get_result)
{
    if (dlt_698_payld_remain(ins_ptr) < 1)
    {
        return DLT_698_ERR_OVER;
    }
    uint8_t result = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    uint8_t data_type = 0;
    if (result == 0)
    {
        if (dlt_698_payld_remain(ins_ptr) < 1)
        {
            return DLT_698_ERR_OVER;
        }
        get_result->dar = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    }
    else
    {
        if (dlt_698_payld_remain(ins_ptr) < 1)
        {
            return DLT_698_ERR_OVER;
        }
        data_type = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    }
    return dlt_698_parse_data(ins_ptr, data_type, &get_result->result_data);
}

int16_t dlt_698_parse_get_res_record_result(struct DLT_698_PRIVATE *ins_ptr, struct DLT_698_RESULT_RECORD *data_ptr)
{
    data_ptr->next_index = 0;
    // 解析OAD
    int16_t ret = dlt_698_parse_oad(ins_ptr, &data_ptr->oad);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }

    // 解析RCSD
    int csd_cnt = ins_ptr->_payld_ptr[ins_ptr->_payld_index];
    ret = dlt_698_parse_rcsd(ins_ptr, &data_ptr->rcsd);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    /*解析响应数据*/
    // 数据有效性检查
    if (dlt_698_payld_remain(ins_ptr) < 1)
    {
        return DLT_698_ERR_OVER;
    }
    uint8_t choice = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    data_ptr->record.row_ptr = NULL;
    if (0 == choice)
    {
        if (dlt_698_payld_remain(ins_ptr) < 1)
        {
            return DLT_698_ERR_OVER;
        }
        data_ptr->record.dar = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    }
    else
    {
        // 记录行数
        if (dlt_698_payld_remain(ins_ptr) < 1)
        {
            return DLT_698_ERR_OVER;
        }
        uint8_t row_cnt = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
        data_ptr->record.row_ptr = NULL;
        struct DLT_698_GET_RECORD_ROW **row_father = &data_ptr->record.row_ptr;
        // 数据起始位置
        for (int i = 0; i < row_cnt; i++)
        {
            uint16_t row_index = ins_ptr->_mem.alloc_mempool_size;
            struct DLT_698_GET_RECORD_ROW *rec_row_ptr = (struct DLT_698_GET_RECORD_ROW *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_GET_RECORD_ROW));
            if (rec_row_ptr == NULL)
            {
                return DLT_698_ERR_MEM;
            }
            DLT_698_append_next(struct DLT_698_GET_RECORD_ROW, ins_ptr->_mem.start, row_father, row_index);

            rec_row_ptr->data = NULL;
            dlt_698_data_t **node_father = &rec_row_ptr->data;
            for (int j = 0; j < csd_cnt; j++)
            {
                uint16_t next_index = ins_ptr->_mem.alloc_mempool_size;
                dlt_698_data_t *unit_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
                if (unit_ptr == NULL)
                {
                    return DLT_698_ERR_MEM;
                }
                // 获取数据类型
                if (dlt_698_payld_remain(ins_ptr) < 1)
                {
                    return DLT_698_ERR_OVER;
                }
                uint8_t data_type = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
                DLT_698_append_next(dlt_698_data_t, ins_ptr->_mem.start, node_father, next_index);
                // 解析数据占用长度
                int16_t ret = dlt_698_parse_data(ins_ptr, data_type, unit_ptr);
                if (ret != DLT_698_ERR_NONE)
                {
                    return ret;
                }
            }
        }
    }
    return DLT_698_ERR_NONE;
}
int16_t dlt_698_parse_rsd_sel0(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *rsd_ptr)
{
    uint16_t child_index = ins_ptr->_mem.alloc_mempool_size;
    // NULL
    dlt_698_data_t *data_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (data_ptr == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, rsd_ptr, child_index);
    return dlt_698_parse_null(ins_ptr, data_ptr);
}
int16_t dlt_698_parse_rsd_sel1(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *rsd_ptr)
{
    uint16_t child_index = ins_ptr->_mem.alloc_mempool_size;
    // OAD
    dlt_698_data_t *oad_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (oad_ptr == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, rsd_ptr, child_index);
    int16_t res = dlt_698_parse_oad(ins_ptr, oad_ptr);
    if (res != DLT_698_ERR_NONE)
    {
        return res;
    }
    // Data
    child_index = ins_ptr->_mem.alloc_mempool_size;
    dlt_698_data_t *data_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (data_ptr == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, rsd_ptr, child_index);
    if (dlt_698_payld_remain(ins_ptr) < 1)
    {
        return DLT_698_ERR_OVER;
    }
    uint8_t data_type = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    res = dlt_698_parse_data(ins_ptr, data_type, data_ptr);
    return res;
}

int16_t dlt_698_parse_rsd_sel2(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *rsd_ptr)
{
    uint16_t child_index = ins_ptr->_mem.alloc_mempool_size;
    // OAD
    dlt_698_data_t *oad_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (oad_ptr == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, rsd_ptr, child_index);
    int16_t res = dlt_698_parse_oad(ins_ptr, oad_ptr);
    if (res != DLT_698_ERR_NONE)
    {
        return res;
    }
    // 起始值 Data 结束值data 数据间隔data
    for (int i = 0; i < 3; i++)
    {
        child_index = ins_ptr->_mem.alloc_mempool_size;
        dlt_698_data_t *data_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
        if (data_ptr == NULL)
        {
            res = DLT_698_ERR_MEM;
            break;
        }
        dlt_698_append_childNode(ins_ptr, rsd_ptr, child_index);

        if (dlt_698_payld_remain(ins_ptr) < 1)
        {
            return DLT_698_ERR_OVER;
        }
        uint8_t data_type = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
        res = dlt_698_parse_data(ins_ptr, data_type, data_ptr);
        if (res != DLT_698_ERR_NONE)
        {
            break;
        }
    }
    return res;
}
int16_t dlt_698_parse_rsd_sel3(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *rsd_ptr)
{
    if (dlt_698_payld_remain(ins_ptr) < 1)
    {
        return DLT_698_ERR_OVER;
    }
    uint8_t cnt = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    int16_t res = DLT_698_ERR_NONE;
    for (int i = 0; i < cnt; i++)
    {
        uint16_t child_index = ins_ptr->_mem.alloc_mempool_size;
        // OAD
        dlt_698_data_t *sel2_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
        if (sel2_ptr == NULL)
        {
            res = DLT_698_ERR_MEM;
            break;
        }
        sel2_ptr->index = ins_ptr->_payld_index;
        sel2_ptr->type = 0;
        sel2_ptr->child_index = 0;
        sel2_ptr->next_index = 0;

        dlt_698_append_childNode(ins_ptr, rsd_ptr, child_index);
        sel2_ptr->index = ins_ptr->_payld_index;
        sel2_ptr->type = 2;
        res = dlt_698_parse_rsd_sel2(ins_ptr, sel2_ptr);
        if (res != DLT_698_ERR_NONE)
        {
            return res;
        }
        sel2_ptr->len = ins_ptr->_payld_index - sel2_ptr->index;
    }

    return res;
}
int16_t dlt_698_parse_rsd_sel4(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *rsd_ptr)
{
    uint16_t child_index = ins_ptr->_mem.alloc_mempool_size;
    // 采集启动时间 date_time_s
    dlt_698_data_t *dts_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (dts_ptr == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, rsd_ptr, child_index);
    int16_t res = dlt_698_parse_date_time_s(ins_ptr, dts_ptr);
    if (res != DLT_698_ERR_NONE)
    {
        return res;
    }
    // MS
    child_index = ins_ptr->_mem.alloc_mempool_size;
    dlt_698_data_t *ms_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (ms_ptr == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, rsd_ptr, child_index);
    res = dlt_698_parse_ms(ins_ptr, ms_ptr);

    return res;
}
int16_t dlt_698_parse_rsd_sel5(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *rsd_ptr)
{
    return dlt_698_parse_rsd_sel4(ins_ptr, rsd_ptr);
}
int16_t dlt_698_parse_rsd_sel6(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *rsd_ptr)
{
    // 采集启动时间起始值 date_time_s
    uint16_t child_index = ins_ptr->_mem.alloc_mempool_size;
    dlt_698_data_t *dts_start_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (dts_start_ptr == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, rsd_ptr, child_index);
    int16_t res = dlt_698_parse_date_time_s(ins_ptr, dts_start_ptr);
    if (res != DLT_698_ERR_NONE)
    {
        return res;
    }
    // 采集启动时间结束值 date_time_s
    child_index = ins_ptr->_mem.alloc_mempool_size;
    dlt_698_data_t *dts_end_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (dts_end_ptr == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, rsd_ptr, child_index);
    res = dlt_698_parse_date_time_s(ins_ptr, dts_end_ptr);
    if (res != DLT_698_ERR_NONE)
    {
        return res;
    }
    // 时间间隔TI
    child_index = ins_ptr->_mem.alloc_mempool_size;
    dlt_698_data_t *ti_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (ti_ptr == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, rsd_ptr, child_index);
    res = dlt_698_parse_ti(ins_ptr, ti_ptr);
    if (res != DLT_698_ERR_NONE)
    {
        return res;
    }
    // 表计集合 MS
    child_index = ins_ptr->_mem.alloc_mempool_size;
    dlt_698_data_t *ms_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (ms_ptr == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, rsd_ptr, child_index);
    res = dlt_698_parse_ms(ins_ptr, ms_ptr);

    return res;
}
int16_t dlt_698_parse_rsd_sel7(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *rsd_ptr)
{
    return dlt_698_parse_rsd_sel6(ins_ptr, rsd_ptr);
}
int16_t dlt_698_parse_rsd_sel8(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *rsd_ptr)
{
    return dlt_698_parse_rsd_sel6(ins_ptr, rsd_ptr);
}
int16_t dlt_698_parse_rsd_sel9(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *rsd_ptr)
{
    uint16_t child_index = ins_ptr->_mem.alloc_mempool_size;
    // 上n条记录 unsigned
    dlt_698_data_t *unsigned_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (unsigned_ptr == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, rsd_ptr, child_index);
    int16_t res = dlt_698_parse_unsigned(ins_ptr, unsigned_ptr);
    return res;
}
int16_t dlt_698_parse_rsd_sel10(struct DLT_698_PRIVATE *ins_ptr, dlt_698_data_t *rsd_ptr)
{
    uint16_t child_index = ins_ptr->_mem.alloc_mempool_size;
    // 上n条记录 unsigned
    dlt_698_data_t *unsigned_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (unsigned_ptr == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, rsd_ptr, child_index);
    int16_t res = dlt_698_parse_unsigned(ins_ptr, unsigned_ptr);
    if (res != DLT_698_ERR_NONE)
    {
        return res;
    }
    // 表计集合 MS
    child_index = ins_ptr->_mem.alloc_mempool_size;
    dlt_698_data_t *ms_ptr = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
    if (ms_ptr == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    dlt_698_append_childNode(ins_ptr, rsd_ptr, child_index);
    res = dlt_698_parse_ms(ins_ptr, ms_ptr);
    return res;
}