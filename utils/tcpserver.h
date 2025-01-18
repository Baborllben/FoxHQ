#include <WinSock2.h>
#include <WS2tcpip.h>
// #include <Windows.h>
#pragma comment(lib, "ws2_32.lib")
#include "../foxhq.h"

struct tcpserver
{
    char *bind_ip;
    unsigned short bind_port;
    unsigned int max_connection;
};

struct tcpclient_info
{
    SOCKET ClientSocket;
    char *client_ip;
    unsigned short client_port;
    int currentNumberOfConnections;//当前连接数
};


DWORD WINAPI ThreadFunction(LPVOID lpParam);//当TCP线程建立的时候运行的函数

DWORD WINAPI tcpServer(LPVOID lpParam)
{
    // 解包要用的数据
    struct tcpserver *serverOptions = (struct tcpserver *)lpParam;
    char *bind_ip = serverOptions->bind_ip;
    unsigned short bind_port = serverOptions->bind_port;
    unsigned int max_connection = serverOptions->max_connection;

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
    server.sin_addr.s_addr = inet_addr(bind_ip);
    server.sin_port = htons(bind_port);
    iResult = bind(Socket, (SOCKADDR*)&server, sizeof(server));//绑定套接字
    if (iResult == SOCKET_ERROR) {
        print("绑定套接字时出现问题，可能是端口已被占用", 2, "错误");
        closesocket(Socket);
        WSACleanup();
        return 0;
    }
    iResult = listen(Socket, max_connection);//监听连接请求
    if (iResult == SOCKET_ERROR) {
        print("监听连接请求时出现问题", 2, "错误");
        closesocket(Socket);
        WSACleanup();
        return 0;
    }
    print("服务器已开始监听%s:%d", 3, "信息", bind_ip, bind_port);

    HANDLE *threadHandles = (HANDLE *)calloc(max_connection, sizeof(HANDLE));
    int initial_currentNumberOfConnections = 0;//检测当前连接数有没有自减 所需要使用的变量：初始当前连接数
    int currentNumberOfConnections = 0;//当前连接数
    for (;;currentNumberOfConnections++)
    {
        struct sockaddr_in client;
        int clientSize = sizeof(client);

        // 接受客户端连接
        SOCKET clientSocket = accept(Socket, (SOCKADDR*)&client, &clientSize);

        // 获取客户端 IP 和端口
        struct tcpclient_info *tcpClientInfo = (struct tcpclient_info *)malloc(sizeof(struct tcpclient_info));
        tcpClientInfo->client_ip = (char *)malloc(16);
        inet_ntop(AF_INET, &client.sin_addr, tcpClientInfo->client_ip, 16);
        tcpClientInfo->client_port = ntohs(client.sin_port);
        tcpClientInfo->ClientSocket = clientSocket;
        tcpClientInfo->currentNumberOfConnections = currentNumberOfConnections;

        if (clientSocket == INVALID_SOCKET) {
            print("客户端 %s:%d 连接失败", 1, "警告", tcpClientInfo->client_ip, tcpClientInfo->client_port);
            free(tcpClientInfo->client_ip);
            free(tcpClientInfo);
        }
        else
        {
            print("客户端 %s:%d 开始连接", 1, "信息", tcpClientInfo->client_ip, tcpClientInfo->client_port);
            if (currentNumberOfConnections >= max_connection)
            {
                closesocket(tcpClientInfo->ClientSocket);
                print("客户端 %s:%d 爆满加入，已掐断连接", 1, "警告", tcpClientInfo->client_ip, tcpClientInfo->client_port);
                free(tcpClientInfo->client_ip);
                free(tcpClientInfo);
            }
            else threadHandles[currentNumberOfConnections] = CreateThread(NULL, 0, ThreadFunction, (LPVOID)tcpClientInfo, 0, NULL);
        }
    }
    return 0;
}

DWORD WINAPI ThreadFunction(LPVOID lpParam)
{
    // 将参数转换为 struct tcpclient_info * 类型
    struct tcpclient_info *tcpClientInfo = (struct tcpclient_info *)lpParam;

    char *buffer = (char *)malloc(4096);
    int bytesReceived;

    for(;;)
    {
        // 接收数据
        bytesReceived = recv(tcpClientInfo->ClientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            printf("Received: %s\n", buffer);
            // 发送响应
            send(tcpClientInfo->ClientSocket, buffer, strlen(buffer), 0);
            memset(buffer, 0, sizeof(buffer));//清空buffer
        }
        else if (bytesReceived == 0)
        {
            print("客户端 %s:%d 结束连接", 1, "信息", tcpClientInfo->client_ip, tcpClientInfo->client_port);
            break;
        }
        else
        {
            // 出现错误
            int errorCode = WSAGetLastError();
            print("客户端 %s:%d 连接出错，错误代码: %d", 2, "错误", tcpClientInfo->client_ip, tcpClientInfo->client_port, errorCode);
            break;
        }
    }

    // 当前连接数 - 1
    tcpClientInfo->currentNumberOfConnections--;

    // 释放 tcpClientInfo 以及 buffer
    free(tcpClientInfo->client_ip);
    free(tcpClientInfo);
    free(buffer);
    
    // 关闭套接字
    closesocket(tcpClientInfo->ClientSocket);

    // 关闭线程
    ExitThread(0);
}