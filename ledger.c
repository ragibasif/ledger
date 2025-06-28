/*
 * File: ledger.c
 * Author: Ragib Asif
 * Email: ragib.asif30@myhunter.cuny.edu
 * GitHub: https://github.com/ragibasif
 * LinkedIn: https://www.linkedin.com/in/ragibasif/
 * SPDX-License-Identifier: MIT
 * Copyright (c) 2025 Ragib Asif
 * Version 1.0.0
 *
 * Compile the library with `-DL_COLOR` to print with ANSI color escape
 * codes. If a log file is specified, ANSI color escape will be disabled
 * regardless of the flag.
 *
 */

#include "ledger.h"
#include "shared.h"

static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;
static FILE *log_file = NULL;

static const char *level_strings[] = {
    [LT_INFO] = "[INFO]",
    [LT_DEBUG] = "[DEBUG]",
    [LT_WARN] = "[WARN]",
    [LT_ERROR] = "[ERROR]",
};

#ifdef L_COLOR
static const char *level_colors[] = {[LT_INFO] = AEC_GREEN,
                                     [LT_DEBUG] = AEC_CYAN,
                                     [LT_WARN] = AEC_YELLOW,
                                     [LT_ERROR] = AEC_RED};
#endif // L_COLOR

void l_init(const char *file) {
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

void l_fin(void) {
    pthread_mutex_lock(&log_mutex);
    if (log_file && log_file != stdout) {
        fclose(log_file);
        log_file = NULL;
    }
    pthread_mutex_unlock(&log_mutex);
}

void l_out(enum log_type level, const char *file, unsigned int line,
           const char *function, const char *format, ...) {

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

#ifdef L_COLOR
    if (log_file != stdout) {
        // do not output colors if logging to file
        fprintf(log_file, "%s [%s:%u (%s)] %s ", time_str, file, line, function,
                level_strings[level]);
    } else {
        fprintf(log_file, "%s%s [%s:%u (%s)]%s %s%s%s%s ", AEC_DIM, time_str,
                file, line, function, AEC_RESET, AEC_BOLD, level_colors[level],
                level_strings[level], AEC_RESET);
    }
#else
    fprintf(log_file, "%s [%s:%u (%s)] %s ", time_str, file, line, function,
            level_strings[level]);
#endif // L_COLOR

    va_list args;
    va_start(args, format);
    vfprintf(log_file, format, args);
    va_end(args);

    fprintf(log_file, "\n");
    fflush(log_file);

    pthread_mutex_unlock(&log_mutex);
}
