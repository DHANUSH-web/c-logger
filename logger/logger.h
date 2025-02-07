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
#include <sys/stat.h>
#include <time.h>

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
static struct   LOGGER INIT_LOGGER(const char* root_dir, const char* file_name, BOOL debug);
static BOOL     IS_LOGGER_ACTIVE(struct LOGGER logger);
static void     LOG(struct LOGGER logger, const char* message, enum LEVEL level, BOOL debug_once);
static void     PRINT_LOG(const char* message, enum LEVEL level);
static int      GET_LOGGER_LOG_COUNT(struct LOGGER logger);
static int      GET_LOGGER_LEVEL_COUNT(struct LOGGER logger, enum LEVEL level);
static char*    GET_LOGGER_LEVEL_STRING(enum LEVEL level);
static void     DISPLAY_LOGGER_LEVELS(struct LOGGER logger);
static time_t   GET_LOGGER_START_TIME(struct LOGGER logger);
static time_t   GET_LOGGER_END_TIME(struct LOGGER logger);
static void     EXIT_LOGGER(struct LOGGER logger);
static char*    GET_CURRENT_DATE_TIME();
static void     REGISTER_LOGGER(struct LOGGER logger);
static void     UNREGISTER_LOGGER(struct LOGGER logger);
static void     UNREGISTER_ALL_LOGGERS();
static BOOL     IS_LOGGER_REGISTERED(struct LOGGER logger);

// Logger buffer manager
static struct   LOGGER BUFFERS[sizeof(struct LOGGER) * 100];
static int      BUFFER_COUNT;
static int      BUFFER_SIZE;

// Define a logger instance
static struct LOGGER INIT_LOGGER(const char* root_dir, const char* file_name, const BOOL debug) {
    // Get the absolute path of logger
    char log_file[100] = "";
    strcat(log_file, root_dir);

    if (root_dir[strlen(root_dir) - 1] != '\\' || root_dir[strlen(root_dir) - 1] != '/') {
        strcat(log_file, "/");
    }

    strcat(log_file, file_name);

    // create the root directory
    mkdir(root_dir);

