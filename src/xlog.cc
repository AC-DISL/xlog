#include "xlog/xlog.h"

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/spdlog.h>
#include <unistd.h>

#include <chrono>
#include <iostream>
#include <mutex>
#include <string>

class LogAssit {
public:
    static LogAssit &GetInstance() {
        static LogAssit log_assit;
        return log_assit;
    }

private:
    LogAssit() {
        log_str_ = (char *)malloc(MAX_LOG_SIZE);
        buf_     = (char *)malloc(MAX_LOG_SIZE);
    }
    ~LogAssit() {
        spdlog::drop_all();
        free(log_str_);
        free(buf_);
    }

public:
    char *log_str_;
    char *buf_;
    LOG_LEVEL log_level_;
    std::shared_ptr<spdlog::logger> logger_;
    std::mutex mutex_;
};

void xLogInit(const char *path) {
    std::string filepath;

    if (nullptr == path) {
        filepath = "log.log";
    } else {
        filepath = path;
    }
    LogAssit::GetInstance().logger_ =
        spdlog::rotating_logger_mt("file_logger", filepath, 1024 * 1024 * 5, 3);
    LogAssit::GetInstance().logger_->set_pattern(
        "[%Y-%m-%d %H:%M:%S:%e] [%l] [%P:%t] %v");
    xLogLevelSet(level_info);
}

void xLogLevelSet(LOG_LEVEL level) {
    auto set_level = [](spdlog::level::level_enum loglevel) {
        spdlog::set_level(loglevel);
        LogAssit::GetInstance().logger_->flush_on(loglevel);
    };

    LogAssit::GetInstance().log_level_ = level;
    switch (level) {
    case level_trace:
        set_level(spdlog::level::trace);
        break;
    case level_debug:
        set_level(spdlog::level::debug);
        break;
    case level_info:
        set_level(spdlog::level::info);
        break;
    case level_warn:
        set_level(spdlog::level::warn);
        break;
    case level_error:
        set_level(spdlog::level::err);
        break;
    case level_critical:
        set_level(spdlog::level::critical);
        break;
    default:
        break;
    }
}

void xLogWrite(int level, int line, const char *func, const char *file,
    const char *format, ...) {
    if (level < LogAssit::GetInstance().log_level_) {
        return;
    }
    std::lock_guard<std::mutex> lck(LogAssit::GetInstance().mutex_);
    LogAssit &log_assit = LogAssit::GetInstance();
    va_list ap;
    va_start(ap, format);
    int count_write = vsnprintf(NULL, 0, format, ap);
    va_end(ap);
    if (0 >= count_write) {
        return;
    }
    ++count_write;

    // get format content to buf_
    va_start(ap, format);
    memset(log_assit.buf_, 0, count_write);
    vsnprintf(log_assit.buf_, count_write, format, ap);
    va_end(ap);

    // generate log content
    memset(log_assit.log_str_, 0, MAX_LOG_SIZE);
    sprintf(
        log_assit.log_str_, "[%s:%d, %s] %s", file, line, func, log_assit.buf_);
    log_assit.log_str_[MAX_LOG_SIZE - 1] = 0;

    // write log
    switch (level) {
    case level_trace:
        log_assit.logger_->trace(log_assit.log_str_);
        break;
    case level_debug:
        log_assit.logger_->debug(log_assit.log_str_);
        break;
    case level_info:
        log_assit.logger_->info(log_assit.log_str_);
        break;
    case level_warn:
        log_assit.logger_->warn(log_assit.log_str_);
        break;
    case level_error:
        log_assit.logger_->error(log_assit.log_str_);
        break;
    case level_critical:
        log_assit.logger_->critical(log_assit.log_str_);
        break;
    default:
        break;
    }
}