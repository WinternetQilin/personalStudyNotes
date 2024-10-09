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
#include <poll.h>
#include <sys/epoll.h>
#define MAX_CONNECT_NUM 1024

int serverFd;
int epfds;

void hand(int s)
{
    if (2 == s)
    {
        // 7.断开连接
        close(serverFd);
        printf("服务器关闭\n");
        exit(1);
    }
}
int clientfds[MAX_CONNECT_NUM] = {0}; // 转发用
int curNum = 0;
int main()
{
    signal(2, hand);

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

    // 创建epoll
    epfds = epoll_create(MAX_CONNECT_NUM);
    if (-1 == epfds)
    {
        printf("创建epfds失败：%m\n");
        close(serverFd);
        return -1;
    }
    printf("创建epfds成功\n");

    // 注册epoll
    struct epoll_event ev;                   // 注册的时候用
    struct epoll_event evs[MAX_CONNECT_NUM]; // 处理的时候用
    ev.events = EPOLLIN;
    ev.data.fd = serverFd;

    // 先把serverfd放入fds
    r = epoll_ctl(epfds, EPOLL_CTL_ADD, serverFd, &ev);
    if (-1 == r)
    {
        printf("serverfd放入epfds失败：%m\n");
        hand(2);
        return -1;
    }
    printf("serverfd放入epfds成功\n");

    // 5.接受客户端连接（accept)
    struct sockaddr_in cAddr = {0};
    int len = sizeof cAddr;
    int nfds = 0; // epoll_wait返回值数量
    while (1)
    {
        // 上来先等待
        nfds = epoll_wait(epfds, evs, MAX_CONNECT_NUM, 0);
        // 根据r进行操作
        if (-1 == nfds)
        {
            printf("epoll 异常：%m\n");
            hand(2);
            return -1;
        }
        else if (0 == nfds)
        {
            continue;
        }
        else
        {
            for (int i = 0; i < nfds; i++)
            {
                if (serverFd == evs[i].data.fd)
                {
                    // 服务器有动静，说明有新连接
                    int cfd = accept(serverFd, (struct sockaddr *)&cAddr, &len);
                    if (-1 == cfd)
                    {
                        printf("接受客户端连接失败%m\n");
                    }
                    else
                    {
                        printf("接受客户端连接成功 %d %s %u\n", cfd, inet_ntoa(cAddr.sin_addr), cAddr.sin_port);
                        // 放入epfds
                        ev.events = EPOLLIN;
                        ev.data.fd = cfd;
                        int ret = epoll_ctl(epfds, EPOLL_CTL_ADD, cfd, &ev);
                        if (-1 == ret)
                        {
                            printf("cfd放入epfds失败：%m\n");
                            continue;
                        }
                        printf("cfd放入epfds成功\n");
                        // 放入转发用的数组
                        clientfds[curNum++] = cfd;
                    }
                }
                else if (evs[i].events & EPOLLIN)
                {
                    // 存在的客户端有响应，说明有消息发送来
                    char buff[1024] = {0};
                    int len = recv(evs[i].data.fd, buff, 1023, 0);
                    if (len > 0)
                    {
                        printf("接收到%d 消息：%s\n", evs[i].data.fd, buff);
                    }
                    else
                    {
                        printf("%d 断开连接了\n", evs[i].data.fd);
                        // 解除绑定
                        epoll_ctl(epfds, EPOLL_CTL_DEL, evs[i].data.fd, NULL);
                        // 把对应的从clientfd删除
                        for (int i = 0; i < curNum; i++)
                        {
                            if (clientfds[i] == evs[i].data.fd)
                            {
                                clientfds[i] = -1;
                            }
                        }
                    }

                    // 转发
                    char temp[1024] = {0};
                    sprintf(temp, "%d 说：%s", evs[i].data.fd, buff);
                    for (int i = 0; i < curNum; i++)
                    {
                        if (clientfds[i] != -1)
                            send(clientfds[i], temp, 1024, 0);
                    }
                }
            }
        }
    } // end of while(1)

    return 0;
}