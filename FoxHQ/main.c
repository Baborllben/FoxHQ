#include <WinSock2.h>
#include <WS2tcpip.h>
// #include <Windows.h>
#pragma comment(lib, "ws2_32.lib")
#include "foxhq.h"
#include "config.h"

#include <string.h>

DWORD WINAPI ThreadFunction(LPVOID lpParam);//当TCP线程建立的时候运行的函数

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
    toml_table_t *TABLE_server = toml_table_in(toml, "server");
    char CONFIG_bind_ip[16] = "";
    unsigned short CONFIG_bind_port;
    strcpy(CONFIG_bind_ip, Get_bindIP(TABLE_server));
    CONFIG_bind_port = Get_bindPort(TABLE_server);

    // 开启服务器
    WSADATA wsaData;
    int iResult;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);//初始化Winsock
    if (iResult != 0)
    {
        print("初始化Winsock出现问题", 2, "错误");
        return 0;
    }
    SOCKET Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//创建套接字
    if (Socket == INVALID_SOCKET) {
        print("创建套接字出现问题", 2, "错误");
        WSACleanup();
        return 0;
    }
    struct sockaddr_in server;//设置套接字地址
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(CONFIG_bind_ip);
    server.sin_port = htons(CONFIG_bind_port);
    iResult = bind(Socket, (SOCKADDR*)&server, sizeof(server));//绑定套接字
    if (iResult == SOCKET_ERROR) {
        print("绑定套接字时出现问题，可能是端口已被占用", 2, "错误");
        closesocket(Socket);
        WSACleanup();
        return 0;
    }
    iResult = listen(Socket, SOMAXCONN);//监听连接请求
    if (iResult == SOCKET_ERROR) {
        print("监听连接请求时出现问题", 2, "错误");
        closesocket(Socket);
        WSACleanup();
        return 0;
    }
    for (;;)
    {
        SOCKET clientSocket = accept(Socket, NULL, NULL);//接受客户端连接
        if (clientSocket == INVALID_SOCKET) {
            print("某个客户端连接失败", 1, "警告");
        }
        else
        {
            CreateThread(NULL, 0, ThreadFunction, (LPVOID)clientSocket, 0, NULL);
        }
    }
    return 0;
}

DWORD WINAPI ThreadFunction(LPVOID lpParam)
{
    SOCKET clientSocket = (SOCKET)lpParam;  // 将参数转换为 SOCKET 类型

    char buffer[1024];
    int bytesReceived;

    // 接收数据
    bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        printf("Received: %s\n", buffer);
        // 发送响应
        send(clientSocket, buffer, strlen(buffer), 0);
    } else {
        printf("Connection closed or error occurred.\n");
    }

    // 关闭套接字
    closesocket(clientSocket);
}