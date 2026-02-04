# C Logger - A Utility C program for logging events and program flow

<div style="background-color: #ffffff11; font-family: inter; text-align: justify; padding: 12px; border-radius: 5px;">
A Logger header file program written in C as a procedural design to handle events and program flow in your application without worrying about the biggest headache of debugging an issue from multiple program files. CLogger allows you to manage any number of logger instances across your entire project for easy access to different module level loggers.

In a simple words, CLogger is not a shared or compiled library, it is a lightweight, powerful, and flexible logging header program for C programs or applications.

</div>

## Features

- 🚀 Fully customizable and adaptable `API` to meet specific requirements
- ⚡ High-performance logging capabilities
- 🎨 Shared logger instances across the entire project using Buffer Manager
- 🎯 Multiple logger instances in the same runtime
- 🔍 Multiple logging levels (`DEBUG`, `INFO`, `WARNING`, `ERROR`, `CRITICAL`, `UNKNOWN`)

## Usage

Clone the repo directly from `https://github.com/DHANUSH-web/c-logger.git` into your project anywhere

**_For stable release_**

```sh
git clone https://github.com/DHANUSH-web/c-logger.git
```

**_For development release_**

```sh
git clone -b dev https://github.com/DHANUSH-web/c-logger.git
```

If you are using `CMake` as build-system in your project, don't forget to include the logger inside `CMakeLists.txt`

```cmake
include_directories(logger)
add_executable(... ... logger/logger.h)
```

**Note:** You can also run a demo program inside logger `main.c` using the build script.

Build the project using the provided script (on Linux or macOS run `./build`; on Windows run `./build.bat`):

```bash
# For only building
./build build           # builds in debug by default [RECOMMENDED]
./build build --debug   # builds in debug preset
./build build --release # builds in release preset
./build build --all     # builds both debug and release preset
# For build and run
./build run             # runs in debug by default [RECOMMENDED]
./build run --debug     # runs in debug preset
./build run --release   # runs in release preset
```

This will:
- Create a build directory
- Configure CMake with the default preset
- Build the project
- Run the executable (when using `run`)

Clean the project:

```bash
./build clean           # cleans the entire build [RECOMMENDED]
./build clean --debug   # cleans only debug build
./build clean --release # cleans only release build
```

**Note**: Use `./build help` to learn more about `./build` command usage

## Quick Start

Open `main.c` file inside logger and try to explore the code

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the LICENSE file for more details.

## Developer

`CLogger` is purely written in `C` developed by [DHANUSH H V](https://dhanushhv.vercel.app)
