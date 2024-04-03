/*
 * @Author: zhanghongzhi
 * @Date: 2024-04-02 19:15:34
 * @LastEditors: zhanghongzhi
 * @LastEditTime: 2024-04-02 19:31:40
 * @FilePath: /xlog/test/test.cc
 * @Description:
 *
 * Copyright (c) 2024 by aircas, All Rights Reserved.
 */
#include "xlog/xlog.h"

int main() {
    xLogInit("test.log");
    int i = 0;
    LOG_DEBUG("test logfile, level=%s, id=%d", "debug", ++i);
    LOG_DEBUG("print debug log");
    LOG_INFO("test logfile, level=%s, id=%d", "info", ++i);
    LOG_INFO("print info log");
    LOG_WARN("test logfile, level=%s, id=%d", "warn", ++i);
    LOG_ERROR("test logfile, level=%s, id=%d", "error", ++i);
    return 0;
}