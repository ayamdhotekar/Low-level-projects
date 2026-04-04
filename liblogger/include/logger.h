#ifndef LOGGER_H
#define LOGGER_H

typedef enum {
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
} log_level;

void logger_init(const char *filename);
void log_message(log_level level, const char *msg);
void logger_close();

#endif
