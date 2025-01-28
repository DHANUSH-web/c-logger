/*
 * Logger demo and practices would be done here. Please feel free to submit
 * pull requests at https://github.com/DHANUSH-web/cmod-cli/pulls#
 */

#include <logger.h>

int main(const int argc, char *argv[]) {
    const char* root_dir = "";    // Insert absolute path of project root ex:/home/.../cache
    const char* file_name = "";   // Insert the file name of log file ex: test_logger.log
    const struct LOGGER logger = INIT_LOGGER(root_dir, file_name, TRUE);

    LOG(logger, "Error log", ERROR, FALSE);
    LOG(logger, "Info log", INFO, FALSE);
    LOG(logger, "Warning log", WARNING, FALSE);
    LOG(logger, "Debug log", DEBUG, FALSE);
    LOG(logger, "Message log", INFO, FALSE);
    LOG(logger, "Unknown log", UNKNOWN, FALSE);

    EXIT_LOGGER(logger);
    return 0;
}
