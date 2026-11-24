#include "dlt_698_test_server.h"
#include "dlt_698_utl_take.h"
#include "dlt_698_parser.h"
#include "dlt_698_parser_get_normal.h"
#include "dlt_698_parser_get_record.h"
#include "dlt_698_parser_get_next.h"
#include "dlt_698_parser_get_md5.h"
#include "dlt_698_parser_set_normal.h"
#include "dlt_698_parser_action_normal.h"
#include "dlt_698_parser_report_normal.h"
#include "dlt_698_parser_security_normal.h"
#include "dlt_698_parser_link_normal.h"
#include "dlt_698_parser_connect_normal.h"
#include "dlt_698_utl_tools.h"
#include "dlt_698_utl_print.h"
#include "dlt_698_demo_take.h"

struct DLT_698_DATA_HANDLE
{
    enum DLT_698_FRAME_TYPE type;
    dlt_698_cb _handle;
} dlt_698_handle_tb[] = {{DLT_698_FRAME_TYPE_LINK_REQ, handle_link_req}, {DLT_698_FRAME_TYPE_CONN_REQ, handle_conn_req}, {DLT_698_FRAME_TYPE_GET_REQ, handle_get_req},
                         {DLT_698_FRAME_TYPE_SET_REQ, handle_set_req},   {DLT_698_FRAME_TYPE_ACT_REQ, handle_act_req},   {DLT_698_FRAME_TYPE_SEC_REQ, handle_sec_req},
                         {DLT_698_FRAME_TYPE_REP_RES, handle_rep_res}};
