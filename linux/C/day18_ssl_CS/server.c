#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

int createSocket(int port);
void acceptSocket(int sfd);
void saveLog(char *str);
void *http_thread(void *arg);
void get_http_command(char *buf, char *command);
int make_http_content(char *command, char **content);
// 获取文件内容
int getFileContent(char *filename, char **content);
// 获取content-type
char *getFileType(char *filename);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("请输入端口号\n");
        return -1;
    }
    int port = atoi(argv[1]);
    int sfd = createSocket(port);
    acceptSocket(sfd);
    return 0;
}
int createSocket(int port)
{
    printf("------start of socket------\n");
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1)
    {
        printf("createSocket中创建socket失败%m\n");
        saveLog("createSocket中创建socket失败\n");
        return -1;
    }
    printf("创建socket成功\n");
    int n = 1;
    int r = setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &n, sizeof(n));
    if (-1 == r)
    {
        printf("createSocket中setsockopt失败%m\n");
        saveLog("createSocket中setsockopt失败\n");
        return -1;
    }
    printf("设置socket成功\n");
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY; // 监听任意地址
    r = bind(sfd, (struct sockaddr *)&addr, sizeof(addr));
    if (-1 == r)
    {
        printf("createSocket中bind失败%m\n");
        saveLog("createSocket中bind失败\n");
        return -1;
    }
    printf("绑定成功\n");
    // 1.4 监听
    r = listen(sfd, 999999);
    if (-1 == r)
    {
        printf("createSocket中listen失败%m\n");
        saveLog("createSocket中listen失败\n");
        return -1;
    }
    printf("监听成功\n");
    printf("------end of socket------\n");
    return sfd;
}
void acceptSocket(int sfd)
{
    struct sockaddr_in addr = {0};
    socklen_t len = sizeof(addr);

    pthread_t thrd_t;
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    memset(&addr, 0, len);
    while (1)
    {
        int cfd = accept(sfd, (struct sockaddr *)&addr, &len);
        if (-1 == cfd)
        {
            printf("acceptSocket中accept失败%m\n");
            saveLog("acceptSocket中accept失败\n");
            continue;
        }
        printf("有客户端连上了服务器\n");
        int *temp = (int *)calloc(1, sizeof(int));
        *temp = cfd;
        pthread_create(&thrd_t, &attr, http_thread, temp);
    }
    pthread_detach(thrd_t);
}
void *http_thread(void *arg)
{
    if (arg == NULL)
        return NULL;
    printf("======http_thread线程启动======\n");

    int cfd = *(int *)arg;
    free((int *)arg);
    char buf[1024] = {0};
    int r = recv(cfd, buf, sizeof(buf), 0);
    if (r < 0)
    {
        printf("http_thread中recv失败%m\n");
        saveLog("http_thread中recv失败\n");
        return NULL;
    }
    printf(">>接收到客户端发送的数据：%s\n", buf);
    char command[1024] = {0};
    get_http_command(buf, command);
    printf(">>客户端请求的命令是：%s\n", command);
    char *content = NULL;
    int ilen = make_http_content(command, &content); // 根据请求制作响应
    if (ilen < 0)
    {
        printf("make_http_content失败%m\n");
        saveLog("make_http_content失败\n");
        free(content);
        return NULL;
    }
    printf(">>响应内容是：%s\n", content);
    send(cfd, content, ilen, 0);
    free(content);

    printf("======http_thread线程结束======\n");
    close(cfd);
    return NULL;
}
void get_http_command(char *buf, char *command)
{
    char *pend = buf;
    char *pstart = buf;
    while (*pstart)
    {
        if (*pstart == '/')
            break;
        pstart++;
    }
    pstart++;
    pend = strchr(buf, '\n');
    while (pend != pstart)
    {
        if (' ' == *pend)
            break;
        pend--;
    }
    strncpy(command, pstart, pend - pstart);
}
int make_http_content(char *command, char **content)
{
    int fileLen;
    char *file_buf;
    char headBuf[1024] = {0};
    if (0 == command[0])
    {
        fileLen = getFileContent("index.html", &file_buf);
    }
    else
    {
        fileLen = getFileContent(command, &file_buf);
    }
    if (fileLen <= 0)
    {
        printf("getFileContent中getFileContent失败%m\n");
        saveLog("getFileContent中getFileContent失败\n");
        return -1;
    }
    sprintf(headBuf, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %d\r\n\r\n", getFileType(command), fileLen);
    int headLen = strlen(headBuf);
    int tailLen = strlen("\r\n\r\n");
    int sumLen = headLen + fileLen + tailLen;
    *content = (char *)calloc(1, sumLen + 1);
    if(NULL == *content)
    {
        printf("make_http_content中calloc失败%m\n");
        saveLog("make_http_content中calloc失败\n");
        return -1;
    }
    char*temp = *content;
    memcpy(temp, headBuf, headLen);
    memcpy(temp + headLen, file_buf, fileLen);
    memcpy(temp + headLen + fileLen, "\r\n\r\n", tailLen);
    printf(">>响应内容是：%s\n", temp);
    return sumLen;
}
char *getFileType(char *filename)
{
    char ext[56] = {0};
    char *temp = filename;
    while (*temp)
    {
        if ('.' == *temp)
            break;
        temp++;
    }
    strncpy(ext, temp, sizeof(ext));
    if (0 == strcmp(ext, "html"))
    {
        return "image/bmp";
    }
    else if (0 == strcmp(ext, "jpg") || 0 == strcmp(ext, "png"))
    {
        return "image/jpeg";
    }
    else if (0 == strcmp(ext, "txt"))
    {
        return "text/plain";
    }
    return "text/html";
}
int getFileContent(char *filename, char **content)
{
    if (NULL == filename)
        return 0;
    FILE *fp = fopen(filename, "rb");
    if (NULL == fp)
    {
        printf("getFileContent中fopen失败%m\n");
        saveLog("getFileContent中fopen失败\n");
        return -1;
    }
    // 先获取文件大小
    fseek(fp, 0, SEEK_END);
    int fileLen = ftell(fp);
    rewind(fp); // 等同于fseek(fp, 0, SEEK_SET);
    *content = (char *)calloc(1, fileLen + 1);
    if (NULL == *content)
    {
        printf("getFileContent中calloc失败%m\n");
        saveLog("getFileContent中calloc失败\n");
        return -1;
    }
    fread(*content, fileLen, 1, fp);

    fclose(fp);
    return fileLen;
}
void saveLog(char *str)
{
    FILE *fp = fopen("log.txt", "a+");
    printf(str, fp);
    fclose(fp);
}