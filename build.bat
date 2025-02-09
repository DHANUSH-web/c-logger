@echo off

REM Set the path variables
set BUILD_DIR=out
set EXECUTABLE="clogger.exe"
set GCC="gcc.exe"
set G++="g++.exe"
set CMAKE="cmake.exe"
set MAKE="make.exe"
set GENERATOR="MinGW Makefiles"

REM Remove old cache folders
if exist %BUILD_DIR% rmdir /s /q %BUILD_DIR%

REM Create the directory
mkdir %BUILD_DIR%

REM Change directory to build directory
cd %BUILD_DIR%

REM Compile the project with CMake gcc and g++ compilers
%CMAKE% -G %GENERATOR% -DCMAKE_C_COMPILER=%GCC% -DCMAKE_MAKE_PROGRAM=%MAKE% ..

REM Build the Makefile
%MAKE%

REM Remove the final binary once executed
cd ..

REM Execute the final binary
"./%BUILD_DIR%/%EXECUTABLE%"

REM Print the final success message for little nerd happyness after hours of grinding :)
echo "You did it nerd.. Congrats!! Now go and have a break buddy :)"
