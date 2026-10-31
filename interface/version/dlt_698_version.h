/**
 * @file dlt_698_version.h
 * @brief 此文件为698协议解析器版本号定义的头文件，定义了获取版本信息接口
 * @date 2026/5/20
 */
#ifndef DLT_698_VERSION_H_
#define DLT_698_VERSION_H_
#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief 获取698协议解析器版本号
     * @return 版本号字符串指针，例如"1.0.0"
     */
    const char *dlt_698_get_version(void);
#ifdef __cplusplus
}
#endif
#endif