# FoxHQ
FoxHQ is a multi-threaded Minecraft server rewritten in C, and I will try to restore Minecraft Java Edition

FoxHQ 是一个用C语言重写的多线程 Minecraft 服务端，致力于还原我的世界 Java 版所有特性和 bugs
# 已知漏洞 Known bugs
- FOXHQ-BUG_1：

    >The thread handle cannot be closed after the tcpClient thread is executed, resulting in a zombie thread. After the server is shut down, all zombie threads are automatically shut down.

    > 在 tcpClient 线程执行结束后无法关闭线程句柄，造成僵尸线程的情况。关闭服务端后，僵尸线程会自动全部关闭。

    + The current situation: This bug cannot be fixed
    + Reason: Foxrptr's technical capabilities are insufficient
    + 修复情况：无法修复
    + 原因：狐狸技术力不够，修复不了
