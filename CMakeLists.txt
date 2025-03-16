cmake_minimum_required(VERSION 3.20)
project(c-logger VERSION 0.1.0 LANGUAGES C CXX)
include_directories(".")
set(CMAKE_C_STANDARD 11)

add_executable(clogger main.c
    logger.h
)
