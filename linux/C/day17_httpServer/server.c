#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
// 创建监听套接字
int create_listenfd();
// 处理请求
void handle_request(int clientfd);
int main()
{
    // 1.建立tcp连接
    int serverfd = create_listenfd();
    while (1)
    {
        // 2.接收客户端连接
        int clientfd = accept(serverfd, NULL, NULL);
        if (-1 == clientfd)
        {
            printf("accept失败%m\n");
            continue;
        }
        // 3.处理客户端发来的请求
        handle_request(clientfd);
    }
    return 0;
}
int create_listenfd()
{
    printf("------start of socket------\n");
    // 1.1 创建socket
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sfd)
    {
        printf("create_listenfd中创建socket失败%m\n");
        return -1;
    }
    printf("创建socket成功\n");
    // 1.2 设置socket
    int n = 1;
    int r = setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &n, sizeof(n));
    if (-1 == r)
    {
        printf("create_listenfd中setsockopt失败%m\n");
        return -1;
    }
    printf("设置socket成功\n");
    // 1.3 绑定
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    addr.sin_addr.s_addr = INADDR_ANY; // 监听任意地址
    r = bind(sfd, (struct sockaddr *)&addr, sizeof(addr));
    if (-1 == r)
    {
        printf("create_listenfd中bind失败%m\n");
        return -1;
    }
    printf("绑定成功\n");
    // 1.4 监听
    r = listen(sfd, 999999);
    if (-1 == r)
    {
        printf("create_listenfd中listen失败%m\n");
        return -1;
    }
    printf("监听成功\n");
    printf("------end of socket------\n");
    return sfd;
}
void handle_request(int clientfd)
{
    // 接收请求
    char buff[1024 * 1024] = {0};
    int nread = read(clientfd, buff, sizeof(buff)); // 也可以用recv
    if (-1 == nread)
    {
        printf("read失败%m\n");
        return;
    }
    // printf("%d: %s\n",nread,buff);
    // 解析请求
    // 获取文件名
    char filename[20] = {0};
    sscanf(buff, "GET /%s", filename);
    printf("文件名：%s\n", filename);
    // 根据文件名获取mime文件类
    // 用来放到响应头中，告诉浏览器返回的是什么类型的文件
    char *mime = NULL;
    if (strstr(filename, ".html"))
    {
        mime = "text/html"; // 文本类型
    }
    else if (strstr(filename, ".jpg"))
    {
        mime = "image/jpg"; // jpeg图片类型
    }
    // 制作响应
    char response[1024 * 1024] = {0};
    // 响应头
    //这里不直接用sprintf是因为sprintf会报warning
    const char* header = "HTTP/1.1 200 OK\r\nContent-Type:%s\r\n\r\n";
    snprintf(response, sizeof(response), header, mime);
    int header_len = strlen(response);
    // 响应体
    int fd = open(filename, O_RDONLY);
    if(-1 == fd)
    {
        printf("open %s 失败%m\n",filename);
        return;
    }
    int file_len = read(fd, response + header_len, sizeof(response) - header_len);

    // 发送响应
    write(clientfd, response, header_len + file_len);
    close(fd);
}