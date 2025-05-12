/*
 * Logger demo and practices would be done here. Please feel free to submit
 * pull requests at https://github.com/DHANUSH-web/cmod-cli/pulls#
 */

#include "logger.h"

// Handle file system for specific platform
#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif

int main(const int argc, char *argv[]) {
    const char* app_name    = "app";
    char *root_dir          = getcwd(NULL, 100);    // Insert absolute path of project root ex:/home/.../cache
    const char* file_name   = "test_logger.log";    // Insert the file name of log file ex: test_logger.log

    strcat(root_dir, "/cache"); // Append logs directory to root directory
    struct LOGGER logger  = INIT_LOGGER(app_name, root_dir, file_name, TRUE);

    /*
        LOG method includes following parameters which can't be ignored in C

        @param1: struct Logger logger   => Logger instance
        @param2: char* message          => Message to be logged
        @param3: enum LEVEL level       => Log level
        @param4: BOOL debug_once        => Debug only once even if global debug is disabled
    */
    LOG(logger, "Error log",    ERROR,      FALSE);
    LOG(logger, "Info log",     INFO,       FALSE);
    LOG(logger, "Warning log",  WARNING,    FALSE);
    LOG(logger, "Debug log",    DEBUG,      FALSE);
    LOG(logger, "Message log",  INFO,       FALSE);
    LOG(logger, "Unknown log",  UNKNOWN,    FALSE);

    EXIT_LOGGER(&logger);
    return 0;
}
