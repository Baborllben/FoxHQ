#include <stdio.h>
#include <Windows.h>
#include <time.h>
#define INFO 100
#define WARN 101
#define ERROR_IN_FOXHQ 102
#define DEBUG 103

void setTimeHead_in_Rhyotonium(int color, int header)
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
        sprintf_s(buffer, "[%02d:%02d:%02d] [@readConfigFileDLL.h/INFO] \0", buffer_hour, buffer_min, buffer_sec);
        break;
    case 101:
        sprintf_s(buffer, "[%02d:%02d:%02d] [@readConfigFileDLL.h/WARN] \0", buffer_hour, buffer_min, buffer_sec);
        break;
    case 102:
        sprintf_s(buffer, "[%02d:%02d:%02d] [@readConfigFileDLL.h/ERROR] \0", buffer_hour, buffer_min, buffer_sec);
        break;
    case 103:
        sprintf_s(buffer, "[%02d:%02d:%02d] [@readConfigFileDLL.h/INFO] \0", buffer_hour, buffer_min, buffer_sec);
        break;
    default:
        break;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    printf("%s", buffer);
}

int ConnectToDLL()
{
    typedef char* (*_getAuthor)(void);
    typedef char* (*_getBuildDate)(void);
    typedef char* (*_getDescription)(void);

    HMODULE hdll = LoadLibrary(L"@readConfigFile.dll");//加载dll文件
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
    else {
        setTimeHead_in_Rhyotonium(0x04, ERROR_IN_FOXHQ); printf("The application is missing a critical component.");
        MessageBox(NULL, L"@readConfigFile.dll 可能丢失或损坏\nFile @readConfigFile.dll may have been lost or damaged", L"Fotailx FoxHQ LoadLibrary", MB_OK | MB_ICONSTOP);
        return 0;
    }

    FreeLibrary(hdll);//释放dll文件
}