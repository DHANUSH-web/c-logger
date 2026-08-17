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
git clone https://github.com/DHANUSH-web/c-logger.git extras/logger --recurse-submodules --depth 1
```

**_For development release_**

```sh
git clone https://github.com/DHANUSH-web/c-logger.git extras/logger --branch dev --recurse-submodules --depth 1
```

We are using `CMake` as build-system in your project, don't forget to include the logger inside `CMakeLists.txt`

```cmake
add_exectuable(<TARGET> extras/logger/src/logger.c ...)
target_include_directories(<TARGET> PRIVATE extras/logger/include ...)
```

## Building
There are two presets `debug` and `release` for CMake build. Replace `profile` with `debug` or `release` as per your requirements

```sh
# build
cmake --preset profile
cmake --build ./out/profile

# run
./out/profile/c-logger          # main target
./out/profile/c-logger-tests    # test target
```

## Quick Start

Open `src/main.c` file inside logger and try to explore the code

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the LICENSE file for more details.

## Developer

`CLogger` is purely written in `C` developed by [DHANUSH H V](https://dhanushhv.vercel.app)
