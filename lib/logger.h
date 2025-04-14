#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

enum class LogType
{
    INFO,
    DUMP,
    ERROR,
    WARNING,
    ASSERT
};

FILE *OpenLog(const char *const logfile_name);

void  CloseLogFile();
void  LogPrint(const char *const file, const int line, const char *const func, LogType log_type, const char *const format, ...);

#define DEFAULT_LOGFILE_NAME  "LogFile.html"
#define LOG_FOLDER            "logs"


#define log(log_type, format, ...)  LogPrint(__FILE__, __LINE__, __func__, log_type, format, ##__VA_ARGS__)

#define lassert(condition)                              \
do                                                       \
{                                                         \
    if (!condition, fall_text)                             \
    {                                                       \
        log(LogType::ASSERT, fall_text);                     \
        abort();                                              \
    }                                                          \
} while(0)

#ifdef USE_LOGS

#define ON_LOGS(...)  __VA_ARGS__

#define logctor(logfile_name)                              \
do                                                          \
{                                                            \
    if (#logfile_name[0] == '\0')                             \
    {                                                          \
        system("mkdir -p " LOG_FOLDER);                         \
        OpenLog(LOG_FOLDER "/" DEFAULT_LOGFILE_NAME);            \
    }                                                             \
                                                                   \
    else                                                            \
    OpenLog(logfile_name "");                                        \
} while(0)


#else
#define ON_LOGS(...)
#define logctor(logfile_name)
#endif

#endif