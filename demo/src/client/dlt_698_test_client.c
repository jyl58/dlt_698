#include "dlt_698_test_client.h"
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
#include "dlt_698_utl_data.h"
#include "dlt_698_demo_take.h"

struct DLT_698_DATA_HANDLE
{
    enum DLT_698_FRAME_TYPE type;
    dlt_698_cb _handle;
} dlt_698_handle_res_tb[] = {{DLT_698_FRAME_TYPE_LINK_RES, handle_link_res}, {DLT_698_FRAME_TYPE_CONN_RES, handle_conn_res}, {DLT_698_FRAME_TYPE_REL_RES, handle_rel_res},
                             {DLT_698_FRAME_TYPE_REL_NTY, handle_rel_nty},   {DLT_698_FRAME_TYPE_GET_RES, handle_get_res},   {DLT_698_FRAME_TYPE_SET_RES, handle_set_res},
                             {DLT_698_FRAME_TYPE_ACT_RES, handle_act_res},   {DLT_698_FRAME_TYPE_SEC_RES, handle_sec_res},   {DLT_698_FRAME_TYPE_REP_REQ, handle_rep_req}};
void dlt_698_utl_client_handler(dlt_698_parser *parser)
{
    dlt_698_utl_print_head(parser);
    /* 字段提取示例: 提取帧头字段 */
    demo_take_frame_fields(parser);
    uint8_t sect_type = DLT_698_SEC_COMMON;
    dlt_698_take_sec_type(parser, &sect_type);
    if (sect_type == DLT_698_SEC_COMMON)
    {
        int16_t type = dlt_698_take_type(parser);
        for (int i = 0; i < sizeof(dlt_698_handle_res_tb) / sizeof(dlt_698_handle_res_tb[0]); i++)
        {
            if (dlt_698_handle_res_tb[i].type == type)
            {
                if (NULL != dlt_698_handle_res_tb[i]._handle)
                {
                    dlt_698_handle_res_tb[i]._handle(parser);
                }
            }
        }
    }
    else
    {
        handle_sec_res(parser);
    }
    /* 字段提取示例: 提取APDU内各数据字段的值 */
    demo_take_apdu_fields(parser);
    dlt_698_utl_print_mempool_status(parser);
}
void handle_get_res(dlt_698_parser *parser)
{
    int16_t method = dlt_698_take_method(parser);
    switch ((enum DLT_698_GET_METHOD)method)
    {
        case DLT_698_GET_METHOD_NOR:         // GET NOMARL
        case DLT_698_GET_METHOD_NOR_LIST:    // GET NORMAL List
            dlt_cli_handle_get_normal(parser);
            break;
        case DLT_698_GET_METHOD_RECORD:    // GET RECORD
        case DLT_698_GET_METHOD_RECORD_LIST:
            dlt_cli_handle_get_record(parser);
            break;
        case DLT_698_GET_METHOD_NEXT:
            dlt_cli_handle_get_record_next(parser);
            break;
        case DLT_698_GET_METHOD_MD5:
            dlt_cli_handle_get_md5(parser);
            break;
        default:
            break;
    }
    dlt_698_utl_print_follow_report(parser);
    dlt_698_utl_print_time_tag(parser);
}
void DLT_WEAK dlt_cli_handle_get_normal(dlt_698_parser *parser)
{
    struct DLT_698_GET_NOR_RES *data = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_GET_RES, dlt_698_take_method(parser), (void **)&data);
    if (NULL == data)
    {
        DLT_printf("take normal data err.");
        return;
    }
    DLT_printf("result normal cnt%d\n", dlt_698_get_common_sibling_cnt(parser, data->normal_ptr, offsetof(struct DLT_698_Result_Normal, next_index)));
    dlt_698_utl_print_result_normal(parser, data->normal_ptr);
}
void DLT_WEAK dlt_cli_handle_get_record(dlt_698_parser *parser)
{
    struct DLT_698_GET_REC_RES *data = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_GET_RES, dlt_698_take_method(parser), (void **)&data);
    if (NULL == data)
    {
        DLT_printf("take normal data err.");
        return;
    }
    dlt_698_utl_print_result_record(parser, data->rec_ptr);
}
void DLT_WEAK dlt_cli_handle_get_record_next(dlt_698_parser *parser)
{
    struct DLT_698_GET_NEXT_RES *next_res = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_GET_RES, dlt_698_take_method(parser), (void **)&next_res);
    if (NULL == next_res)
    {
        DLT_printf("take normal data err.");
        return;
    }
    DLT_printf("last frame flag= %d\n", next_res->is_end);
    DLT_printf("frame num= %d\n", next_res->frame_num);
    DLT_printf("data choice= %d\n", next_res->data_choice);
    switch (next_res->data_choice)
    {
        case 0:
            DLT_printf("dar= %d\n", next_res->next_data.dar);
            break;
        case 1:
        {
            dlt_698_utl_print_result_normal(parser, next_res->next_data.normal_ptr);
        }
        break;
        case 2:
        {
            dlt_698_utl_print_result_record(parser, next_res->next_data.record_ptr);
        }
        break;
    }
}
void DLT_WEAK dlt_cli_handle_get_md5(dlt_698_parser *parser)
{
    struct DLT_698_GET_MD5_RES *md5_res = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_GET_RES, dlt_698_take_method(parser), (void **)&md5_res);
    if (NULL == md5_res)
    {
        DLT_printf("take normal data err.");
        return;
    }
    DLT_printf("MD5 OAD=");
    dlt_698_utl_print_data(parser, &md5_res->oad);
    DLT_printf("dar= %d\n", md5_res->dar);
    DLT_printf("MD5= ");
    dlt_698_utl_print_data(parser, &md5_res->data);
}
void handle_set_res(dlt_698_parser *parser)
{
    int16_t method = dlt_698_take_method(parser);
    switch ((enum DLT_698_SET_METHOD)method)
    {
        case DLT_698_SET_METHOD_NOR:         // SET NOMARL
        case DLT_698_SET_METHOD_NOR_LIST:    // SET NORMAL List
            dlt_cli_handle_set_normal(parser);
            break;
        case DLT_698_SET_METHOD_SET_GET_LIST:    // SetThenGetResponseNormalList
            dlt_cli_handle_set_get_normal(parser);
            break;
        default:
            break;
    }
    dlt_698_utl_print_follow_report(parser);
    dlt_698_utl_print_time_tag(parser);
}
void DLT_WEAK dlt_cli_handle_set_normal(dlt_698_parser *parser)
{
    struct DLT_698_SET_NOR_RES *data = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_SET_RES, dlt_698_take_method(parser), (void **)&data);
    if (NULL == data)
    {
        DLT_printf("take normal data err.");
        return;
    }
    struct DLT_698_SET_RESULT *result_ptr = data->result_ptr;
    // printf("set result cnt=%d\n",dlt_698_set_result_sibling_cnt(parser,result_ptr));
    while (result_ptr)
    {
        DLT_printf("SET_RES.OAD=");
        dlt_698_utl_print_data(parser, &result_ptr->oad);
        DLT_printf("SET_RES.DAR=%d\n", result_ptr->DAR);

        result_ptr = dlt_698_get_next_ptr(parser, result_ptr->next_index);
    }
}
void DLT_WEAK dlt_cli_handle_set_get_normal(dlt_698_parser *parser)
{
    struct DLT_698_SET_GET_RES *data = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_SET_RES, dlt_698_take_method(parser), (void **)&data);
    if (NULL == data)
    {
        DLT_printf("take normal data err.");
        // 提取数据异常
        return;
    }
    struct DLT_698_SET_GET_RESULT *result_ptr = data->result_ptr;
    // printf("set get result cnt=%d\n",dlt_698_set_get_result_sibling_cnt(parser,result_ptr));
    while (result_ptr)
    {
        DLT_printf("SET_RES.OAD=");
        dlt_698_utl_print_data(parser, &result_ptr->set_oad);
        DLT_printf("SET_RES.DAR=%d\n", result_ptr->DAR);
        DLT_printf("GET_RES.OAD=");
        dlt_698_utl_print_result_normal(parser, &result_ptr->result_nornaml);

        result_ptr = dlt_698_get_next_ptr(parser, result_ptr->next_index);
    }
}
void handle_act_res(dlt_698_parser *parser)
{
    int16_t method = dlt_698_take_method(parser);
    switch ((enum DLT_698_ACT_METHOD)method)
    {
        case DLT_698_ACT_METHOD_NOR:         // ACT NOMARL
        case DLT_698_ACT_METHOD_NOR_LIST:    // ACT NORMAL List
            dlt_cli_handle_act_normal(parser);
            break;
        case DLT_698_ACT_METHOD_SET_GET_LIST:    // ActionThenGetResponseNormalList
            dlt_cli_handle_act_get_normal(parser);
            break;
        default:
            break;
    }
    dlt_698_utl_print_follow_report(parser);
    dlt_698_utl_print_time_tag(parser);
}
void DLT_WEAK dlt_cli_handle_act_normal(dlt_698_parser *parser)
{
    struct DLT_698_ACT_NOR_RES *data = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_ACT_RES, dlt_698_take_method(parser), (void **)&data);
    if (NULL == data)
    {
        DLT_printf("act take normal data err.");
        // 提取数据异常
        return;
    }
    struct DLT_698_ACT_METHOD_RESULT *result_ptr = data->result_ptr;
    // printf("act method result cnt=%d\n",dlt_698_act_method_result_sibling_cnt(parser,result_ptr));
    while (result_ptr)
    {
        DLT_printf("ACT_RES.OMD=");
        dlt_698_utl_print_data(parser, &result_ptr->omd);
        DLT_printf("ACT_RES.DAR=%d\n", result_ptr->DAR);
        dlt_698_utl_print_data(parser, &result_ptr->data);

        result_ptr = dlt_698_get_next_ptr(parser, result_ptr->next_index);
    }
}
void DLT_WEAK dlt_cli_handle_act_get_normal(dlt_698_parser *parser)
{
    struct DLT_698_ACT_GET_RES *data = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_ACT_RES, dlt_698_take_method(parser), (void **)&data);
    if (NULL == data)
    {
        DLT_printf("act take normal data err.");
        // 提取数据异常
        return;
    }
    struct DLT_698_ACT_GET_MOTHOD_RESUlT *result_ptr = data->result_ptr;
    // printf("act method result cnt=%d\n",dlt_698_act_get_method_result_sibling_cnt(parser,result_ptr));
    while (result_ptr)
    {
        DLT_printf("ACT_RES.OMD=");
        dlt_698_utl_print_data(parser, &result_ptr->act_omd);
        DLT_printf("_RES.DAR=%d\n", result_ptr->DAR);
        DLT_printf("data=");
        dlt_698_utl_print_data(parser, &result_ptr->get_data);
        DLT_printf("A-ResultNormal=");
        dlt_698_utl_print_result_normal(parser, &result_ptr->result_normal);

        result_ptr = dlt_698_get_next_ptr(parser, result_ptr->next_index);
    }
}
void handle_rep_req(dlt_698_parser *parser)
{
    int16_t method = dlt_698_take_method(parser);
    switch ((enum DLT_698_REP_METHOD)method)
    {
        case DLT_698_REP_METHOD_NOTIFY_LIST:
            dlt_cli_handle_rep_notify(parser);
            break;
        case DLT_698_REP_METHOD_NOTIFY_RECORD_LIST:
            dlt_cli_handle_rep_record_notify(parser);
            break;
        case DLT_698_REP_METHOD_NOTIFY_TRANS:
            dlt_cli_handle_rep_trans_notify(parser);
            break;
        default:
            break;
    }
    dlt_698_utl_print_follow_report(parser);
    dlt_698_utl_print_time_tag(parser);
}
void DLT_WEAK dlt_cli_handle_rep_notify(dlt_698_parser *parser)
{
    struct DLT_698_REP_NTF_NOR *data = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_REP_REQ, dlt_698_take_method(parser), (void **)&data);
    if (NULL == data)
    {
        DLT_printf("take report apdu err.\n");
        // 提取数据异常
        return;
    }
    dlt_698_utl_print_result_normal(parser, data->normal_ptr);
}
void DLT_WEAK dlt_cli_handle_rep_record_notify(dlt_698_parser *parser)
{
    struct DLT_698_REP_NTF_REC *data = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_REP_REQ, dlt_698_take_method(parser), (void **)&data);
    if (NULL == data)
    {
        DLT_printf("take report apdu err.\n");
        // 提取数据异常
        return;
    }
    dlt_698_utl_print_result_record(parser, data->record_ptr);
}
void DLT_WEAK dlt_cli_handle_rep_trans_notify(dlt_698_parser *parser)
{
    struct DLT_698_REP_NTF_TRANS *trans_data = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_REP_REQ, dlt_698_take_method(parser), (void **)&trans_data);
    if (NULL == trans_data)
    {
        DLT_printf("take report apdu err.\n");
        // 提取数据异常
        return;
    }
    DLT_printf("REPORT OAD=");
    dlt_698_utl_print_data(parser, &trans_data->oad);
    DLT_printf("REPORT Data=");
    dlt_698_utl_print_data(parser, trans_data->data_ptr);
}
void handle_sec_res(dlt_698_parser *parser)
{
    struct DLT_698_SEC_RES *sec = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_SEC_RES, 0, (void **)&sec);
    if (NULL == sec)
    {
        DLT_printf("take security data err.");
        // 提取数据异常
        return;
    }
    printf("apdu type=%d\n", sec->apdu_type);
    if (sec->apdu_type == 0 || sec->apdu_type == 1)
    {
        printf("apdu data=");
        dlt_698_utl_print_data(parser, &sec->apdu.apdu_data);
    }
    else
    {
        printf("apdu dar=%d\n", sec->apdu.dar);
    }
    if (sec->apdu_type == 0)
    {
        int16_t type = dlt_698_take_type(parser);
        for (int i = 0; i < sizeof(dlt_698_handle_res_tb) / sizeof(dlt_698_handle_res_tb[0]); i++)
        {
            if (dlt_698_handle_res_tb[i].type == type)
            {
                if (NULL != dlt_698_handle_res_tb[i]._handle)
                {
                    dlt_698_handle_res_tb[i]._handle(parser);
                }
            }
        }
    }

    if (NULL == sec->verify_ptr)
    {
        printf("verify data=NULL\n");
    }
    else
    {
        printf("verify data_type=%d\n", sec->verify_ptr->verify_type);
        switch (sec->verify_ptr->verify_type)
        {
            case 0:
                dlt_698_utl_print_data(parser, &sec->verify_ptr->verify_data.MAC);
                break;
            default:
                break;
        }
    }
}
void handle_link_res(dlt_698_parser *parser)
{
    struct DLT_698_LINK_RES *link = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_LINK_RES, 0, (void **)&link);
    if (NULL == link)
    {
        DLT_printf("take security res data err.");
        // 提取数据异常
        return;
    }
    printf("result=%02x\n", link->result);
    printf("req time=");
    dlt_698_utl_print_data(parser, &link->req_dt);
    printf("req time=");
    dlt_698_utl_print_data(parser, &link->recv_dt);
    printf("res time=");
    dlt_698_utl_print_data(parser, &link->res_dt);
}
void handle_conn_res(dlt_698_parser *parser)
{
    struct DLT_698_CONN_RES *conn_ptr = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_CONN_RES, 0, (void **)&conn_ptr);
    if (NULL == conn_ptr)
    {
        DLT_printf("take connect res data err.");
        return;
    }
    uint16_t len = sizeof(conn_ptr->factory_verison.factory_code) / sizeof(conn_ptr->factory_verison.factory_code[0]);
    DLT_printf("服务器厂商版本信息-厂商代码=");
    for (uint16_t i = 0; i < len; i++)
    {
        DLT_printf("%02X", conn_ptr->factory_verison.factory_code[i]);
    }
    DLT_printf("\n");
    len = sizeof(conn_ptr->factory_verison.software_version) / sizeof(conn_ptr->factory_verison.software_version[0]);
    DLT_printf("服务器厂商版本信息-软件版本号=");
    for (uint16_t i = 0; i < len; i++)
    {
        DLT_printf("%02X", conn_ptr->factory_verison.software_version[i]);
    }
    DLT_printf("\n");
    len = sizeof(conn_ptr->factory_verison.software_date) / sizeof(conn_ptr->factory_verison.software_date[0]);
    DLT_printf("服务器厂商版本信息-软件版本日期=");
    for (uint16_t i = 0; i < len; i++)
    {
        DLT_printf("%02X", conn_ptr->factory_verison.software_date[i]);
    }
    DLT_printf("\n");
    len = sizeof(conn_ptr->factory_verison.hardware_version) / sizeof(conn_ptr->factory_verison.hardware_version[0]);
    DLT_printf("服务器厂商版本信息-硬件版本号=");
    for (uint16_t i = 0; i < len; i++)
    {
        DLT_printf("%02X", conn_ptr->factory_verison.hardware_version[i]);
    }
    DLT_printf("\n");
    len = sizeof(conn_ptr->factory_verison.hardware_date) / sizeof(conn_ptr->factory_verison.hardware_date[0]);
    DLT_printf("服务器厂商版本信息-硬件版本日期=");
    for (uint16_t i = 0; i < len; i++)
    {
        DLT_printf("%02X", conn_ptr->factory_verison.hardware_date[i]);
    }
    DLT_printf("\n");
    len = sizeof(conn_ptr->factory_verison.factory_extension) / sizeof(conn_ptr->factory_verison.factory_extension[0]);
    DLT_printf("服务器厂商版本信息-厂商拓展信息=");
    for (uint16_t i = 0; i < len; i++)
    {
        DLT_printf("%02X", conn_ptr->factory_verison.factory_extension[i]);
    }
    DLT_printf("\n");
    DLT_printf("商定的协议版本号=%d\n", conn_ptr->protocol_version);
    len = sizeof(conn_ptr->protocol_conform) / sizeof(conn_ptr->protocol_conform[0]);
    DLT_printf("商定的协议一致性块=");
    for (uint16_t i = 0; i < len; i++)
    {
        printf("%02X", conn_ptr->protocol_conform[i]);
    }
    DLT_printf("\n");
    DLT_printf("商定的功能一致性块=");
    len = sizeof(conn_ptr->function_conform) / sizeof(conn_ptr->function_conform[0]);
    for (uint16_t i = 0; i < len; i++)
    {
        printf("%02X", conn_ptr->function_conform[i]);
    }
    DLT_printf("\n");
    DLT_printf("服务器发送帧最大尺寸=%d\n", conn_ptr->frame_send_max_size);
    DLT_printf("服务器接收帧最大尺寸=%d\n", conn_ptr->frame_recv_max_size);
    DLT_printf("服务器接收帧最大窗口尺寸=%d\n", conn_ptr->frame_recv_max_wnd_size);
    DLT_printf("服务器最大可处理帧尺寸=%d\n", conn_ptr->frame_handle_max_size);
    DLT_printf("商定的应用连接超时时间 =%d\n", conn_ptr->connect_timeout);
    DLT_printf("连接响应对象-认证结果=%d\n", conn_ptr->res_info.connect_result);
    DLT_printf("连接响应对象-认证附加信息=%d\n", conn_ptr->res_info.optional);
    if (conn_ptr->res_info.optional == 0)
    {
        DLT_printf("无");
        dlt_698_utl_print_data(parser, conn_ptr->res_info.verify.null_data);
    }
    else if (conn_ptr->res_info.optional == 1)
    {
        DLT_printf("连接响应对象-服务器随机数");
        dlt_698_utl_print_data(parser, &conn_ptr->res_info.verify.sec_data->RN);
        DLT_printf("连接响应对象-服务器签名信息");
        dlt_698_utl_print_data(parser, &conn_ptr->res_info.verify.sec_data->info);
    }
    else if (conn_ptr->res_info.optional == 2)
    {
        DLT_printf("连接响应对象-模数");
        dlt_698_utl_print_data(parser, &conn_ptr->res_info.verify.rsa_pub_key->modulus);
        DLT_printf("连接响应对象-公钥");
        dlt_698_utl_print_data(parser, &conn_ptr->res_info.verify.rsa_pub_key->key);
    }
    dlt_698_utl_print_follow_report(parser);
    dlt_698_utl_print_time_tag(parser);
}
void handle_rel_res(dlt_698_parser *parser)
{
    struct DLT_698_REL_RES *conn_ptr = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_REL_RES, 0, (void **)&conn_ptr);
    if (NULL == conn_ptr)
    {
        DLT_printf("take connect res data err.");
        return;
    }
    DLT_printf("result=%d\n", conn_ptr->result);
}
void handle_rel_nty(dlt_698_parser *parser)
{
    struct DLT_698_REL_NTF *conn_ptr = NULL;
    dlt_698_take_apdu_info_head(parser, DLT_698_FRAME_TYPE_REL_NTY, 0, (void **)&conn_ptr);
    if (NULL == conn_ptr)
    {
        DLT_printf("take release notification data err.");
        return;
    }
    dlt_698_utl_print_data(parser, &conn_ptr->link_dt);
    dlt_698_utl_print_data(parser, &conn_ptr->cur_dt);
}