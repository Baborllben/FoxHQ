#include <stdio.h>
#include <windows.h>
#include <time.h>

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
    char buffer[32] = { 0 };
    char header_c[] = "Main Thread";
    //int color = 0x08;
    int buffer_hour = b.tm_hour;
    int buffer_min = b.tm_min;
    int buffer_sec = b.tm_sec;
    //asctime_s(buffer, 32, &b);
    switch (header)
    {
    case INFO:
        sprintf_s(buffer, "[%02d:%02d:%02d] [%s/INFO] \0", buffer_hour, buffer_min, buffer_sec, header_c);
    case WARN:
        sprintf_s(buffer, "[%02d:%02d:%02d] [%s/WARN] \0", buffer_hour, buffer_min, buffer_sec, header_c);
    case ERROR_IN_FOXHQ:
        sprintf_s(buffer, "[%02d:%02d:%02d] [%s/ERROR] \0", buffer_hour, buffer_min, buffer_sec, header_c);
    case DEBUG:
        sprintf_s(buffer, "[%02d:%02d:%02d] [%s/INFO] \0", buffer_hour, buffer_min, buffer_sec, header_c);
    default:
        break;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    printf("%s", buffer);
}


int main(void)
{
    // Fotailx
    setTimeHead(0x08, INFO); printf("  ______      _          _  _       \n");
    setTimeHead(0x08, INFO); printf(" |  ____|    | |        (_)| |      \n");
    setTimeHead(0x08, INFO); printf(" | |__  ___  | |_  __ _  _ | |__  __\n");
    setTimeHead(0x08, INFO); printf(" |  __|/ _ \\ | __|/ _` || || |\\ \\/ /\n");
    setTimeHead(0x08, INFO); printf(" | |  | (_) || |_| (_| || || | >  < \n");
    setTimeHead(0x08, INFO); printf(" |_|   \\___/  \\__|\\__,_||_||_|/_/\\_\\\n");
    typedef char* (*_getAuthor)(void);
    typedef char* (*_getBuildDate)(void);
    typedef char* (*_getDescription)(void);
    
    HMODULE hdll = LoadLibrary(L"Foxrptr@readConfigFile.dll");//加载dll文件
    if (hdll != NULL)
    {
        _getAuthor getAuthor = (_getAuthor)GetProcAddress(hdll, "getAuthor");//检索要调用函数的地址
        _getBuildDate getBuildDate = (_getBuildDate)GetProcAddress(hdll, "getBuildDate");
        _getDescription getDescription = (_getDescription)GetProcAddress(hdll, "getDescription");
        if (getAuthor != NULL && getDescription != NULL && getBuildDate != NULL)
        {
            printf("作者: %s\n", getAuthor());//调用接口函数
            printf("日期: %s\n", getBuildDate());
            printf("描述:\n%s\n", getDescription());
            system("pause");
        }
    }

    FreeLibrary(hdll);//释放dll文件
    return 0;
}