# dlt_698 — DL/T 698 报文解析库

一个独立、轻量的 **DL/T 698（面向对象的用电信息数据交换协议）报文解析与组帧库**，使用 C11 编写，仅依赖 C 标准库，可移植到 Linux、RTOS 及各类嵌入式平台。

- **许可证**：MIT（见 [LICENSE](LICENSE)）
- **语言标准**：C11
- **外部依赖**：无（仅 libc / libm）

## 功能特性

- **逐字节流式解析**：`dlt_698_parse()` 逐字节喂入，内置状态机自动完成帧头同步、帧头校验（HCS）、帧校验（FCS）验证
- **全类型帧支持**：LINK / CONNECT / RELEASE / GET / SET / ACTION / REPORT / SECURITY 请求与响应
- **安全传输（SEC）支持**：明文 APDU 内嵌套解析，带递归深度保护
- **内置内存池**：解析结果采用 bump-allocator 风格内存池存储，复用接收缓冲区空间，零动态内存申请、无碎片
- **组帧编码**：`dlt_698_encode()` 自动添加前导符、帧头、地址域、HCS/FCS 校验
- **数据取值工具**：解析结果以索引式链表组织，提供 `dlt_698_get_*` 系列接口按类型取值

## 目录结构

```
dlt_698/
├── CMakeLists.txt          # 工程构建配置
├── LICENSE                 # MIT 许可证
├── interface/              # 对外接口头文件
│   ├── dlt_type.h          #   基础类型与通用宏
│   ├── dlt_698_cfg.h       #   编译期配置（解析器实例数等）
│   ├── dlt_system_utl.h    #   系统时间戳接口（移植点）
│   ├── dlt_698.h           #   总入口头文件
│   ├── parser/             #   解析器接口（GET/SET/ACTION/REPORT...）
│   ├── utl/                #   取值/打印/工具接口
│   └── version/            #   版本接口
├── src/                    # 库实现（生成 libdlt_698）
│   ├── parser/             #   状态机与各帧类型解析
│   ├── encoder/            #   组帧编码
│   ├── mempool/            #   解析结果内存池
│   ├── utl/                #   工具实现
│   ├── dlt_system_utl.c    #   时间戳默认实现（POSIX时钟）
│   └── version/
└── demo/                   # 报文解析示例（生成 dlt_698_demo）
    ├── main.c              #   示例入口：喂入一帧完整报文
    ├── inc/                #   示例用头文件（含 class 数据模型）
    └── src/                #   服务端/客户端处理回调示例
```

## 编译方法

### Linux 编译

```bash
cd dlt_698
mkdir -p build && cd build
cmake ..
make -j4
```

编译产物：

| 产物 | 说明 |
|---|---|
| `libdlt_698.so.1.0.0` | 动态库（默认） |
| `dlt_698_demo` | 报文解析示例程序 |

### 编译选项

| CMake 选项 | 默认 | 说明 |
|---|---|---|
| `DLT_698_BUILD_DEMO` | `ON` | 是否编译 demo |
| `DLT_698_BUILD_SHARED` | `ON` | `ON` 编译动态库，`OFF` 编译静态库 |
| `CMAKE_BUILD_TYPE` | `Release` | 编译类型 |

示例：编译静态库、不编译 demo：

```bash
cmake -DDLT_698_BUILD_SHARED=OFF -DDLT_698_BUILD_DEMO=OFF ..
```

### 安装

```bash
make install
```

安装内容包括头文件、库文件及 LICENSE（许可证安装至 `share/dlt_698/`）。

### 运行 demo

```bash
./dlt_698_demo
```

demo 会解析一帧内置的 GET/SET 报文，输出帧信息、数据内容及内存池使用情况。

## 快速上手

```c
#include "dlt_698.h"

/* 1. 准备接收缓冲区（帧数据 + 解析结果共用） */
uint8_t frame_buf[4500];

/* 2. 配置本机地址 */
dlt_698_addr_t addr;
dlt_698_addr_init(&addr, "010203040506", 5, 160);

/* 3. 初始化解析器，注册解析完成回调 */
dlt_698_parser parser;
dlt_698_parser_init(&parser, addr, frame_buf, sizeof(frame_buf), my_handler);

/* 4. 从串口/网络等收到字节后逐字节喂入 */
for (int i = 0; i < len; i++) {
    dlt_698_parse(&parser, data[i]);  /* 解析完成时自动回调 my_handler */
}
```

> 注意：`dlt_698_parse()` 在帧未接收完整时返回负值（`DLT_698_ERR_PARSING`），属正常中间状态，无需当作错误处理。

## 配置说明

编辑 `interface/dlt_698_cfg.h`：

| 宏 | 默认值 | 说明 |
|---|---|---|
| `DLT_698_PARSER_MAX_COUNT` | `4` | 解析器实例最大个数 |

## 移植说明

库对平台的依赖已收敛到一处：

- **`src/dlt_system_utl.c`**：`dlt_sys_start_timestamp_ms()` 用于接收超时判断，默认基于 POSIX `clock_gettime(CLOCK_MONOTONIC)` 实现。移植到 RTOS 或其他平台时，替换该函数实现即可。

## 版本

当前版本：`1.0.0`，可通过 `dlt_698_get_version()` 获取。
