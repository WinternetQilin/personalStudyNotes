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
#include <signal.h> //SIGCHLD
int *p;
void hand()
{
    // 5.卸载共享内存	shmdt
    shmdt(p);
    printf("已卸载\n");
    exit(0);
    // 6.删除共享内存	shmctl
}
int main(int argc, char *argv[])
{
    signal(2,hand);
    // 1.创建key		ftok
    key_t key = ftok("./", 'm');
    if (-1 == key)
    {
        printf("创建key失败%m\n");
        return -1;
    }
    printf("创建key成功\n");
    // 2.创建共享内存	shmget
    int shmid = shmget(key, 4096, IPC_CREAT | 0666);
    if (-1 == shmid)
    {
        printf("创建共享内存失败%m\n");
        return -1;
    }
    printf("创建共享内存成功\n");
    // 3.挂载共享内存	shmat
    p = (int *)shmat(shmid, NULL, 0); // 0是默认权限，读写都可以
    if (-1 == *p)
    {
        printf("挂载共享内存失败%m\n");
        return -1;
    }
    printf("挂载共享内存成功\n");
    // 4.使用
    int n = 0;
    while (1)
    {
        *p = n++;
        sleep(1);
    }
    return 0;
}