cmake_minimum_required(VERSION 3.20)
project(c-logger C)
include_directories("logger")
set(CMAKE_C_STANDARD 11)

add_executable(clogger main.c
    logger/logger.h
)
