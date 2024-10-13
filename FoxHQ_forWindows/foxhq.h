#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

// windows
#include <Windows.h>

// time
#include <time.h>

// iniparser
#include "util/iniparser/dictionary.h"
#include "util/iniparser/iniparser.h"

// cjson
#include "util/cjson/cJSON.h"

int isConfigFileExists() {
    FILE* file = fopen("config.ini", "r");
    if (file)
    {
        fclose(file);
        return 1;
    }
    else
    {
        return 0;
    }
}

void print(char* str, int loglevel)
{
    time_t current_time;
    struct tm* time_info;
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
        printf("[%s WARN] %s\n", timeString, str);
        break;
    case 2:
        // ERROR
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 4);
        printf("[%s ERROR] %s\n", timeString, str);
        break;
    case 3:
        // DEBUG
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 2);
        printf("[%s DEBUG] %s\n", timeString, str);
        break;
    default:
        // INFO
        printf("[%s INFO] %s\n", timeString, str);
        break;
    }
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | 7);
}