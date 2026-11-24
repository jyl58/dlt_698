cmake_minimum_required(VERSION 3.10)
project(dlt_698 VERSION 1.0.0 LANGUAGES C DESCRIPTION "DL/T 698 protocol parser library")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 许可证信息（MIT）
set(CMAKE_PROJECT_DESCRIPTION "DL/T 698 protocol parser library")
set(DLT_698_LICENSE "MIT")
set(DLT_698_LICENSE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

option(DLT_698_BUILD_DEMO "Build dlt_698 demo" ON)
option(DLT_698_BUILD_SHARED "Build shared library" ON)

add_compile_options(-Wall -Wextra -Wuninitialized)

# 头文件目录
set(DLT_698_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/interface
    ${CMAKE_CURRENT_SOURCE_DIR}/interface/parser
    ${CMAKE_CURRENT_SOURCE_DIR}/interface/utl
    ${CMAKE_CURRENT_SOURCE_DIR}/interface/version
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/mempool
    ${CMAKE_CURRENT_SOURCE_DIR}/src/parser
)

# 库源文件
file(GLOB_RECURSE DLT_698_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

if(DLT_698_BUILD_SHARED)
    add_library(dlt_698 SHARED ${DLT_698_SOURCES})
else()
    add_library(dlt_698 STATIC ${DLT_698_SOURCES})
endif()

target_include_directories(dlt_698 PUBLIC ${DLT_698_INCLUDE_DIRS})
set_target_properties(dlt_698 PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 1)

# 安装许可证
install(FILES ${DLT_698_LICENSE_FILE} DESTINATION share/dlt_698)

# demo
if(DLT_698_BUILD_DEMO)
    file(GLOB_RECURSE DEMO_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/demo/src/*.c)
    # 排除各demo入口, 入口在add_executable中单独指定
    list(REMOVE_ITEM DEMO_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/demo/src/server/main.c
        ${CMAKE_CURRENT_SOURCE_DIR}/demo/src/client/main.c)

    # server端测试demo: 解析client发来的请求帧
    add_executable(dlt_698_demo_server ${CMAKE_CURRENT_SOURCE_DIR}/demo/src/server/main.c ${DEMO_SOURCES})

    # client端测试demo: 组帧server返回的响应帧并解析
    add_executable(dlt_698_demo_client ${CMAKE_CURRENT_SOURCE_DIR}/demo/src/client/main.c ${DEMO_SOURCES})

    set(DEMO_INC_DIRS
        ${DLT_698_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/demo/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/demo/inc/client
        ${CMAKE_CURRENT_SOURCE_DIR}/demo/inc/server
        ${CMAKE_CURRENT_SOURCE_DIR}/demo/inc/encode
    )
    target_include_directories(dlt_698_demo_server PRIVATE ${DEMO_INC_DIRS})
    target_include_directories(dlt_698_demo_client PRIVATE ${DEMO_INC_DIRS})
    # demo内class生成的头文件目录
    file(GLOB_RECURSE DEMO_CLASS_DIRS LIST_DIRECTORIES true ${CMAKE_CURRENT_SOURCE_DIR}/demo/inc/class/*)
    foreach(DIR ${DEMO_CLASS_DIRS})
        if(IS_DIRECTORY ${DIR})
            target_include_directories(dlt_698_demo_server PRIVATE ${DIR})
            target_include_directories(dlt_698_demo_client PRIVATE ${DIR})
        endif()
    endforeach()

    target_link_libraries(dlt_698_demo_server PRIVATE dlt_698)
    target_link_libraries(dlt_698_demo_client PRIVATE dlt_698)
endif()
