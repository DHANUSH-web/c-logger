/*
 *  ************************************************************************
 *  Copyright (c) 2025, Dhanush H V. All rights reserved.
 *  Licensed under the MIT License. See the LICENSE file for more details
 *  *************************************************************************
 */

#ifndef C_LOGGER_INCLUDE_LOGGER_H
#define C_LOGGER_INCLUDE_LOGGER_H

#include <stdio.h>
#include <time.h>
#include "main.h"

// different log levels
typedef enum {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL,
    MESSAGE,
    UNKNOWN,
} LEVEL;

// Define a level handler struct
struct LVL_HANDLER {
    LEVEL       level;
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

// RETURN TYPE  METHOD                      SIGNATURE/PARAMETERS
struct LOGGER   INIT_LOGGER                 (const char* name, const char* root_dir, const char* file_name, BOOL debug);
BOOL            IS_LOGGER_ACTIVE            (struct LOGGER logger);
void            LOG                         (struct LOGGER logger, const char* message, LEVEL level, BOOL debug_once);
void            PRINT_LOG                   (const char* message, LEVEL level);
int             GET_LOGGER_LOG_COUNT        (struct LOGGER logger);
int             GET_LOGGER_LEVEL_COUNT      (struct LOGGER logger, LEVEL level);
char*           GET_LOGGER_LEVEL_STRING     (LEVEL level);
void            DISPLAY_LOGGER_LEVELS       (struct LOGGER logger);
time_t          GET_LOGGER_START_TIME       (struct LOGGER logger);
time_t          GET_LOGGER_END_TIME         (struct LOGGER logger);
void            EXIT_LOGGER                 (struct LOGGER* logger);
char*           GET_CURRENT_DATE_TIME       ();
void            REGISTER_LOGGER             (struct LOGGER logger);
void            UNREGISTER_LOGGER           (struct LOGGER logger);
void            UNREGISTER_ALL_LOGGERS      ();
BOOL            IS_LOGGER_REGISTERED        (struct LOGGER logger);

#endif
