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
#include <sys/select.h>

int clientFd;
void hand(int s)
{
    if (2 == s)
    {
        // 5.断开连接
        close(clientFd);
        printf("断开连接\n");
        exit(1);
    }
}

int main()
{
    signal(2, hand);
    // 1.创建socket
    clientFd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == clientFd)
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

    // 3.连接服务器
    int r = connect(clientFd, (struct sockaddr *)&addr, sizeof addr);
    if (-1 == r)
    {
        printf("连接服务器失败%m\n");
        close(clientFd);
        return -1;
    }
    printf("连接服务器成功\n");
#if 0
    // 4.通信
    char buff[1024];
    char temp[1024];
    while (1)
    {
        printf("请输入要发送的内容：");
        scanf("%s", buff);
        r = send(clientFd, buff, strlen(buff), 0);
        printf("发送%d字节数据到服务器\n", r);
        //这么写接收会导致C1可以正常显示转发，但是C2因为停留在scanf，还是阻塞状态，无法正常显示转发内容
        // memset(temp, 0, 1024);
        // r = recv(clientFd, temp, 1023, 0);
        // if (r > 0)
        //     printf("%s\n", temp);
    }
#else
    fd_set fds;

    char buff[1024];
    char temp[1024];
    while (1)
    {
        FD_ZERO(&fds);
        FD_SET(0, &fds);
        FD_SET(clientFd, &fds);
        r = select(clientFd + 1, &fds, NULL, NULL, NULL);
        if (r > 0)
        {
            if (FD_ISSET(0, &fds))
            {
                printf("请输入要发送的内容：");
                scanf("%s", buff);
                int len = send(clientFd, buff, strlen(buff), 0);
                printf("发送%d字节数据到服务器\n", len);
            }

            if (FD_ISSET(clientFd, &fds))
            {
                memset(temp, 0, 1024);
                int len = recv(clientFd, temp, 1023, 0);
                if (len > 0)
                {
                    printf("\n接收服务器转发：%s\n", temp);
                }
            }
        }
        else if (0 == r)
        {
            printf("没有动静\n");
        }
        else
        {
            printf("错误:%m\n");
        }
    }

#endif
    return 0;
}