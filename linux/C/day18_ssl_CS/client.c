#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sys/select.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("请输入端口号\n");
        return -1;
    }
    printf("------start of createSocket------\n");
    int cFd = socket(AF_INET, SOCK_STREAM, 0);
    if (cFd < 0)
    {
        printf("createSocket失败%m\n");
        return -1;
    }
    printf("创建socket成功\n");

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));
    addr.sin_addr.s_addr = inet_addr("172.18.222.58");
    int r = connect(cFd, (struct sockaddr *)&addr, sizeof(addr));
    if (r < 0)
    {
        printf("connect失败%m\n");
        return -1;
    }
    printf("connect成功\n");
    printf("------end of createSocket------\n");

    // 发送数据
    {
        char data[1024] = {0};
        strcat(data, "qqCode=1261338615");
        int len = strlen(data);
        // 数据的长度转字符串
        char lenStr[100] = {0};
        sprintf(lenStr, "%d", len);

        char str[1024] = {0};
        strcat(str, "GET /index.html HTTP/1.1\n");
        // strcat(str, "Host: www.webxml.com.cn\n");
        strcat(str, "Content-Type: application/x-www-form-urlencoded\n");
        strcat(str, "Content-Length: ");
        strcat(str, lenStr);
        strcat(str, "\n\n");
        strcat(str, data);
        strcat(str, "\r\n\r\n");
        r = send(cFd, str, strlen(str), 0);
        if (r < 0)
        {
            printf("send失败%m\n");
            close(cFd);
            return -1;
        }
        printf("发送数据成功\n");
    }

    // 用select监听数据
    fd_set set;
    FD_ZERO(&set);
    FD_SET(cFd, &set);
    char buf[1024] = {0};
    int rlen = 0;
    while (1)
    {
        sleep(1);
        r = select(cFd + 1, &set, NULL, NULL, NULL);
        if (0 == r)
            continue;
        if (r < 0)
        {
            printf("select失败%m\n");
            close(cFd);
            return -1;
        }
        memset(buf, 0, sizeof(buf));
        rlen = recv(cFd, buf, sizeof(buf), 0);
        if (rlen > 0)
        {
            printf("接收%d数据成功\n", rlen);
            printf("%s\n", buf);
        }
    }

    return 0;
}
