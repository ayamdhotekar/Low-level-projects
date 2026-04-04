#include "../include/logger.h"

int main() {
    logger_init("app.log");

    log_message(LOG_INFO, "Application started");
    log_message(LOG_WARN, "Low memory warning");
    log_message(LOG_ERROR, "Something went wrong");

    logger_close();
    return 0;
}
