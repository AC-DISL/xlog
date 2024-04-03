<!--
 * @Author: zhanghongzhi
 * @Date: 2024-04-02 18:34:57
 * @LastEditors: zhanghongzhi
 * @LastEditTime: 2024-04-02 19:30:38
 * @FilePath: /xlog/README.md
 * @Description: 
 * 
 * Copyright (c) 2024 by aircas, All Rights Reserved. 
-->
## Introduction
该库基于spdlog库封装，并且是线程安全的，日志级别分为trace, debug, info, warning, error, critical六种
打印日志到日志文件中，为滚动打印，日志文件大小最大为5M，最大文件数为3个，当日志文件超过5M时，将修改日志文件名为xxx.1.log, xxx.2.log, xxx.3.log

日志格式实例及说明：
[2024-04-02 19:35:18:332] [info] [75054:75054] [main.cc:31, main] start ground-end-server
[年-月-日 时:分:秒:毫秒] [日志级别] [进程ID:线程ID] [文件名:行号, 函数名] 日志内容

## How to use
1. 引用该库的进程，需在进程启动时main函数首先调用log_init初始化，参数为日志文件名，可指定绝对路径，如指定相对路径则为相对可执行文件的路径; 如参数为NULL则日志名默认为log.log
2. 日志库默认打印级别为info，如需修改日志级别，调用set_log_level，参数为LOG_LEVEL枚举类型
3. LOG_TRACE, ... , LOG_ERROR等为打印日志的宏，使用方法完全等同于printf
4. 如需在调试时将日志打印到控制台终端，可在编译时定义NOLOG宏，LOG_INFO等将被解释为printf，此时只需引用xlog.h头文件即可，不需要链接该库。在发布正式版本时，只需在编译文件中删除NOLOG宏，同时链接该库即可，不需要修改业务代码

## How to compile