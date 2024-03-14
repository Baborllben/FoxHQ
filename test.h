#include<stdio.h>
#include<Winsock2.h>
#include<time.h>
#include<string.h>
#pragma warning(disable:4996)
#pragma comment(lib,"ws2_32.lib")

#define USER_ERROR -1

int main()
{
    char recvData[200];
    char sendData[200];
    int ret;
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("Failed to load Winsock.\n");
        return USER_ERROR;
    }

    SOCKET socket_of_server;
    SOCKET socket_of_client;
    socket_of_server = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_of_server == INVALID_SOCKET)
    {
        printf("socket() Failed:%d\n", WSAGetLastError());
        return USER_ERROR;
    }

    struct sockaddr_in s_sin;
    s_sin.sin_family = AF_INET;
    s_sin.sin_port = htons(6666);
    s_sin.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    if (bind(socket_of_server, (LPSOCKADDR)&s_sin, sizeof(s_sin)) == SOCKET_ERROR)
    {
        printf("blind() Failed:%d\n", WSAGetLastError());
        return USER_ERROR;
    }
    if (listen(socket_of_server, 5) == SOCKET_ERROR)
    {
        printf("listen() Failed:%d\n", WSAGetLastError());
        return USER_ERROR;
    }
    struct sockaddr_in c_sin;
    int c_sin_len = sizeof(c_sin);
    while (1)
    {
        printf("waiting for connect\n");
        socket_of_client = accept(socket_of_server, (SOCKADDR *)&c_sin, &c_sin_len);
        if (socket_of_client== INVALID_SOCKET)
            printf("accept() Failed:%d\n", WSAGetLastError());
        else
        {
            printf("接收到一个连接：%s\r\n", inet_ntoa(c_sin.sin_addr));
            while (1)
            {
                printf("读取消息：");
                recvData[0] = '\0';
                ret = recv(socket_of_client, recvData, 200, 0);
                if (ret < 0)
                {
                    printf("something wrong\n");
                    continue;
                }
                recvData[ret] = '\0';
                if (strcmp(recvData, "quit") == 0)
                    break;
                printf("%s\n", recvData);
                printf("发送消息：");
                scanf("%s", sendData);
                printf("\n");
                send(socket_of_client, sendData, strlen(sendData), 0);
                if (strcmp("quit", sendData) == 0)
                    break;
            }
        }
        
    }
    
    closesocket(socket_of_server);
    WSACleanup();
    return 0;
}

 

客户端

#include <winsock2.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <direct.h>     
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)

#define USER_ERROR -1

int main()
{
    char recvData[200];
    char sendData[200];
    int ret;


    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("Failed to load Winsock.\n");
        return USER_ERROR;
    }

    SOCKET socket_client = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_client == INVALID_SOCKET)
    {
        printf(" Failed socket() \n");
        return 0;
    }

    struct sockaddr_in server_in;
    server_in.sin_family = AF_INET;
    server_in.sin_port = htons(6666);
    server_in.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    if (connect(socket_client, (struct sockaddr*)&server_in, sizeof(server_in)) == -1)
    {
        printf(" Failed connect() \n");
        return 0;
    }
    else
    {
        printf("connect %s.%d\n", inet_ntoa(server_in.sin_addr), server_in.sin_port);
        while (1)
        {
            printf("发送消息：");
            scanf("%s", sendData);
            printf("\n");
            send(socket_client, sendData, strlen(sendData), 0);
            if (strcmp(sendData, "quit") == 0)
                break;
            printf("读取消息：");
            recvData[0] = '\0';
            ret = recv(socket_client, recvData, 200, 0);
            recvData[ret] = '\0';
            printf("%s\n", recvData);
        }

    }
    closesocket(socket_client);
    WSACleanup();
    return 0;
}
