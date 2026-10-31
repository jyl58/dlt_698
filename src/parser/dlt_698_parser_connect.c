#include "dlt_698_parser_connect.h"
#include "dlt_698_parser_widget.h"

int16_t dlt_698_parse_conn_req(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.req_conn = (struct DLT_698_CONN_REQ *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_CONN_REQ));
    if (ins_ptr->frame.content.req_conn == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    uint8_t *data_ptr = ins_ptr->_payld_ptr;
    uint16_t pos = ins_ptr->_payld_index;
    ins_ptr->frame.type = DLT_698_FRAME_TYPE_CONN_REQ;
    ins_ptr->frame.piid = data_ptr[pos++];
    struct DLT_698_CONN_REQ *conn_ptr = ins_ptr->frame.content.req_conn;
    ///< 期望的协议版本号
    conn_ptr->protocol_version = (data_ptr[pos] << 8) + data_ptr[pos + 1];
    pos += 2;
    ///< 期望的协议一致性块
    uint16_t len = sizeof(conn_ptr->protocol_conform) / sizeof(conn_ptr->protocol_conform[0]);
    for (uint16_t i = 0; i < len; i++)
    {
        conn_ptr->protocol_conform[i] = data_ptr[pos++];
    }
    ///< 期望的功能一致性块
    len = sizeof(conn_ptr->function_conform) / sizeof(conn_ptr->function_conform[0]);
    for (uint16_t i = 0; i < len; i++)
    {
        conn_ptr->function_conform[i] = data_ptr[pos++];
    }
    ///< 客户机发送帧最大尺寸
    conn_ptr->frame_send_max_size = (data_ptr[pos] << 8) + data_ptr[pos + 1];
    pos += 2;
    ///< 客户机接收帧最大尺寸
    conn_ptr->frame_recv_max_size = (data_ptr[pos] << 8) + data_ptr[pos + 1];
    pos += 2;
    ///< 客户机接收帧最大窗口尺寸
    conn_ptr->frame_recv_max_wnd_size = data_ptr[pos++];
    ///< 客户机最大可处理帧尺寸
    conn_ptr->frame_handle_max_size = (data_ptr[pos] << 8) + data_ptr[pos + 1];
    pos += 2;
    ///< 期望的应用连接超时时间
    conn_ptr->connect_timeout = (data_ptr[pos] << 24) + (data_ptr[pos + 1] << 16) + (data_ptr[pos + 2] << 8) + data_ptr[pos + 3];
    ;
    pos += 4;
    ///< 认证请求对象类型选择
    conn_ptr->sec_choice = data_ptr[pos++];
    ///< 设置解析位置
    ins_ptr->_payld_index = pos;
    int16_t ret = DLT_698_ERR_NONE;
    switch (conn_ptr->sec_choice)
    {
        case 0:
            ret = dlt_698_parse_null(ins_ptr, &conn_ptr->security.null_data);
            break;
        case 1:
            ret = dlt_698_parse_visible_string(ins_ptr, &conn_ptr->security.password.security);
            break;
        case 2:
            ret = dlt_698_parse_octet_string(ins_ptr, &conn_ptr->security.symmetry.ciphertext);
            if (ret == DLT_698_ERR_NONE)
            {
                ret = dlt_698_parse_octet_string(ins_ptr, &conn_ptr->security.symmetry.signature);
            }
            break;
        case 3:
            ret = dlt_698_parse_octet_string(ins_ptr, &conn_ptr->security.signature.ciphertext);
            if (ret == DLT_698_ERR_NONE)
            {
                ret = dlt_698_parse_octet_string(ins_ptr, &conn_ptr->security.signature.signature);
            }
            break;
        default:
            ret = DLT_698_ERR_PARSE;
            break;
    }
    if (ret == DLT_698_ERR_NONE)    // 解析成功
    {
        ret = dlt_698_parse_TimeTag(ins_ptr, &ins_ptr->frame.time_tag);
    }
    return ret;
}
int16_t dlt_698_parse_conn_res(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.res_conn = (struct DLT_698_CONN_RES *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_CONN_RES));
    if (ins_ptr->frame.content.res_conn == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    uint8_t *data_ptr = ins_ptr->_payld_ptr;
    uint16_t pos = ins_ptr->_payld_index;
    ins_ptr->frame.type = DLT_698_FRAME_TYPE_CONN_RES;
    ins_ptr->frame.piid = data_ptr[pos++];
    struct DLT_698_CONN_RES *conn_ptr = ins_ptr->frame.content.res_conn;
    ///< 服务器厂商版本信息-厂商代码
    uint16_t len = sizeof(conn_ptr->factory_verison.factory_code) / sizeof(conn_ptr->factory_verison.factory_code[0]);
    for (uint16_t i = 0; i < len; i++)
    {
        conn_ptr->factory_verison.factory_code[i] = data_ptr[pos++];
    }
    ///< 服务器厂商版本信息-软件版本号
    len = sizeof(conn_ptr->factory_verison.software_version) / sizeof(conn_ptr->factory_verison.software_version[0]);
    for (uint16_t i = 0; i < len; i++)
    {
        conn_ptr->factory_verison.software_version[i] = data_ptr[pos++];
    }
    ///< 服务器厂商版本信息-软件版本日期
    len = sizeof(conn_ptr->factory_verison.software_date) / sizeof(conn_ptr->factory_verison.software_date[0]);
    for (uint16_t i = 0; i < len; i++)
    {
        conn_ptr->factory_verison.software_date[i] = data_ptr[pos++];
    }
    ///< 服务器厂商版本信息-硬件版本号
    len = sizeof(conn_ptr->factory_verison.hardware_version) / sizeof(conn_ptr->factory_verison.hardware_version[0]);
    for (uint16_t i = 0; i < len; i++)
    {
        conn_ptr->factory_verison.hardware_version[i] = data_ptr[pos++];
    }
    ///< 服务器厂商版本信息-硬件版本日期
    len = sizeof(conn_ptr->factory_verison.hardware_date) / sizeof(conn_ptr->factory_verison.hardware_date[0]);
    for (uint16_t i = 0; i < len; i++)
    {
        conn_ptr->factory_verison.hardware_date[i] = data_ptr[pos++];
    }
    ///< 服务器厂商版本信息-厂商拓展信息
    len = sizeof(conn_ptr->factory_verison.factory_extension) / sizeof(conn_ptr->factory_verison.factory_extension[0]);
    for (uint16_t i = 0; i < len; i++)
    {
        conn_ptr->factory_verison.factory_extension[i] = data_ptr[pos++];
    }
    ///< 商定的协议版本号
    conn_ptr->protocol_version = (data_ptr[pos] << 8) + data_ptr[pos + 1];
    pos += 2;
    ///< 商定的协议一致性块
    len = sizeof(conn_ptr->protocol_conform) / sizeof(conn_ptr->protocol_conform[0]);
    for (uint16_t i = 0; i < len; i++)
    {
        conn_ptr->protocol_conform[i] = data_ptr[pos++];
    }
    ///< 商定的功能一致性块
    len = sizeof(conn_ptr->function_conform) / sizeof(conn_ptr->function_conform[0]);
    for (uint16_t i = 0; i < len; i++)
    {
        conn_ptr->function_conform[i] = data_ptr[pos++];
    }
    ///< 服务器发送帧最大尺寸
    conn_ptr->frame_send_max_size = (data_ptr[pos] << 8) + data_ptr[pos + 1];
    pos += 2;
    ///< 服务器接收帧最大尺寸
    conn_ptr->frame_recv_max_size = (data_ptr[pos] << 8) + data_ptr[pos + 1];
    pos += 2;
    ///<  服务器接收帧最大窗口尺寸
    conn_ptr->frame_recv_max_wnd_size = data_ptr[pos++];
    ///< 服务器最大可处理帧尺寸
    conn_ptr->frame_handle_max_size = (data_ptr[pos] << 8) + data_ptr[pos + 1];
    pos += 2;
    ///< 商定的应用连接超时时间
    conn_ptr->connect_timeout = (data_ptr[pos] << 24) + (data_ptr[pos + 1] << 16) + (data_ptr[pos + 2] << 8) + data_ptr[pos + 3];
    ;
    pos += 4;
    ///< 认证请求对象
    conn_ptr->res_info.connect_result = data_ptr[pos++];
    conn_ptr->res_info.optional = data_ptr[pos++];
    ///< 设置解析位置
    ins_ptr->_payld_index = pos;
    int16_t ret = DLT_698_ERR_NONE;
    if (conn_ptr->res_info.optional == 0)
    {
        conn_ptr->res_info.verify.null_data = (dlt_698_data_t *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(dlt_698_data_t));
        if (conn_ptr->res_info.verify.null_data == NULL)
        {
            ret = DLT_698_ERR_EMPTY_PTR;
        }
        else
        {
            ret = dlt_698_parse_null(ins_ptr, conn_ptr->res_info.verify.null_data);
        }
    }
    else if (conn_ptr->res_info.optional == 1)
    {
        conn_ptr->res_info.verify.sec_data = (struct DLT_698_Security_Data *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_Security_Data));
        if (!conn_ptr->res_info.verify.sec_data)
        {
            ret = DLT_698_ERR_OVER;
        }
        else
        {
            ret = dlt_698_parse_rn(ins_ptr, &conn_ptr->res_info.verify.sec_data->RN);
            if (ret == DLT_698_ERR_NONE)
            {
                ret = dlt_698_parse_octet_string(ins_ptr, &conn_ptr->res_info.verify.sec_data->info);
            }
        }
    }
    else if (conn_ptr->res_info.optional == 2)
    {
        conn_ptr->res_info.verify.rsa_pub_key = (struct DLT_698_RSA_Public_Key *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_RSA_Public_Key));
        if (!conn_ptr->res_info.verify.rsa_pub_key)
        {
            ret = DLT_698_ERR_OVER;
        }
        else
        {
            dlt_698_parse_visible_string(ins_ptr, &conn_ptr->res_info.verify.rsa_pub_key->modulus);
            if (ret == DLT_698_ERR_NONE)
            {
                ret = dlt_698_parse_octet_string(ins_ptr, &conn_ptr->res_info.verify.rsa_pub_key->key);
            }
        }
    }
    else
    {
        ret = DLT_698_ERR_PARSE;
    }
    if (ret == DLT_698_ERR_NONE)
    {
        ret = dlt_698_parse_FollowReportTag(ins_ptr, &ins_ptr->frame.follow_report);
        if (ret == DLT_698_ERR_NONE)
        {
            ret = dlt_698_parse_TimeTag(ins_ptr, &ins_ptr->frame.time_tag);
        }
    }
    return ret;
}
int16_t dlt_698_parse_rel_req(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.type = DLT_698_FRAME_TYPE_REL_REQ;
    ins_ptr->frame.piid = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    int16_t ret = dlt_698_parse_TimeTag(ins_ptr, &ins_ptr->frame.time_tag);


    return ret;
}
int16_t dlt_698_parse_rel_res(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.res_rel = (struct DLT_698_REL_RES *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_REL_RES));
    if (ins_ptr->frame.content.res_rel == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    ins_ptr->frame.type = DLT_698_FRAME_TYPE_REL_RES;
    ins_ptr->frame.piid = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    ins_ptr->frame.content.res_rel->result = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    return DLT_698_ERR_NONE;
}
int16_t dlt_698_parse_rel_ntf(dlt_698_parser *parser)
{
    struct DLT_698_PRIVATE *ins_ptr = (struct DLT_698_PRIVATE *)parser->_ins;
    ins_ptr->frame.content.rel_nty = (struct DLT_698_REL_NTF *)dlt_698_mempool_alloc(&ins_ptr->_mem, sizeof(struct DLT_698_REL_NTF));
    if (ins_ptr->frame.content.rel_nty == NULL)
    {
        return DLT_698_ERR_EMPTY_PTR;
    }
    ins_ptr->frame.type = DLT_698_FRAME_TYPE_REL_NTY;
    ins_ptr->frame.piid = ins_ptr->_payld_ptr[ins_ptr->_payld_index++];
    dlt_698_parse_date_time_s(ins_ptr, &ins_ptr->frame.content.rel_nty->link_dt);
    dlt_698_parse_date_time_s(ins_ptr, &ins_ptr->frame.content.rel_nty->cur_dt);
    return DLT_698_ERR_NONE;
}