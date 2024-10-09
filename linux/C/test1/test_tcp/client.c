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

    // 4.通信
    char buff[1024];
    char temp[1024];
    while (1)
    {
        printf("请输入要发送的内容：");
        scanf("%s", buff);
        r = send(clientFd, buff, strlen(buff), 0);
        printf("发送%d字节数据到服务器\n",r);
        r=recv(clientFd,temp,1023,0);
        if (r > 0)
        {
            printf("服务器回复%d字节消息：%s\n", r, temp);
        }
    }

    return 0;
}