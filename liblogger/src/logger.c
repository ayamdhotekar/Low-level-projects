#include <stdio.h>
#include <time.h>
#include "../include/logger.h"

static FILE *log_file = NULL;

static const char* level_str(log_level level) {
    switch(level) {
        case LOG_INFO: return "INFO";
        case LOG_WARN: return "WARN";
        case LOG_ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

void logger_init(const char *filename) {
    log_file = fopen(filename, "a");
}

void log_message(log_level level, const char *msg) {
    if (!log_file) return;

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    fprintf(log_file, "[%02d:%02d:%02d] %s: %s\n",
            t->tm_hour, t->tm_min, t->tm_sec,
            level_str(level), msg);

    fflush(log_file);
}

void logger_close() {
    if (log_file) fclose(log_file);
}
