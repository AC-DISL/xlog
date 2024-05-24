/*
 * @Author: zhanghongzhi
 * @Date: 2024-04-02 18:34:41
 * @LastEditors: zhanghongzhi
 * @LastEditTime: 2024-05-24 16:53:23
 * @FilePath: /xlog/include/xlog/xlog.h
 * @Description:
 *
 * Copyright (c) 2024 by aircas, All Rights Reserved.
 */
#ifndef AURORAHD_UTILS_xlog_SPDLOG_H_H
#define AURORAHD_UTILS_xlog_SPDLOG_H_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

// clang-format off

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_LOG_SIZE 4096
#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1) : __FILE__)

enum LOG_LEVEL {
    level_trace = 0,
    level_debug = 1,
    level_info,
    level_warn,
    level_error,
    level_critical
};

#ifdef NO_LOG
#define LOG_TRACE(format, ...)    printf(format, ##__VA_ARGS__);printf("\n");
#define LOG_DEBUG(format, ...)    printf(format, ##__VA_ARGS__);printf("\n");
#define LOG_INFO(format, ...)     printf(format, ##__VA_ARGS__);printf("\n");
#define LOG_WARN(format, ...)     printf(format, ##__VA_ARGS__);printf("\n");
#define LOG_ERROR(format, ...)    printf(format, ##__VA_ARGS__);printf("\n");
#define LOG_CRITICAL(format, ...) printf(format, ##__VA_ARGS__);printf("\n");
void xLogInit(const char *path){}
void xLogLevelSet(LOG_LEVEL level){}
#else
#define LOG_TRACE(format, ...)    xLogWrite(level_trace, __LINE__, __FUNCTION__, __FILENAME__, format, ##__VA_ARGS__)
#define LOG_DEBUG(format, ...)    xLogWrite(level_debug, __LINE__, __FUNCTION__, __FILENAME__, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...)     xLogWrite(level_info, __LINE__, __FUNCTION__, __FILENAME__, format, ##__VA_ARGS__)
#define LOG_WARN(format, ...)     xLogWrite(level_warn, __LINE__, __FUNCTION__, __FILENAME__, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...)    xLogWrite(level_error, __LINE__, __FUNCTION__, __FILENAME__, format, ##__VA_ARGS__)
#define LOG_CRITICAL(format, ...) xLogWrite(level_critical, __LINE__, __FUNCTION__, __FILENAME__, format, ##__VA_ARGS__)
void xLogInit(const char *path);
void xLogLevelSet(LOG_LEVEL level);
void xLogWrite(int level, int line, const char *func, const char *file, const char *format, ...);
#endif

#ifdef __cplusplus
}
#endif

// clang-format on

#endif