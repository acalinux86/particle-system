#ifndef LOG_H_
#define LOG_H_

#include <stdio.h>
#include <stdarg.h>

typedef enum {
    INFO,
    ERROR,
    DEBUG,
    WARN,
    USAGE,
    COUNT_LEVELS,
} Log_Levels;

void Logging(FILE *stream, Log_Levels level, const char *fmt, ...);

#define Log(level, fmt, ...) Logging(stdout, level, fmt, ##__VA_ARGS__)
#define Logf(stream, level, fmt, ...) Logging(stream, level, fmt, ##__VA_ARGS__)

#endif // LOG_H_

