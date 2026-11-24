#include "dlt_698_parser_private.h"
#include "dlt_698_parser_widget.h"
typedef int16_t (*dlt_698_sec_fun)(struct DLT_698_PRIVATE *ins_ptr);

static int16_t dlt_698_parse_sec_RN_MAC(struct DLT_698_PRIVATE *ins_ptr)
{

    int16_t ret = dlt_698_parse_rn(ins_ptr, &ins_ptr->frame.req_sec->verify.RN_MAC.RN);
    if (DLT_698_ERR_NONE == ret)
    {
        ret = dlt_698_parse_mac(ins_ptr, &ins_ptr->frame.req_sec->verify.RN_MAC.MAC);
    }
    return ret;
}
/*解析安全数据项，SID*/
static int16_t dlt_698_parse_sec_SID(struct DLT_698_PRIVATE *ins_ptr)
{
    return dlt_698_parse_sid(ins_ptr, &ins_ptr->frame.req_sec->verify.SID);
}
/*解析安全数据项，RN*/
static int16_t dlt_698_parse_sec_RN(struct DLT_698_PRIVATE *ins_ptr)
{
    return dlt_698_parse_rn(ins_ptr, &ins_ptr->frame.req_sec->verify.RN);
}
/*解析安全数据项，SID_MAC*/
static int16_t dlt_698_parse_sec_SID_MAC(struct DLT_698_PRIVATE *ins_ptr)
{
    return dlt_698_parse_sid_mac(ins_ptr, &ins_ptr->frame.req_sec->verify.SID_MAC);
}
static const dlt_698_sec_fun dlt_698_sec_req_fun_table[] = {
    dlt_698_parse_sec_SID_MAC,    // 0
    dlt_698_parse_sec_RN,         // 1
    dlt_698_parse_sec_RN_MAC,     // 2
    dlt_698_parse_sec_SID         // 3
};
/*解析请求时的安全相关数据项*/
int16_t dlt_698_parse_security_req(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame._sec_type = DLT_698_SEC_REQ;
    ins_ptr->frame.req_sec = (struct DLT_698_SEC_REQ *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_SEC_REQ));
    if (ins_ptr->frame.req_sec == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    ins_ptr->frame.type = DLT_698_FRAME_TYPE_SEC_REQ;
    /*安全请求帧头至少需要 APDU类型 一个字节*/
    if (dlt_698_payld_need(ins_ptr, 1) != DLT_698_ERR_NONE)
    {
        return DLT_698_ERR_OVER;
    }
    uint8_t apdu_type = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    ins_ptr->frame.req_sec->apdu_type = apdu_type;
    int16_t ret = DLT_698_ERR_NONE;
    switch (apdu_type)
    {
        case 0:    ///< [0]明文数据单元 octet-string
        case 1:    ///< [1]密文数据单元 octet-string
            ret = dlt_698_parse_octet_string(ins_ptr, &ins_ptr->frame.req_sec->apdu_data);
            break;
        default:
            ret = DLT_698_ERR_PARSE;
            break;
    }
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }

    /*安全请求的验证信息类型至少需要一个字节*/
    if (dlt_698_payld_need(ins_ptr, 1) != DLT_698_ERR_NONE)
    {
        return DLT_698_ERR_OVER;
    }
    uint8_t verify_type = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    ins_ptr->frame.req_sec->verify_type = verify_type;
    if (verify_type >= (sizeof(dlt_698_sec_req_fun_table)) / (sizeof(dlt_698_sec_req_fun_table[0])))
    {
        // TODO::get handle 函数索引超出预定数组，需要进行异常处理
        return DLT_698_ERR_PARSE;
    }
    ret = dlt_698_sec_req_fun_table[verify_type](ins_ptr);
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    if (apdu_type == 0)    // 明文数据单元继续解析
    {
        uint16_t field_len = 0;
        uint16_t content_len = 0;
        uint16_t axdr_index = ins_ptr->frame.req_sec->apdu_data.index;
        uint16_t remain = (axdr_index < ins_ptr->_payld_len) ? (uint16_t)(ins_ptr->_payld_len - axdr_index) : 0;
        ret = dlt_698_parse_axdr_len(ins_ptr->_payld_ptr + axdr_index, remain, &field_len, &content_len);
        if (ret != DLT_698_ERR_NONE || (uint32_t)axdr_index + field_len + content_len > ins_ptr->_payld_len)
        {
            return DLT_698_ERR_OVER;
        }
        ins_ptr->_payld_index = (uint16_t)(axdr_index + field_len);
        ret = dlt_698_parse_entry(parser);
    }

    return ret;
}

