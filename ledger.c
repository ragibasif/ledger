/*
 * File: ledger.c
 * Author: Ragib Asif
 * Email: 182296466+ragibasif@users.noreply.github.com
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 *
 */

#include "ledger.h"

static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;
static FILE *log_file = NULL;

static const char *level_literal[] = {
    [LL_OFF] = "OFF",     [LL_FATAL] = "FATAL", [LL_ERROR] = "ERROR",
    [LL_WARN] = "WARN",   [LL_INFO] = "INFO",   [LL_DEBUG] = "DEBUG",
    [LL_TRACE] = "TRACE", [LL_ALL] = "ALL",
};

void l_create(const char *file) {
    pthread_mutex_lock(&log_mutex);
    if (file) {
        log_file = fopen(file, "a");
        if (!log_file) {
            fprintf(stderr, "Failed to open log file: %s\n", file);
            pthread_mutex_unlock(&log_mutex);
            exit(EXIT_FAILURE);
        }
    } else {
        log_file = stdout; // default to standard output
    }
    pthread_mutex_unlock(&log_mutex);
}

void l_destroy(void) {
    pthread_mutex_lock(&log_mutex);
    if (log_file && log_file != stdout) {
        fclose(log_file);
        log_file = NULL;
    }
    pthread_mutex_unlock(&log_mutex);
}

void l_log(const enum log_level level, const char *file,
           const unsigned int line, const char *func, const char *fmt, ...) {

    if (!log_file) {
        fprintf(stderr, "Logging not initialized.\n");
        pthread_mutex_unlock(&log_mutex);
        return;
    }

    pthread_mutex_lock(&log_mutex);

    time_t now;
    char *time_str;
    now = time(NULL);
    time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0';

    fprintf(log_file, "%s [%s:%u (%s)] %s ", time_str, file, line, func,
            level_literal[level]);

    va_list args;
    va_start(args, fmt);
    vfprintf(log_file, fmt, args);
    va_end(args);

    fprintf(log_file, "\n");
    fflush(log_file);

    pthread_mutex_unlock(&log_mutex);
}
