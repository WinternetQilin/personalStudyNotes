#include <stdio.h>
#include <unistd.h> //linux操作系统标准头文件
#include <string.h> //memcpy
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h> //umask
#include <time.h>
#include <sys/time.h>
#include <dirent.h> //遍历目录
#include <fcntl.h>  //文件映射虚拟内存
#include <sys/mman.h>
#include <wait.h>
#include <signal.h> //SIGCHLD
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/select.h>
#define MAX_CONNECT_NUM 1024
int clientFds[MAX_CONNECT_NUM];
int serverFd;
void hand(int s)
{
    if (2 == s)
    {
        // 7.断开连接
        for (int i = 0; i < MAX_CONNECT_NUM; i++)
        {
            if (-1 != clientFds[i])
                close(clientFds[i]);
        }
        close(serverFd);
        printf("服务器关闭\n");
        exit(1);
    }
}

int main()
{
    signal(2, hand);
    for (int i = 0; i < MAX_CONNECT_NUM; i++)
    {
        clientFds[i] = -1;
    }
    // 1.创建socket
    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == serverFd)
    {
        printf("创建socket失败%m\n");
        return -1;
    }
    printf("创建socket成功\n");

    // 2.确定服务器协议地址簇
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // ip地址 注意字符串转网络字节序
    addr.sin_port = htons(9999);                   // 端口号 用10000左右的 注意大小端转换

    // 3.绑定（bind）
    int r = bind(serverFd, (struct sockaddr *)&addr, sizeof addr);
    if (-1 == r)
    {
        printf("绑定失败%m\n");
        close(serverFd);
        return -1;
    }
    printf("绑定成功\n");

    // 4.监听（listen）
    r = listen(serverFd, 100);
    if (-1 == r)
    {
        printf("监听失败%m\n");
        close(serverFd);
        return -1;
    }
    printf("监听成功\n");

    // 5.接受客户端连接（accept)
    struct sockaddr_in cAddr = {0};
    int len = sizeof cAddr;
    fd_set fds;
    int maxfd = (0 < serverFd) ? serverFd : 0;
    while (1)
    {
        // 服务器放进来，用来接收accept
        FD_ZERO(&fds);
        FD_SET(serverFd, &fds);
        // clientFd放进来，用来接收客户端通信
        for (int i = 0; i < MAX_CONNECT_NUM; i++)
        {
            if (-1 != clientFds[i])
            {
                FD_SET(clientFds[i], &fds);
                maxfd = (clientFds[i] < maxfd) ? maxfd : clientFds[i];
            }
        }

        //6.判断输入
        r = select(maxfd + 1, &fds, NULL, NULL, NULL);
        if (r > 0)
        {
            // 检查是否有客户端连接
            if (FD_ISSET(serverFd, &fds))
            {
                int newfd = accept(serverFd, (struct sockaddr *)&cAddr, &len);
                if (-1 == newfd)
                {
                    printf("接受客户端连接失败%m\n");
                }
                else
                {
                    printf("接受客户端连接成功 %d %s %u\n", newfd, inet_ntoa(cAddr.sin_addr), cAddr.sin_port);
                    // 循环放到fds里
                    for (int i = 0; i < MAX_CONNECT_NUM; i++)
                    {
                        if (-1 == clientFds[i])
                        {
                            clientFds[i] = newfd;
                            FD_SET(clientFds[i], &fds);
                            maxfd = (clientFds[i] < maxfd) ? maxfd : clientFds[i];
                            break;
                        }
                    }
                }
            }
            //检查是否有客户端通信
            for (int i = 0; i < MAX_CONNECT_NUM; i++)
            {
                if (-1 != clientFds[i])
                {
                    if (FD_ISSET(clientFds[i], &fds))
                    {
                        char buff[1024];
                        char temp[1024 + 10 + 4 + 1];
                        int len = recv(clientFds[i], buff, 1023, 0);
                        if (len > 0)
                        {
                            buff[len] = 0; // 添加字符串结束符号
                            printf("接受到来自%d的%d字节消息：%s\n", clientFds[i], len, buff);
                            // 转发
                            memset(temp, 0, 1024);
                            // snprintf(temp,sizeof temp, "%d>>%s", clientFds[i], buff);
                            sprintf(temp, "%d>>%s", clientFds[i], buff);
                            // 循环遍历逐一发送
                            for (int j = 0; j < MAX_CONNECT_NUM; j++)
                            {
                                if (-1 != clientFds[j])
                                    send(clientFds[j], temp, strlen(temp), 0);
                            }
                        }
                        else
                        {
                            printf("客户端%d断开连接\n", clientFds[i]);
                            clientFds[i] = -1;
                        }
                    }
                }
            }
        }
        else if (0 == r)
        {
            printf("没有动静\n");
            continue;
        }
        else
        {
            printf("错误:%m\n");
            hand(2);
        }
    } // end of while(1)

    return 0;
}