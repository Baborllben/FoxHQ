#include <WinSock2.h>
#include <WS2tcpip.h>
// #include <Windows.h>
#pragma comment(lib, "ws2_32.lib")
#include "foxhq.h"
#include "config.h"
#include "utils/tcpserver.h"

#include <string.h>

int main()
{
    // 将输出转化为UTF-8
    SetConsoleOutputCP(CP_UTF8);

    print("FoxHQ 正在启动", 1, "信息");

    // 读取配置文件（toml）
    print("正在解析 `config.toml`", 0, "信息");

    char *buffer = (char *)malloc(4096);
    memset(buffer, 1, 4096 - 1);    //将前4095位设置为'\1'
    buffer[4095] = '\0';            //最后一位设置为'\0'

    int code = Get_Config_File_Content(buffer);
    
    // 处理配置文件
    switch (code)
    {
    case 1:
        print("读取配置文件 `config.toml` 出错", 2, "错误");
        print("原因：文件不存在！", 2, "错误");
        print("正在关闭服务器...", 0, "信息");
        return 0;
        break;

    case 2:
        print("读取配置文件 `config.toml` 出错", 2, "错误");
        print("原因：缓冲区太小！（文件大小过大！）", 2, "错误");
        print("正在关闭服务器...", 0, "信息");
        return 0;
        break;
    }
    
    // 解析toml
    char *errbuf = (char *)malloc(1024);
    toml_table_t *toml = parse_Config_File(buffer, errbuf);
    if (!toml)
    {
        print("读取配置文件 `config.toml` 出错", 2, "错误");
        print("原因：`tomlc99` toml_table_t *toml 为 NULL", 2, "错误");
        print(errbuf, 2, "错误");
        print("正在关闭服务器...", 0, "信息");
        return 0;
    }

    // [server] 表解析
    struct tcpserver *serverOptions = (struct tcpserver *)malloc(sizeof(struct tcpserver));
    toml_table_t *TABLE_server = toml_table_in(toml, "server");

    serverOptions->bind_ip = (char *)malloc(16);
    strcpy(serverOptions->bind_ip, Get_bindIP(TABLE_server));//bind_ip
    print("已加载配置：bind_ip = %s", 0, "信息", serverOptions->bind_ip);

    serverOptions->bind_port = Get_bindPort(TABLE_server);//bind_port
    print("已加载配置：bind_port = %d", 0, "信息", serverOptions->bind_port);
    serverOptions->max_connection = Get_maxConnection(TABLE_server);//max_connection
    print("已加载配置：bind_ip = %d", 0, "信息", serverOptions->max_connection);

    // 开启服务器
    HANDLE TCPSERVER = CreateThread(NULL, 0, tcpServer, serverOptions, 0, NULL);
    if (TCPSERVER == NULL) {
        print("创建 TCPSERVER 失败！", 2, "错误");
        free(serverOptions->bind_ip);
        free(serverOptions);
        return 0;
    }

    WaitForSingleObject(TCPSERVER, INFINITE);
    CloseHandle(TCPSERVER);
    return 0;
}