void handle_get_req(dlt_698_parser *parser)
{
    int16_t method = dlt_698_take_method(parser);
    switch ((enum DLT_698_GET_METHOD)method)
    {
        case DLT_698_GET_METHOD_NOR:         // GET NOMARL
        case DLT_698_GET_METHOD_NOR_LIST:    // GET NORMAL List
            dlt_server_handle_get_normal(parser);
            break;
        case DLT_698_GET_METHOD_RECORD:    // GET RECORD
        case DLT_698_GET_METHOD_RECORD_LIST:
            dlt_server_handle_get_record(parser);
            break;
        case DLT_698_GET_METHOD_NEXT:
            dlt_server_handle_get_next(parser);
            break;
        case DLT_698_GET_METHOD_MD5:
            dlt_server_handle_get_md5(parser);
            break;
        default:
            break;
    }

    dlt_698_utl_print_time_tag(parser);
}
void dlt_698_utl_server_handler(dlt_698_parser *parser)
{
    dlt_698_utl_print_head(parser);
    /* 字段提取示例: 提取帧头字段 */
    demo_take_frame_fields(parser);
    uint8_t sect_type = DLT_698_SEC_COMMON;
    dlt_698_take_sec_type(parser, &sect_type);
    if (sect_type == DLT_698_SEC_COMMON)
    {
        int16_t type = dlt_698_take_type(parser);
        for (int i = 0; i < sizeof(dlt_698_handle_tb) / sizeof(dlt_698_handle_tb[0]); i++)
        {
            if (dlt_698_handle_tb[i].type == type)
            {
                if (NULL != dlt_698_handle_tb[i]._handle)
                {
                    dlt_698_handle_tb[i]._handle(parser);
                }
            }
        }
    }
    else
    {
        handle_sec_req(parser);
    }
    /* 字段提取示例: 提取APDU内各数据字段的值 */
    demo_take_apdu_fields(parser);
    dlt_698_utl_print_mempool_status(parser);
}
void DLT_WEAK dlt_server_handle_get_normal(dlt_698_parser *parser)
{
    struct DLT_698_GET_NOR_REQ *data = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_GET_REQ, dlt_698_take_method(parser), (void **)&data);
    if (NULL == data)
    {
        DLT_printf("take normal data err.");
        return;
    }
    printf("----oad cnt=%d\n", dlt_698_get_common_sibling_cnt(parser, data->oad_ptr, offsetof(dlt_698_data_t, next_index)));
    uint8_t arry[] = {0x30, 0x2D, 0x06, 0x01};    // 30060503
    dlt_698_data_t *node_ptr = NULL;
    dlt_698_find_data(parser, data->oad_ptr, &node_ptr, DLT_698_TYPE_OOP_OAD, arry, sizeof(arry) / sizeof(arry[0]));
    if (NULL != node_ptr)
    {
        printf("--------find--------\n");
        dlt_698_utl_print_node_data(parser, node_ptr);
        printf("--------find--------\n");
    }
    // 做打印处理,验证数据有效性
    dlt_698_utl_print_data(parser, data->oad_ptr);
}
void DLT_WEAK dlt_server_handle_get_record(dlt_698_parser *parser)
{
    struct DLT_698_GET_REC_REQ *data = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_GET_REQ, dlt_698_take_method(parser), (void **)&data);
    if (NULL == data)
    {
        DLT_printf("take record data err.");
        return;
    }
    // DLT_printf("get record cnt=%d\n",dlt_698_request_record_sibling_cnt(parser,data->rec_ptr));
    struct DLT_698_GET_RECORD *rec_ptr = data->rec_ptr;
    while (NULL != rec_ptr)
    {
        // OAD
        DLT_printf("OAD=");
        dlt_698_utl_print_data(parser, &rec_ptr->oad);
        // RSD
        DLT_printf("RSD=");
        dlt_698_utl_print_data(parser, &rec_ptr->rsd);
        // RCSD
        DLT_printf("RCSD=");
        dlt_698_utl_print_data(parser, &rec_ptr->rcsd);
        rec_ptr = dlt_698_get_next_ptr(parser, rec_ptr->next_index);
    }
}
void DLT_WEAK dlt_server_handle_get_next(dlt_698_parser *parser)
{
    struct DLT_698_GET_NEXT_REQ *data = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_GET_REQ, dlt_698_take_method(parser), (void **)&data);
    if (NULL == data)
    {
        DLT_printf("take normal data err.");
        // 提取数据异常
        return;
    }
    printf("recv last frame:%d\n", data->last_frame);
}
void DLT_WEAK dlt_server_handle_get_md5(dlt_698_parser *parser)
{
    struct DLT_698_GET_MD5_REQ *data = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_GET_REQ, dlt_698_take_method(parser), (void **)&data);
    if (NULL == data)
    {
        DLT_printf("take normal data err.");
        // 提取数据异常
        return;
    }
    dlt_698_utl_print_data(parser, &data->oad);
}
/**处理设置请求数据 */
void handle_set_req(dlt_698_parser *parser)
{
    int16_t method = dlt_698_take_method(parser);
    switch ((enum DLT_698_SET_METHOD)method)
    {
        case DLT_698_SET_METHOD_NOR:
        case DLT_698_SET_METHOD_NOR_LIST:
            dlt_server_handle_set_normal(parser);
            break;
        case DLT_698_SET_METHOD_SET_GET_LIST:
            dlt_server_handle_set_get_normal(parser);
            break;
        default:
            break;
    }
    dlt_698_utl_print_time_tag(parser);
}
void DLT_WEAK dlt_server_handle_set_normal(dlt_698_parser *parser)
{
    struct DLT_698_SET_NOR_REQ *data = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_SET_REQ, dlt_698_take_method(parser), (void **)&data);
    if (NULL == data)
    {
        DLT_printf("take set apdu err.\n");
        // 提取数据异常
        return;
    }
    struct DLT_698_SET_ATTRIBUTE *set_ptr = data->set_ptr;
    //  printf("set attribute cnt=%d\n",dlt_698_set_attribute_sibling_cnt(parser,set_ptr));
    while (set_ptr)
    {
        // OAD
        DLT_printf("SET.OAD=");
        dlt_698_utl_print_data(parser, &set_ptr->oad);
        // DATA
        DLT_printf("SET.DATA=");
        dlt_698_utl_print_data(parser, &set_ptr->data);

        set_ptr = dlt_698_get_next_ptr(parser, set_ptr->next_index);
    }
}
void DLT_WEAK dlt_server_handle_set_get_normal(dlt_698_parser *parser)
{
    struct DLT_698_SET_GET_REQ *data = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_SET_REQ, dlt_698_take_method(parser), (void **)&data);
    if (NULL == data)
    {
        DLT_printf("take set apdu err.\n");
        // 提取数据异常
        return;
    }
    struct DLT_698_SET_GET_ATTRIBUTE *set_ptr = data->set_ptr;
    // printf("set get attribute cnt=%d\n",dlt_698_set_get_attribute_sibling_cnt(parser,set_ptr));
    while (set_ptr)
    {
        // SET OAD
        DLT_printf("SET.SET_OAD=");
        dlt_698_utl_print_data(parser, &set_ptr->set_oad);
        DLT_printf("SET.SET_DATA=");
        dlt_698_utl_print_data(parser, &set_ptr->set_data);
        DLT_printf("SET.GET_OAD=");
        dlt_698_utl_print_data(parser, &set_ptr->get_oad);
        DLT_printf("SET.Delay=%02X\n", set_ptr->delay);

        set_ptr = dlt_698_get_next_ptr(parser, set_ptr->next_index);
    }
}
void handle_act_req(dlt_698_parser *parser)
{
    int16_t method = dlt_698_take_method(parser);
    switch ((enum DLT_698_ACT_METHOD)method)
    {
        case DLT_698_ACT_METHOD_NOR:
        case DLT_698_ACT_METHOD_NOR_LIST:
            dlt_server_handle_act_normal(parser);
            break;
        case DLT_698_ACT_METHOD_SET_GET_LIST:
            dlt_server_handle_act_get_normal(parser);
            break;
        default:
            break;
    }
    dlt_698_utl_print_time_tag(parser);
}
void DLT_WEAK dlt_server_handle_act_normal(dlt_698_parser *parser)
{
    struct DLT_698_ACT_NOR_REQ *data = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_ACT_REQ, dlt_698_take_method(parser), (void **)&data);
    if (NULL == data)
    {
        DLT_printf("take act apdu err.\n");
        // 提取数据异常
        return;
    }
    struct DLT_698_ACT_METHOD_PARA *act_ptr = data->act_ptr;
    // printf("act method para cnt=%d\n",dlt_698_act_method_para_sibling_cnt(parser,act_ptr));
    while (act_ptr)
    {
        DLT_printf("ACT.OMD=");
        dlt_698_utl_print_data(parser, &act_ptr->omd);

        DLT_printf("ACT.DATA=");
        dlt_698_utl_print_data(parser, &act_ptr->data);

        act_ptr = dlt_698_get_next_ptr(parser, act_ptr->next_index);
    }
}
void DLT_WEAK dlt_server_handle_act_get_normal(dlt_698_parser *parser)
{
    struct DLT_698_ACT_GET_REQ *data = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_ACT_REQ, dlt_698_take_method(parser), (void **)&data);
    if (NULL == data)
    {
        DLT_printf("take act apdu err.\n");
        // 提取数据异常
        return;
    }
    struct DLT_698_ACT_GET_MOTHOD_PARA *act_ptr = data->act_ptr;
    // printf("act get method para cnt=%d\n",dlt_698_act_get_method_para_sibling_cnt(parser,act_ptr));
    while (act_ptr)
    {
        // ACT OAD
        DLT_printf("ACT.ACT_OMD=");
        dlt_698_utl_print_data(parser, &act_ptr->act_omd);
        DLT_printf("ACT.ACT_DATA=");
        dlt_698_utl_print_data(parser, &act_ptr->data);
        DLT_printf("ACT.GET_OAD=");
        dlt_698_utl_print_data(parser, &act_ptr->get_oad);
        DLT_printf("ACT.Delay=%d\n", act_ptr->delay);

        act_ptr = dlt_698_get_next_ptr(parser, act_ptr->next_index);
    }
}
void handle_sec_req(dlt_698_parser *parser)
{
    struct DLT_698_SEC_REQ *sec = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_SEC_REQ, 0, (void **)&sec);
    if (NULL == sec)
    {
        DLT_printf("take security res data err.");
        // 提取数据异常
        return;
    }
    printf("apdu type=%d\n", sec->apdu_type);
    printf("apdu data=");
    dlt_698_utl_print_data(parser, &sec->apdu_data);
    printf("verify type=%d\n", sec->verify_type);
    if (sec->apdu_type == 0)    // 明文数据单元继续解析
    {
        int16_t type = dlt_698_take_type(parser);
        for (int i = 0; i < sizeof(dlt_698_handle_tb) / sizeof(dlt_698_handle_tb[0]); i++)
        {
            if (dlt_698_handle_tb[i].type == type)
            {
                if (NULL != dlt_698_handle_tb[i]._handle)
                {
                    dlt_698_handle_tb[i]._handle(parser);
                }
            }
        }
    }

    switch (sec->verify_type)
    {
        case 0:
        {
            dlt_698_utl_print_data(parser, &sec->verify.SID_MAC);
        }
        break;
        case 1:
        {
            dlt_698_utl_print_data(parser, &sec->verify.RN);
        }
        break;
        case 2:
        {
            dlt_698_utl_print_data(parser, &sec->verify.RN_MAC.RN);
            dlt_698_utl_print_data(parser, &sec->verify.RN_MAC.MAC);
        }
        break;
        case 3:
        {
            dlt_698_utl_print_data(parser, &sec->verify.SID);
        }
        break;
        default:
            break;
    }
}
void DLT_WEAK dlt_server_handle_rep_notify(dlt_698_parser *parser)
{
    struct DLT_698_REP_RES_NOR *data = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_REP_RES, dlt_698_take_method(parser), (void **)&data);
    if (NULL == data)
    {
        DLT_printf("take report data err.");
        // 提取数据异常
        return;
    }
    // 做打印处理,验证数据有效性
    dlt_698_utl_print_data(parser, data->oad_ptr);
    dlt_698_utl_print_time_tag(parser);
}
void DLT_WEAK dlt_server_handle_rep_trans(dlt_698_parser *parser)
{
    DLT_printf("Report trans ok.\n");
}
void handle_rep_res(dlt_698_parser *parser)
{
    int16_t method = dlt_698_take_method(parser);
    switch ((enum DLT_698_REP_METHOD)method)
    {
        case DLT_698_REP_METHOD_NOTIFY_LIST:
        case DLT_698_REP_METHOD_NOTIFY_RECORD_LIST:
            dlt_server_handle_rep_notify(parser);
            break;
        case DLT_698_REP_METHOD_NOTIFY_TRANS:
            dlt_server_handle_rep_trans(parser);
            break;
        default:
            break;
    }
}
void handle_link_req(dlt_698_parser *parser)
{
    struct DLT_698_LINK_REQ *link_ptr = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_LINK_REQ, 0, (void **)&link_ptr);
    if (NULL == link_ptr)
    {
        DLT_printf("take link req data err.");
        // 提取数据异常
        return;
    }
    printf("req type=%d\n", link_ptr->req_type);
    printf("heart_cycle=%d\n", link_ptr->heart_cycle);
    printf("req time=");
    dlt_698_utl_print_data(parser, &link_ptr->req_dt);
}
void handle_conn_req(dlt_698_parser *parser)
{
    struct DLT_698_CONN_REQ *conn_ptr = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_CONN_REQ, 0, (void **)&conn_ptr);
    if (NULL == conn_ptr)
    {
        DLT_printf("take connect req data err.");
        // 提取数据异常
        return;
    }
    DLT_printf("期望的协议版本号=%d\n", conn_ptr->protocol_version);
    uint16_t len = sizeof(conn_ptr->protocol_conform) / sizeof(conn_ptr->protocol_conform[0]);
    DLT_printf("期望的协议一致性块=");
    for (uint16_t i = 0; i < len; i++)
    {
        printf("%02X", conn_ptr->protocol_conform[i]);
    }
    DLT_printf("\n");
    DLT_printf("期望的功能一致性块=");
    len = sizeof(conn_ptr->function_conform) / sizeof(conn_ptr->function_conform[0]);
    for (uint16_t i = 0; i < len; i++)
    {
        printf("%02X", conn_ptr->function_conform[i]);
    }
    DLT_printf("\n");
    DLT_printf("客户机发送帧最大尺寸=%d\n", conn_ptr->frame_send_max_size);
    DLT_printf("客户机接收帧最大尺寸=%d\n", conn_ptr->frame_recv_max_size);
    DLT_printf("客户机接收帧最大窗口尺寸=%d\n", conn_ptr->frame_recv_max_wnd_size);
    DLT_printf("客户机最大可处理帧尺寸=%d\n", conn_ptr->frame_handle_max_size);
    DLT_printf("期望的应用连接超时时间=%d\n", conn_ptr->connect_timeout);
    DLT_printf("认证请求对象类型=%d\n", conn_ptr->sec_choice);
    switch (conn_ptr->sec_choice)
    {
        case 0:
            dlt_698_utl_print_data(parser, &conn_ptr->security.null_data);
            break;
        case 1:
            dlt_698_utl_print_data(parser, &conn_ptr->security.password.security);
            break;
        case 2:
            dlt_698_utl_print_data(parser, &conn_ptr->security.symmetry.ciphertext);
            dlt_698_utl_print_data(parser, &conn_ptr->security.symmetry.signature);
            break;
        case 3:
            dlt_698_utl_print_data(parser, &conn_ptr->security.signature.ciphertext);
            dlt_698_utl_print_data(parser, &conn_ptr->security.signature.signature);
            break;
        default:
            break;
    }
    dlt_698_utl_print_time_tag(parser);
}