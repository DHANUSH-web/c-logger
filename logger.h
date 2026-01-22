/*
 *  ************************************************************************
 *  Copyright (c) 2025, Dhanush H V. All rights reserved.
 *  Licensed under the MIT License. See the LICENSE file for more details
 *  *************************************************************************
 */

#pragma once
#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Handle file system based on platform
#ifdef _WIN32
#include <direct.h>
#define MKDIR(path) _mkdir(path)
#else
#include <sys/stat.h>
#define MKDIR(path) mkdir(path, 0777)
#endif

// Define boolean types
typedef enum {
    FALSE = 0,
    TRUE = 1,
} BOOL;

// Define colors for logger with respect to log level
#define RED         "\033[0;31m"
#define GREEN       "\033[0;32m"
#define YELLOW      "\033[0;33m"
#define ORANGE      "\033[0;93m"
#define BLUE        "\033[0;34m"
#define MAGENTA     "\033[0;35m"
#define CYAN        "\033[0;36m"
#define WHITE       "\033[0;37m"
#define RESET       "\033[0m"

// Define different text styles
#define BOLD        "\033[1m"
#define UNDERLINE   "\033[4m"
#define BLINK       "\033[5m"
#define REVERSE     "\033[7m"
#define HIDDEN      "\033[8m"

// Define log levels
// #define DEBUG       "DEBUG"
// #define INFO        "INFO"
// #define WARNING     "WARNING"
// #define ERROR       "ERROR"
// #define FATAL       "FATAL"
// #define MESSAGE     "MESSAGE"
// #define UNKNOWN     "UNKNOWN"

// different log levels
enum LEVEL {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL,
    MESSAGE,
    UNKNOWN,
};

// Define a level handler struct
struct LVL_HANDLER {
    enum LEVEL  level;
    char*       color;
    int         count;
};

// create logger instance
struct LOGGER {
    const char*         name;
    const char*         root_dir;
    const char*         file_name;
    FILE*               file;
    time_t              start_time;
    time_t              end_time;
    time_t              cur_time;
    int                 log_count;
    BOOL                debug;
    struct LVL_HANDLER  level[7];
};

// Declare all the methods of logger
static inline struct LOGGER INIT_LOGGER(const char* name, const char* root_dir, const char* file_name, BOOL debug);
static inline BOOL     IS_LOGGER_ACTIVE(const struct LOGGER* logger);
static inline void     LOG(struct LOGGER* logger, const char* message, enum LEVEL level, BOOL debug_once);
static inline void     PRINT_LOG(const char* message, enum LEVEL level);
static inline void     PRINT_LOG_WITH_TIME(const char* message, enum LEVEL level, const char* time_buf);
static inline int      GET_LOGGER_LOG_COUNT(const struct LOGGER* logger);
static inline int      GET_LOGGER_LEVEL_COUNT(const struct LOGGER* logger, enum LEVEL level);
static inline char*    GET_LOGGER_LEVEL_STRING(enum LEVEL level);
static inline void     DISPLAY_LOGGER_LEVELS(const struct LOGGER* logger);
static inline time_t   GET_LOGGER_START_TIME(const struct LOGGER* logger);
static inline time_t   GET_LOGGER_END_TIME(const struct LOGGER* logger);
static inline void     EXIT_LOGGER(struct LOGGER* logger);
static inline void     GET_CURRENT_DATE_TIME(char* buf, size_t size);
static inline void     REGISTER_LOGGER(const struct LOGGER* logger);
static inline void     UNREGISTER_LOGGER(const struct LOGGER* logger);
static inline void     UNREGISTER_ALL_LOGGERS();
static inline BOOL     IS_LOGGER_REGISTERED(const struct LOGGER* logger);

// Logger buffer manager
static struct   LOGGER BUFFERS[100];
static int      BUFFER_COUNT;
static int      BUFFER_SIZE;

