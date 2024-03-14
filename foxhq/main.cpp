#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

#include "@readConfigFileDLL.h"

#define INFO 100
#define WARN 101
#define ERROR_IN_FOXHQ 102
#define DEBUG 103

// 控制台颜色文字
void color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 设置当前时间与日志级别
void setTimeHead(int color, int header)
{
    time_t a;
    struct tm b;

    time(&a);
    localtime_s(&b, &a);
    char buffer[64] = { 0 };
    //int color = 0x08;
    int buffer_hour = b.tm_hour;
    int buffer_min = b.tm_min;
    int buffer_sec = b.tm_sec;
    //asctime_s(buffer, 32, &b);
    switch (header)
    {
        case 100:
            sprintf_s(buffer, "[%02d:%02d:%02d] [Main()/INFO] \0", buffer_hour, buffer_min, buffer_sec);
            break;
        case 101:
            sprintf_s(buffer, "[%02d:%02d:%02d] [Main()/WARN] \0", buffer_hour, buffer_min, buffer_sec);
            break;
        case 102:
            sprintf_s(buffer, "[%02d:%02d:%02d] [Main()/ERROR] \0", buffer_hour, buffer_min, buffer_sec);
            break;
        case 103:
            sprintf_s(buffer, "[%02d:%02d:%02d] [Main()/INFO] \0", buffer_hour, buffer_min, buffer_sec);
            break;
        default:
            break;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    printf("%s", buffer);
}


int main(void)
{
    system("title Fotailx FoxHQ");
    // Fotailx
    setTimeHead(0x08, INFO); printf("  ______      _          _  _       \n");
    setTimeHead(0x08, INFO); printf(" |  ____|    | |        (_)| |      \n");
    setTimeHead(0x08, INFO); printf(" | |__  ___  | |_  __ _  _ | |__  __\n");
    setTimeHead(0x08, INFO); printf(" |  __|/ _ \\ | __|/ _` || || |\\ \\/ /\n");
    setTimeHead(0x08, INFO); printf(" | |  | (_) || |_| (_| || || | >  < \n");
    setTimeHead(0x08, INFO); printf(" |_|   \\___/  \\__|\\__,_||_||_|/_/\\_\\\n");
    ConnectToDLL();
    return 0;
}