/*解析安全数据项，SID_MAC*/
static int16_t dlt_698_parse_sec_res_MAC(struct DLT_698_PRIVATE *ins_ptr)
{
    return dlt_698_parse_mac(ins_ptr, &ins_ptr->frame.res_sec->verify_ptr->verify_data.MAC);
}
static const dlt_698_sec_fun dlt_698_sec_res_fun_table[] = {
    dlt_698_parse_sec_res_MAC,    // 0

};
/*********security response********* */
/*解析响应时的安全相关数据项*/
int16_t dlt_698_parse_security_res(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame._sec_type = DLT_698_SEC_RES;
    ins_ptr->frame.res_sec = (struct DLT_698_SEC_RES *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_SEC_RES));
    if (ins_ptr->frame.res_sec == NULL)
    {
        return DLT_698_ERR_MEM;
    }
    ins_ptr->frame.type = DLT_698_FRAME_TYPE_SEC_RES;
    /*安全响应帧头至少需要 APDU类型 一个字节*/
    if (dlt_698_payld_need(ins_ptr, 1) != DLT_698_ERR_NONE)
    {
        return DLT_698_ERR_OVER;
    }
    uint8_t apdu_type = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    ins_ptr->frame.res_sec->apdu_type = apdu_type;
    int16_t ret = DLT_698_ERR_NONE;
    switch (apdu_type)
    {
        case 0:    ///< [0]明文数据单元 octet-string
        case 1:    ///< [1]密文数据单元 octet-string
            ret = dlt_698_parse_octet_string(ins_ptr, &ins_ptr->frame.res_sec->apdu.apdu_data);
            break;
        case 2:    ///< [2]错误码
            /*错误码 DAR 至少需要一个字节*/
            if (dlt_698_payld_need(ins_ptr, 1) != DLT_698_ERR_NONE)
            {
                return DLT_698_ERR_OVER;
            }
            ins_ptr->frame.res_sec->apdu.dar = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
            break;
        default:
            ret = DLT_698_ERR_PARSE;
            break;
    }
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    /*验证信息可选标志至少需要一个字节*/
    if (dlt_698_payld_need(ins_ptr, 1) != DLT_698_ERR_NONE)
    {
        return DLT_698_ERR_OVER;
    }
    uint8_t verify_optional = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    if (verify_optional == 0)    ///< 无数据验证信息
    {
        ins_ptr->frame.res_sec->verify_ptr = NULL;
    }
    else
    {
        ins_ptr->frame.res_sec->verify_ptr = (struct DLT_698_VERIFY_INFO *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_VERIFY_INFO));
        if (ins_ptr->frame.res_sec->verify_ptr == NULL)
        {
            return DLT_698_ERR_MEM;
        }
        /*验证信息类型至少需要一个字节*/
        if (dlt_698_payld_need(ins_ptr, 1) != DLT_698_ERR_NONE)
        {
            return DLT_698_ERR_OVER;
        }
        uint8_t verify_type = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
        ins_ptr->frame.res_sec->verify_ptr->verify_type = verify_type;
        if ((verify_type < 0) || (verify_type >= (sizeof(dlt_698_sec_res_fun_table)) / (sizeof(dlt_698_sec_res_fun_table[0]))))
        {
            // TODO::get handle 函数索引超出预定数组，需要进行异常处理
            return DLT_698_ERR_PARSE;
        }
        ret = dlt_698_sec_res_fun_table[verify_type](ins_ptr);
    }
    if (ret != DLT_698_ERR_NONE)
    {
        return ret;
    }
    if (apdu_type == 0)    // 明文数据单元继续解析
    {
        uint16_t field_len = 0;
        uint16_t content_len = 0;
        uint16_t axdr_index = ins_ptr->frame.res_sec->apdu.apdu_data.index;
        uint16_t remain = (axdr_index < ins_ptr->_payld_len) ? (uint16_t)(ins_ptr->_payld_len - axdr_index) : 0;
        ret = dlt_698_parse_axdr_len(ins_ptr->_payld_ptr + axdr_index, remain, &field_len, &content_len);
        if (ret != DLT_698_ERR_NONE || (uint32_t)axdr_index + field_len + content_len > ins_ptr->_payld_len)
        {
            return DLT_698_ERR_OVER;
        }
        ins_ptr->_payld_index = (uint16_t)(axdr_index + field_len);
        ret = dlt_698_parse_entry(parser);
    }
    return ret;
}