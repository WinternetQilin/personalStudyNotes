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

int main(int argc,char* argv[])
{
	// 1）创建管道文件（可以是第三个进程） mkfifo
	int r = mkfifo(argv[1], 0666);
	if (-1 == r)
	{
		printf("创建管道文件失败：%m\n");
		return -1;
	}
	printf("创建管道文件成功\n");
	// 2）两线程分别打开管道文件（注意文件打开方式，一读一写） open
	int fd = open(argv[1], O_RDONLY);
	if (-1 == fd)
	{
		printf("打开管道文件失败：%m\n");
		unlink(argv[1]);
		return -1;
	}
	printf("打开管道文件成功\n");
	// 3）数据传输	read
	char buff[256];
	int n=0;
	while(1)
	{
		int r=read(fd,buff,255);
		if(r>0)
		{
			buff[r]=0;
			printf("%d: %s\n",n++,buff);
            if (0 == strcmp(buff, "close"))
					break;
		}
	}
	// 4）关闭管道 close
	close(fd);
	// 5）删除管道文件	unlink
	unlink(argv[1]);
    return 0;
}