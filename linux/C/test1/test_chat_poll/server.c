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
#define MAX_CONNECT_NUM 1024
struct pollfd fds[MAX_CONNECT_NUM];//放这里了，方便操作
int serverFd;
void hand(int s)
{
    if (2 == s)
    {
        // 7.断开连接
        for (int i = 0; i < MAX_CONNECT_NUM; i++)
        {
            if (-1 != fds[i].fd)
                close(fds[i].fd);
        }
        // close(serverFd);//serverfd也在fds里
        printf("服务器关闭\n");
        exit(1);
    }
}

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

    // 5.接受客户端连接（accept)
    struct sockaddr_in cAddr = {0};
    int len = sizeof cAddr;

    
    int curNum = 0; // 当前描述符号数量

    // 先把服务器fd放进来
    fds[curNum].fd = serverFd;
    fds[curNum].events = POLLIN;
    curNum++;

    while (1)
    {
        // 上来先监视
        r = poll(fds, curNum, 0);
        // 根据r进行操作
        if (-1 == r)
        {
            printf("poll 异常：%m\n");
            return -1;
        }
        else if (0 == r)
        {
            continue;
        }
        else
        {
            // 先检查服务器有没有动静
            if (fds[0].revents & POLLIN)
            {
                int cfd = accept(serverFd, (struct sockaddr *)&cAddr, &len);
                if (-1 == cfd)
                {
                    printf("接受客户端连接失败%m\n");
                }
                else
                {
                    printf("接受客户端连接成功 %d %s %u curNum:%d\n", cfd, inet_ntoa(cAddr.sin_addr), cAddr.sin_port, curNum);
                    // 放入fds
                    fds[curNum].fd = cfd;
                    fds[curNum].events = POLLIN;
                    curNum++;
                }
            }

            char buff[1024];
            // 再循环判断客户端的描述符号是否有动静
            for (int i = 1; i < curNum; i++)
            {
                if ((fds[i].fd != -1) && (fds[i].revents & POLLIN))
                {
                    // 有动静说明客户端发来消息
                    memset(buff, 0, 1024);
                    int len = recv(fds[i].fd, buff, 1023, 0);
                    if (len > 0)
                    {
                        printf("接收到%d 消息：%s\n", fds[i].fd, buff);
                    }
                    else
                    {
                        printf("%d 断开连接了\n", fds[i].fd);
                        fds[i].fd = -1;
                    }
                }
            }
        }
    } // end of while(1)

    return 0;
}