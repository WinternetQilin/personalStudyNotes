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
#include <sys/msg.h>
#include <sys/sem.h>

union semun
{
    int val;               /* Value for SETVAL */
    struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* Array for GETALL, SETALL */
    struct seminfo *__buf; /* Buffer for IPC_INFO
                              (Linux-specific) */
}u;

int main(int argc, char *argv[])
{
    // 1.创建key		ftok
    key_t key = ftok(".", 's');
    if (-1 == key)
    {
        printf("创建key失败%m\n");
        return -1;
    }
    printf("创建key成功\n");

    // 2.获取信号量
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (-1 == semid)
    {
        printf("获取semid失败%m\n");
        return -1;
    }
    printf("获取semid成功\n");

    //3.使用信号量
    struct sembuf buf;
    buf.sem_num = 0;
    buf.sem_op = 2;
    buf.sem_flg=0;
    int n=0;
    while(1)
    {
        int r = semop(semid,&buf,1);
        if(-1==r)printf("semop failure\n");
        else printf("semop success\n");
        sleep(1);
    }

    return 0;
}