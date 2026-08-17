cmake_minimum_required(VERSION 3.20)
project(c-logger LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED OFF)
set(CMAKE_C_EXTENSIONS OFF)

# main target
add_executable(c-logger src/main.c src/logger.c)
target_include_directories(c-logger PRIVATE include)

# test target
add_executable(c-logger-tests tests/test_logger.c src/logger.c extras/unity/src/unity.c)
target_include_directories(c-logger-tests PRIVATE include extras/unity/src)