// Define a logger instance
static inline struct LOGGER INIT_LOGGER(const char* name, const char* root_dir, const char* file_name, const BOOL debug) {
    // Get the absolute path of logger
    char log_file[4096] = "";
    snprintf(log_file, sizeof(log_file), "%s/%s", root_dir, file_name);

    // create the root directory
    MKDIR(root_dir);

    const struct LOGGER logger = {
        .name       = name,
        .root_dir   = root_dir,
        .file_name  = file_name,
        .start_time = time(NULL),
        .end_time   = time(NULL),
        .cur_time   = time(NULL),
        .log_count  = 0,
        .level      = {
            {DEBUG,   GREEN,  0},
            {INFO,    CYAN,   0},
            {WARNING, YELLOW, 0},
            {ERROR,   ORANGE, 0},
            {FATAL,   RED,    0},
            {MESSAGE, BLUE,   0},
            {UNKNOWN, WHITE,  0},
        },
        .file   = fopen(log_file, "w+"),
        .debug  = debug,
    };

    if (logger.file == NULL) {
        PRINT_LOG("Failed to open log file", FATAL);
        exit(EXIT_FAILURE); // exit logger if failed to create logger file
    }

    char time_buf[100];
    GET_CURRENT_DATE_TIME(time_buf, sizeof(time_buf));

    fprintf(logger.file, ">>> Logger %s initiated at %s <<<\n", name, time_buf);
    printf("%s>>> Logger %s initiated at %s <<< %s\n", CYAN, name, time_buf, RESET);

    // Register the logger to BUF_MANAGER
    REGISTER_LOGGER(&logger);
    return logger;
};

// Check if the logger is active
static inline BOOL IS_LOGGER_ACTIVE(const struct LOGGER* logger) {
    return logger != NULL && logger->file != NULL;
}

// Log method to save and print the log
static inline void LOG(struct LOGGER* logger, const char* message, const enum LEVEL level, const BOOL debug_once) {
    if (!IS_LOGGER_ACTIVE(logger)) {
        PRINT_LOG("FAILED: No active logger is running, please initiate logger", ERROR);
        exit(EXIT_FAILURE);
    }

    char time_buf[100];
    GET_CURRENT_DATE_TIME(time_buf, sizeof(time_buf));

    if (logger->debug || debug_once) {
        PRINT_LOG_WITH_TIME(message, level, time_buf);
    }

    fprintf(logger->file, "%s %s %s\n", time_buf, GET_LOGGER_LEVEL_STRING(level), message);

    // Update log counters
    logger->log_count++;
    logger->level[level].count++;
}

// Print the log to console with colored text
static inline void PRINT_LOG(const char* message, const enum LEVEL level) {
    char time_buf[100];
    GET_CURRENT_DATE_TIME(time_buf, sizeof(time_buf));
    PRINT_LOG_WITH_TIME(message, level, time_buf);
}

// Print the log to console with provided time string
static inline void PRINT_LOG_WITH_TIME(const char* message, const enum LEVEL level, const char* time_buf) {
    const char* color = NULL;

    switch (level) {
        case DEBUG:   color = GREEN;  break;
        case INFO:    color = CYAN;   break;
        case WARNING: color = YELLOW; break;
        case ERROR:   color = ORANGE; break;
        case FATAL:   color = RED;    break;
        case MESSAGE: color = BLUE;   break;
        default:      color = WHITE;  break;
    }

    printf("%s%s %s %s%s\n", color, time_buf, GET_LOGGER_LEVEL_STRING(level), message, RESET);
}

// Get the total logs count
static inline int GET_LOGGER_LOG_COUNT(const struct LOGGER* logger) {
    return logger->log_count;
}

// Get the total specific level count
static inline int GET_LOGGER_LEVEL_COUNT(const struct LOGGER* logger, const enum LEVEL level) {
    return logger->level[level].count;
}

// Get the specific level in string
static inline char* GET_LOGGER_LEVEL_STRING(const enum LEVEL level) {
    switch (level) {
        case DEBUG:
            return "DEBUG";
        case INFO:
            return "INFO";
        case WARNING:
            return "WARNING";
        case ERROR:
            return "ERROR";
        case FATAL:
            return "FATAL";
        case MESSAGE:
            return "MESSAGE";
        default:
            return "UNKNOWN";
    }
}

