cmake_minimum_required(VERSION 3.20)
project(ModularC C)
include_directories("custom")
set(CMAKE_C_STANDARD 11)

add_executable(ModularC main.c
    custom/logger.h
)
