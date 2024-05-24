/*
 * @Author: zhanghongzhi
 * @Date: 2024-05-24 16:46:51
 * @LastEditors: zhanghongzhi
 * @LastEditTime: 2024-05-24 16:53:39
 * @FilePath: /xlog/test/nolog.cc
 * @Description:
 *
 * Copyright (c) 2024 by aircas, All Rights Reserved.
 */
#include <xlog/xlog.h>

int main() {
    xLogInit("log.log");
    xLogLevelSet(level_info);
    LOG_INFO("info");
    LOG_WARN("warn");
}