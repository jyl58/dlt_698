/**
 * @file main.c
 * @date 2026-10-31
 * @brief DL/T 698 server端测试demo
 * @details 模拟server(表计/终端)侧: 解析client发来的SET请求帧,
 *          在回调中提取并打印帧头字段与APDU各字段。
 *          示例中直接喂入十六进制报文字节流，实际使用时可将
 *          串口/网络等通信接口收到的字节逐个送入 dlt_698_parse()。
 */
#include <stdio.h>
#include "dlt_698.h"
#include "dlt_698_test_server.h"
#include "dlt_698_test_client.h"
#include "dlt_698_test_encode.h"

/* 一帧完整的698报文（GET-Request normal 示例） */
static const char *frame_string =
    "68 25 00 43 05 01 00 00 00 00 00 00 4a de 06 01 01 00 00 01 00 09 02 00 "
    "00 01 07 e1 03 17 00 17 26 05 00 05 1c 82 16";

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    printf("parser version=%s\n", dlt_698_parser_version());

    uint8_t _frame_buf[4500] = {0};
    ///< 设置地址域信息
    char *addr = "010203040506";
    dlt_698_addr_t addr_info;
    dlt_698_addr_init(&addr_info, addr, 5, 160);

    dlt_698_parser dlt_698_parser_ins;
    // 初始化创建的698解析器
    if (dlt_698_parser_init(&dlt_698_parser_ins, addr_info, _frame_buf, sizeof(_frame_buf), dlt_698_utl_server_handler) < 0)
    {
        printf("parse init err. \n");
        return -1;
    }

    /* 将报文字符串转换为字节流 */
    unsigned char hexArr[4096] = {0};
    int hexLen = dlt_698_string_hex(frame_string, hexArr);
    printf("frame len=%d\n", hexLen);

    /* 逐字节送入解析器，解析完成后回调 dlt_698_utl_server_handler
     * 注意: DLT_698_ERR_PARSING(-1)表示帧接收中的正常中间态, 不算错误 */
    for (int i = 0; i < hexLen; i++)
    {
        if (dlt_698_parse(&dlt_698_parser_ins, hexArr[i]) < DLT_698_ERR_PARSING)
        {
            printf("parse err at byte %d. \n", i);
        }
    }

    printf("parse done. \n");
    return 0;
}