    const struct LOGGER logger = {
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

    // update the logger initialization time
    ctime(&logger.start_time);

    fprintf(logger.file, ">>> Logger initiated at %s <<<\n", GET_CURRENT_DATE_TIME());
    printf("%s>>> Logger initiated at %s <<< %s\n", CYAN, GET_CURRENT_DATE_TIME(), RESET);

    // Register the logger to BUF_MANAGER
    REGISTER_LOGGER(logger);
    return logger;
};

// Check if the logger is active
static BOOL IS_LOGGER_ACTIVE(const struct LOGGER logger) {
    return logger.file != NULL;
}

// Log method to save and print the log
static void LOG(const struct LOGGER logger, const char* message, const enum LEVEL level, const BOOL debug_once) {
    if (!IS_LOGGER_ACTIVE(logger)) {
        PRINT_LOG("FAILED: No active logger is running, please initiate logger", ERROR);
        exit(EXIT_FAILURE);
    }

    if (logger.debug || debug_once) {
        PRINT_LOG(message, level);
    }

    fprintf(logger.file, "%s %s %s\n", GET_CURRENT_DATE_TIME(), GET_LOGGER_LEVEL_STRING(level), message);
}

// Print the log to console with colored text
static void PRINT_LOG(const char* message, const enum LEVEL level) {
    const char* color = NULL;

    switch (level) {
        case DEBUG:
            color = GREEN;
            break;
        case INFO:
            color = CYAN;
            break;
        case WARNING:
            color = YELLOW;
            break;
        case ERROR:
            color = ORANGE;
            break;
        case FATAL:
            color = RED;
            break;
        case MESSAGE:
            color = BLUE;
            break;
        default:
            color = WHITE;
            break;
    }

    printf("%s%s %s %s%s\n", color, GET_CURRENT_DATE_TIME(), GET_LOGGER_LEVEL_STRING(level), message, RESET);
}

// Get the total logs count
static int GET_LOGGER_LOG_COUNT(const struct LOGGER logger) {
    return logger.log_count;
}

// Get the total specific level count
static int GET_LOGGER_LEVEL_COUNT(const struct LOGGER logger, const enum LEVEL level) {
    return logger.level[level].count;
}

// Get the specific level in string
static char* GET_LOGGER_LEVEL_STRING(const enum LEVEL level) {
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
static void DISPLAY_LOGGER_LEVELS(const struct LOGGER logger) {
    for (int i = 0; i < 7; i++) {
        printf("%s%s%s\n", logger.level[i].color, GET_LOGGER_LEVEL_STRING(logger.level[i].level), RESET);
    }
}

// Get the logger starting time
static time_t GET_LOGGER_START_TIME(const struct LOGGER logger) {
    return logger.start_time;
}

// Get the logger exit time
static time_t GET_LOGGER_END_TIME(const struct LOGGER logger) {
    if (IS_LOGGER_ACTIVE(logger))
        return logger.end_time;
    return time(NULL);
}

// exit the logger
static void EXIT_LOGGER(struct LOGGER logger) {
    if (IS_LOGGER_ACTIVE(logger)) {
        ctime(&logger.end_time);
        fprintf(logger.file, ">>> Logger exited at %s <<<\n", GET_CURRENT_DATE_TIME());
        printf("%s>>> Logger exited at %s <<<%s\n", CYAN, GET_CURRENT_DATE_TIME(), RESET);
        UNREGISTER_LOGGER(logger);      // unregister logger from buffer manager
        fclose(logger.file);
        logger.file = NULL;
    } else {
        printf("%s>>> Logger not initialized <<<%s\n", RED, RESET);
    }
}

// Get the current date and time
static char* GET_CURRENT_DATE_TIME() {
    char* buf = (char*)malloc(sizeof(char) + 100);
    time_t current_time;

    time(&current_time);
    const struct tm *local_time = localtime(&current_time);
    strftime(buf, 100, "%d-%m-%Y %H:%M:%S", local_time);

    return buf;
}

// Check if the logger has already registered to the register
static BOOL IS_LOGGER_REGISTERED(const struct LOGGER logger) {
    for (int i = 0; i < BUFFER_COUNT / 2; i++)
        if ((BUFFERS[i].file_name != NULL && strcmp(BUFFERS[i].file_name, logger.file_name) == 0) ||
            (BUFFERS[BUFFER_COUNT-i-1].file_name != NULL && strcmp(BUFFERS[BUFFER_COUNT-i-1].file_name, logger.file_name) == 0)) {
            return TRUE;
        }

    return FALSE;
}

// Register the Logger buffer
static void REGISTER_LOGGER(const struct LOGGER logger) {
    // check if the buffer already exists in the register
    if (!IS_LOGGER_REGISTERED(logger)) {
        BUFFERS[BUFFER_COUNT++] = logger;
        BUFFER_SIZE++;
        PRINT_LOG("[BUF_MANAGER]: Logger has been registered to BUF_MANAGER", DEBUG);
        return;
    }

    PRINT_LOG("[BUF_MANAGER]: Logger is already registered with BUF_MANAGER", ERROR);
}

// Unregister the logger from buffer manager
static void UNREGISTER_LOGGER(const struct LOGGER logger) {
    // figure out the position of the logger to be removed
    int position = -1;

    // Avoid looping if the only one logger is registered
    if (BUFFER_COUNT == 1 && strcmp(BUFFERS[0].file_name, logger.file_name) == 0) {
        BUFFERS[0].file_name = NULL;
        BUFFER_SIZE--;
        PRINT_LOG("[BUF_MANAGER]: Logger was unregistered successfully", DEBUG);
        return;
    }

    for (int i = 0; i <= BUFFER_COUNT / 2; i++) {
        if (BUFFERS[i].file_name != NULL && strcmp(BUFFERS[i].file_name, logger.file_name) == 0) {
            position = i;
            break;
        }

        if (BUFFERS[BUFFER_COUNT-i-1].file_name != NULL && strcmp(BUFFERS[BUFFER_COUNT-i-1].file_name, logger.file_name) == 0) {
            position = BUFFER_COUNT-i-1;
            break;
        }
    }

    if (position == -1) {
        PRINT_LOG("[BUF_MANAGER]: Failed to unregister the logger, could not be found in the existing register", ERROR);
        return;
    }

    // unregister the logger
    BUFFERS[position].file_name = NULL;
    BUFFER_SIZE--;
    PRINT_LOG("[BUF_MANAGER]: Logger was unregistered successfully", DEBUG);
}

// Unregister all the running loggers
static void UNREGISTER_ALL_LOGGERS() {
    for (int i = 0; i < BUFFER_COUNT / 2; i++) {
        if (BUFFERS[i].file_name != NULL) {
            BUFFERS[i].file_name = NULL;
            EXIT_LOGGER(BUFFERS[i]);
            BUFFER_SIZE--;
            PRINT_LOG("[BUF_MANAGER]: Unregistered logger successfully", DEBUG);
        }

        if (BUFFERS[BUFFER_COUNT-i-1].file_name != NULL) {
            BUFFERS[BUFFER_COUNT-i-1].file_name = NULL;
            EXIT_LOGGER(BUFFERS[BUFFER_COUNT-i-1]);
            BUFFER_SIZE--;
            PRINT_LOG("[BUF_MANAGER]: Unregistered logger successfully", DEBUG);
        }
    }
}

#endif //LOGGER_H
