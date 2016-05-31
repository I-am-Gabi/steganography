#include <stdlib.h>
#include <stdio.h>
#include "../../includes/log.h"

// font: http://www.falloutsoftware.com/tutorials/c/c1.htm

int LogCreated = 0;
char* LOGFILE = "resource/output/log.txt";

void Log(char *message)
{
    FILE *file;

    if (!LogCreated) {
        file = fopen(LOGFILE, "w");
        LogCreated = 1;
    } else {
        file = fopen(LOGFILE, "a");
    }

    if (file == NULL) {
        if (LogCreated)
            LogCreated = 0;
        return;
    } else {
        fputs(message, file);
        fputs("\n", file);
        fclose(file);
    }

    if (file)
        fclose(file);
}

void LogInt(double data) {
    FILE *file;
    file = fopen(LOGFILE, "a");
    fprintf(file, "%f\n", data);
    fclose(file);
}

void LogErr(char *message)
{
    Log(message);
    Log("\n");
}