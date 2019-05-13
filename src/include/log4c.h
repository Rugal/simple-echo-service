#ifndef LOG4C_H
#define LOG4C_H

#include <stdio.h>
#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

enum Log4CLevel {
  LOG4C_ALL     = 0,
  LOG4C_TRACE   = 1,
  LOG4C_DEBUG   = 2,
  LOG4C_INFO    = 3,
  LOG4C_WARNING = 4,
  LOG4C_ERROR   = 5,
  LOG4C_OFF     = 6
};

static const char* LOG_NAME[] = {"ALL",
                                 "TRACE",
                                 "DEBUG",
                                 "INFO",
                                 "WARN",
                                 "ERROR",
                                 "OFF"};

extern int log4c_level;

#define LOG(level, fmt, ...) \
  if (level >= log4c_level) { \
    fprintf(level >= LOG4C_ERROR ? stderr : stdout, \
            "[%5s] %20s @ %-12s#%3d: " fmt "\n", \
            LOG_NAME[level], \
            __func__, \
            __FILENAME__, \
            __LINE__, \
            ##__VA_ARGS__); \
  }

#define LOG_ALL(fmt, ...)   LOG(LOG4C_ALL, fmt, ##__VA_ARGS__)
#define LOG_TRACE(fmt, ...) LOG(LOG4C_TRACE, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) LOG(LOG4C_DEBUG, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)  LOG(LOG4C_INFO, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)  LOG(LOG4C_WARN, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) LOG(LOG4C_ERROR, fmt, ##__VA_ARGS__)

#endif

