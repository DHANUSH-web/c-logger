// include headers
#include "logger.h"
#include "main.h"

int main(void)
{
    struct LOGGER logger = INIT_LOGGER("demo_logger", "logs", "demo_logger.log", TRUE);

    LOG(logger, "Register info log",    INFO,    FALSE);
    LOG(logger, "Register error log",   ERROR,   FALSE);
    LOG(logger, "Register warning log", WARNING, FALSE);
    LOG(logger, "Register fatal log",   FATAL,   FALSE);

    EXIT_LOGGER(&logger);

    return 0;
}
