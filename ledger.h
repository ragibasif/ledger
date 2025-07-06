/*
 * File: ledger.h
 * Author: Ragib Asif
 * Email: 182296466+ragibasif@users.noreply.github.com
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 *
 * Minimal logging library.
 *
 */

#ifndef LEDGER_H_
#define LEDGER_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "common.h"

enum log_level {
    LL_OFF = 0,   // no events will be logged
    LL_FATAL = 1, // non-recoverable, will crash whole application
    LL_ERROR = 2, // recoverable error
    LL_WARN = 3,  // possibly will lead to an error/fatal
    LL_INFO = 4,  // informational log event
    LL_DEBUG = 5, // debugging log
    LL_TRACE = 6, // for very fine grained tracing
    LL_ALL = 7,   // log all events
    LL_COUNT = 8  // count of log levels
};

struct log_event {
    enum log_level level;
    char *file;
    unsigned int line;
    char *func;
    char *fmt;
};

extern void l_create(const char *file);
extern void l_destroy(void);
extern void l_print(const enum log_level level, const char *file,
                    const unsigned int line, const char *func, const char *fmt,
                    ...);

#define FATAL(fmt, ...)                                                        \
    l_print(LL_FATAL, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define ERROR(fmt, ...)                                                        \
    l_print(LL_ERROR, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define WARN(fmt, ...)                                                         \
    l_print(LL_WARN, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define INFO(fmt, ...)                                                         \
    l_print(LL_INFO, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...)                                                        \
    l_print(LL_DEBUG, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)
#define TRACE(fmt, ...)                                                        \
    l_print(LL_TRACE, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // LEDGER_H_
