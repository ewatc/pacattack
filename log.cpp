#include "log.h"
#include <stdio.h>

static FILE *gLogfile = 0;

const char LevelToString[][4] = {
    "CRT",
    "ERR",
    "WRN",
    "NOT",
    "INF",
    "DBG"
};


void OpenLog(const std::string &filename)
{
    if (gLogfile) {
        CloseLog();
    }

    gLogfile = fopen(filename.c_str(), "w");
}

void CloseLog()
{
    if (gLogfile) {
        fclose(gLogfile);
        gLogfile = NULL;
    }
}

void Log(int level, const char *msgfmt, ...)
{
    if (level <= LOG_DEBUG) {
        char fullMessage[1024];
        va_list args;

        va_start(args, msgfmt);

        vsprintf(fullMessage, msgfmt, args);
        if (gLogfile) {
            fprintf(gLogfile, "%s: %s\n", LevelToString[level], fullMessage);
            fflush(gLogfile);
        } else {
            printf("%s: %s\n", LevelToString[level], fullMessage);
        }

        va_end(args);
    }
}
