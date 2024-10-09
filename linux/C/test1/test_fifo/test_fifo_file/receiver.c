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

int main(int argc, char *argv[])
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
	// 3）数据传输

	// 3.1 接收文件名
	char filename[256] = {0};
	r = read(fd, filename, 255);
	if (r > 0)
	{
		printf("成功接收文件名：%s\n", filename);
	}
	// 3.2 接收文件大小
	int filesize = 0;
	r = read(fd, &filesize, sizeof(int));
	if (4 == r)
	{
		printf("成功接收文件大小：%d\n", filesize);
	}
	// 3.3 循环接收文件内容
	//先创建目标文件
	int dstFd = open(filename,O_WRONLY | O_CREAT,0666);
	if(-1 == dstFd)
	{
		printf("创建文件失败：%m\n");
		close(fd);
		unlink(argv[1]);
		return -1;
	}
	printf("创建文件成功\n");
	//再接收
	int temp[1024] = {0};
	int cnt = 0;
	while (1)
	{
		r = read(fd, temp, 1024);
		if (r > 0)
		{
			cnt+=r;
			write(dstFd,temp,r);
			if (cnt >= filesize)
				break;
		}
	}
	close(dstFd);
	// 4）关闭管道 close
	close(fd);
	// 5）删除管道文件	unlink
	unlink(argv[1]);
	return 0;
}