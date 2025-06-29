/*
 * File: log.h
 * Author: Ragib Asif
 * Email: ragib.asif30@myhunter.cuny.edu
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

enum log_type {
    LT_INFO = 0,
    LT_DEBUG = 1,
    LT_WARN = 3,
    LT_ERROR = 4,
};

extern void l_init(const char *file);
extern void l_fin(void);
extern void l_out(enum log_type level, const char *file, unsigned int line,
                  const char *function, const char *format, ...);

#define INFO(format, ...)                                                      \
    l_out(LT_INFO, __FILE__, __LINE__, __func__, format, ##__VA_ARGS__)
#define DEBUG(format, ...)                                                     \
    l_out(LT_DEBUG, __FILE__, __LINE__, __func__, format, ##__VA_ARGS__)
#define WARN(format, ...)                                                      \
    l_out(LT_WARN, __FILE__, __LINE__, __func__, format, ##__VA_ARGS__)
#define ERROR(format, ...)                                                     \
    l_out(LT_ERROR, __FILE__, __LINE__, __func__, format, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // LEDGER_H_
