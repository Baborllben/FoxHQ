#ifndef _FOXHQ_H
#define _FOXHQ_H

#include <stdio.h>
#include <time.h>
#include <Windows.h>

void print(char *str, int loglevel, char *levelname)
{
    time_t current_time;
    struct tm *time_info;
    char timeString[9];
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (loglevel)
    {
    case 1:
        // WARN
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 6);
        printf("[%s %s] %s", timeString, levelname, str);
        break;
    case 2:
        // ERROR
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 4);
        printf("[%s %s] %s", timeString, levelname, str);
        break;
    case 3:
        // DEBUG
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 2);
        printf("[%s %s] %s", timeString, levelname, str);
        break;
    default:
        // INFO
        printf("[%s %s] %s", timeString, levelname, str);
        break;
    }
    printf("\n");
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
}

#endif