// Display available log levels
static inline void DISPLAY_LOGGER_LEVELS(const struct LOGGER* logger) {
    for (int i = 0; i < 7; i++) {
        printf("%s%s%s\n", logger->level[i].color, GET_LOGGER_LEVEL_STRING(logger->level[i].level), RESET);
    }
}

// Get the logger starting time
static inline time_t GET_LOGGER_START_TIME(const struct LOGGER* logger) {
    return logger->start_time;
}

// Get the logger exit time
static inline time_t GET_LOGGER_END_TIME(const struct LOGGER* logger) {
    if (IS_LOGGER_ACTIVE(logger))
        return logger->end_time;
    return time(NULL);
}

// exit the logger
static inline void EXIT_LOGGER(struct LOGGER* logger) {
    if (IS_LOGGER_ACTIVE(logger)) {
        char time_buf[100];
        GET_CURRENT_DATE_TIME(time_buf, sizeof(time_buf));

        logger->end_time = time(NULL);
        fprintf(logger->file, ">>> Logger %s exited at %s <<<\n", logger->name, time_buf);
        printf("%s>>> Logger %s exited at %s <<<%s\n", CYAN, logger->name, time_buf, RESET);
        UNREGISTER_LOGGER(logger);      // unregister logger from buffer manager
        fclose(logger->file);
        logger->file = NULL;
    } else {
        printf("%s>>> Logger %s not initialized <<<%s\n", RED, logger->name, RESET);
    }
}

// Get the current date and time
static inline void GET_CURRENT_DATE_TIME(char* buf, size_t size) {
    time_t current_time;

    time(&current_time);
    const struct tm *local_time = localtime(&current_time);
    strftime(buf, size, "%d-%m-%Y %H:%M:%S", local_time);
}

// Check if the logger has already registered to the register
static inline BOOL IS_LOGGER_REGISTERED(const struct LOGGER* logger) {
    for (int i = 0; i < BUFFER_COUNT; i++)
        if (BUFFERS[i].file_name != NULL && strcmp(BUFFERS[i].file_name, logger->file_name) == 0) {
            return TRUE;
        }

    return FALSE;
}

// Register the Logger buffer
static inline void REGISTER_LOGGER(const struct LOGGER* logger) {
    // check if the buffer already exists in the register
    if (!IS_LOGGER_REGISTERED(logger)) {
        BUFFERS[BUFFER_COUNT++] = *logger;
        BUFFER_SIZE++;
        PRINT_LOG("[BUF_MANAGER]: Logger has been registered to BUF_MANAGER", DEBUG);
        return;
    }

    PRINT_LOG("[BUF_MANAGER]: Logger is already registered with BUF_MANAGER", ERROR);
}

// Unregister the logger from buffer manager
static inline void UNREGISTER_LOGGER(const struct LOGGER* logger) {
    // figure out the position of the logger to be removed
    int position = -1;

    for (int i = 0; i < BUFFER_COUNT; i++) {
        if (BUFFERS[i].file_name != NULL && strcmp(BUFFERS[i].file_name, logger->file_name) == 0) {
            position = i;
            break;
        }
    }

    if (position == -1) {
        PRINT_LOG("[BUF_MANAGER]: Failed to unregister the logger, could not be found in the existing register", ERROR);
        return;
    }

    // unregister the logger by shifting elements
    for (int i = position; i < BUFFER_COUNT - 1; i++) {
        BUFFERS[i] = BUFFERS[i + 1];
    }
    BUFFER_COUNT--;
    BUFFER_SIZE--;
    PRINT_LOG("[BUF_MANAGER]: Logger was unregistered successfully", DEBUG);
}

// Unregister all the running loggers
static inline void UNREGISTER_ALL_LOGGERS() {
    while (BUFFER_COUNT > 0) {
        EXIT_LOGGER(&BUFFERS[0]);
    }
}

#endif //LOGGER_H
