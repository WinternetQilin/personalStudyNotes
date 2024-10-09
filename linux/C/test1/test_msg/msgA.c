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
#include <fcntl.h>	//文件映射虚拟内存
#include <sys/mman.h>
#include <wait.h>
#include <signal.h> //SIGCHLD
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>

#define BUFSIZE 20

struct msgbuf{
    long type;
    char buff[BUFSIZE];
};

int main(int argc, char *argv[])
{
    //接收消息

    // 1.创建key		ftok
    key_t key = ftok(".", 'q');
    if (-1 == key)
    {
        printf("创建key失败%m\n");
        return -1;
    }
    printf("创建key成功\n");
    //2.创建消息队列
    int msgid = msgget(key,IPC_CREAT|0666);
    if (-1 == msgid)
    {
        printf("创建消息队列失败%m\n");
        return -1;
    }
    printf("创建消息队列成功\n");
    //接收消息
    int r;
    struct msgbuf msg;
    while(1)
    {
        memset(msg.buff,0,sizeof(msg.buff));
        r = msgrcv(msgid,&msg,sizeof(msg),1,IPC_NOWAIT);
        printf("%d,%s,%d\n",r,msg.buff,msg.type);
        sleep(1);
    }

    return 0;
}