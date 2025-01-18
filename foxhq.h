#ifndef _FOXHQ_H
#define _FOXHQ_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

void print(const char *format, int loglevel, const char *levelname, ...) {
    time_t current_time;
    struct tm *time_info;
    char timeString[9];
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (loglevel) {
    case 1:  // WARN
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 6);
        break;
    case 2:  // ERROR
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 4);
        break;
    case 3:  // DEBUG
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 2);
        break;
    default:  // INFO
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
        break;
    }

    va_list args;
    va_start(args, levelname);

    // 使用 vprintf 打印格式化字符串
    printf("[%s %s] ", timeString, levelname);
    vprintf(format, args);
    printf("\n");

    // 重置控制台颜色
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);

    va_end(args);
}

#endif