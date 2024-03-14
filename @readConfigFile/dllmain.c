// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"

char* getAuthor(void)
{
    static char str[32] = "Foxrptr";
    return str;
}

char* getBuildDate(void)
{
    static char str[32] = "nmsl/cnm/sb";//不是时间的时间
    return str;
}

char* getVersion(void)
{
    static char str[1024] = "0.0.0.1";
    return str;
}

char* getDescription(void)
{
    static char str[1024] = "Foxrptr\nthis dll file is useless";
    return str;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

