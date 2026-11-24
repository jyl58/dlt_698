/**
 * @file main_get_res.c
 * @date 2026-11-24
 * @brief DL/T 698 client端测试demo
 * @details 模拟client(主站)侧: 组帧一帧 GetResponseNormal 报文
 *          (模拟server返回的响应), 逐字节送入解析器,
 *          解析完成后客户端回调内会提取并打印各字段值。
 */
#include <stdio.h>
#include "dlt_698.h"
#include "dlt_698_test_client.h"
#include "dlt_698_test_encode.h"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    printf("parser version=%s\n", dlt_698_parser_version());

    uint8_t _enc_buf[4500] = {0};
    char *addr = "010203040506";
    dlt_698_addr_t addr_info;
    dlt_698_addr_init(&addr_info, addr, 5, 160);

    /* 组帧GetResponseNormal APDU:
     * 85          : Get-Response
     * 01          : method(GetResponseNormal)
     * 01          : PIID
     * 00 01 00 00 : OAD(oi=0x0001, att_tag=0x00, att_index=0x00)
     * 01          : DataChoice=1, 后面跟数据
     * 06          : 数据类型 double-long-unsigned
     * 00 00 27 10 : 数据值 10000
     * 00          : FollowReportTag=无
     * 01          : TimeTag可选标志=有
     * 07 E1 03 17 00 17 26 : date_time_s 2017-03-23 00:17:26
     * 05 00 05    : TI(unit=5, interval=5) */
    uint8_t res_apdu[] = {0x85, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x01, 0x06, 0x00, 0x00, 0x27, 0x10,
                          0x00, 0x01, 0x07, 0xE1, 0x03, 0x17, 0x00, 0x17, 0x26, 0x05, 0x00, 0x05};
    uint8_t res_frame[128] = {0};
    dlt_698_parser enc_parser;
    if (dlt_698_parser_init(&enc_parser, addr_info, _enc_buf, sizeof(_enc_buf), NULL) < 0)
    {
        printf("encode parser init err. \n");
        return -1;
    }
    int32_t res_len = dlt_698_encode(&enc_parser, DLT_698_FROM_SERVER | RM_698_FRAME_FUN_3,
                                     res_apdu, sizeof(res_apdu), res_frame, sizeof(res_frame));
    if (res_len < 0)
    {
        printf("encode err. \n");
        return -1;
    }
    printf("GET-Response frame(%d bytes):", res_len);
    for (int32_t i = 0; i < res_len; i++)
    {
        printf(" %02X", res_frame[i]);
    }
    printf("\n");

    /* 逐字节送入解析器, 解析完成后回调 dlt_698_utl_client_handler */
    uint8_t _res_buf[4500] = {0};
    dlt_698_parser res_parser;
    if (dlt_698_parser_init(&res_parser, addr_info, _res_buf, sizeof(_res_buf), dlt_698_utl_client_handler) < 0)
    {
        printf("response parser init err. \n");
        return -1;
    }
    /* 注意: DLT_698_ERR_PARSING(-1)表示帧接收中的正常中间态, 不算错误 */
    for (int i = 0; i < res_len; i++)
    {
        if (dlt_698_parse(&res_parser, res_frame[i]) < DLT_698_ERR_PARSING)
        {
            printf("parse err at byte %d. \n", i);
        }
    }

    printf("parse done. \n");
    return 0;
}