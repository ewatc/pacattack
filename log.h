
#ifndef _EWATC_LOG_H
#define _EWATC_LOG_H

#include <stdarg.h>
#include <string>

// Log Levels
enum {
    LOG_CRITICAL,
    LOG_ERROR,
    LOG_WARNING,
    LOG_NOTICE,
    LOG_INFO,
    LOG_DEBUG
};

// This define allows for compile time
// level limit to logging.
#define LOG_COMPILETIME_LEVEL LOG_DEBUG

#define LOG_GENERIC(_level, _msgfmt, args...) \
    do { \
        if (LOG_COMPILETIME_LEVEL >= _level) { \
            Log(_level, _msgfmt , ## args); \
        } \
    } while(0)

#define LOGCRT(_msgfmt, args...) \
    LOG_GENERIC(LOG_CRITICAL,_msgfmt, ## args)

#define LOGERR(_msgfmt, args...) \
    LOG_GENERIC(LOG_ERROR, _msgfmt, ## args)

#define LOGWRN(_msgfmt, args...) \
    LOG_GENERIC(LOG_WARNING, _msgfmt, ## args)

#define LOGNOT(_msgfmt, args...) \
    LOG_GENERIC(LOG_NOTICE, _msgfmt, ## args)

#define LOGINF(_msgfmt, args...) \
    LOG_GENERIC(LOG_INFO,  _msgfmt, ## args)

#define LOGDBG(_msgfmt, args...) \
    LOG_GENERIC(LOG_DEBUG, _msgfmt, ## args)


void OpenLog(const std::string &filename);
void CloseLog();

void Log(int level, const char *msgfmt, ...);

#endif
