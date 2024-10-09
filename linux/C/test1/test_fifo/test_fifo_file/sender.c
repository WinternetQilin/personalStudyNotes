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
	// 2）两线程分别打开管道文件（注意文件打开方式，一读一写） open
	int fd = open(argv[1], O_WRONLY);
	if (-1 == fd)
	{
		printf("打开管道文件失败：%m\n");
		unlink(argv[1]);
		return -1;
	}
	printf("打开管道文件成功\n");
	// 3）数据传输

	// 3.1发送文件名
	char filename[256] = {0};
	printf("请输入要发送的文件名："); // 也可以从argv[2]导入
	scanf("%s", filename);
	write(fd, filename, strlen(filename));
	// 3.2发送文件大小
	struct stat fs;
	stat(filename, &fs);
	write(fd, &(fs.st_size), sizeof(fs.st_size));
	// 3.3循环读取并发送文件内容
	// 先打开要发送的文件
	int srcFd = open(filename, O_RDONLY);
	if (-1 == srcFd)
	{
		printf("打开文件失败：%m\n");
		close(fd);
		return -1;
	}
	printf("打开文件成功\n");
	// 再发送
	char temp[1024] = {0};
	while (1)
	{
		int r = read(srcFd, temp, 1024);
		if (r > 0)
		{
			write(fd, temp, r);
		}
		else
		{
			break;
		}
	}
	close(srcFd);

	// 4）关闭管道 close
	close(fd);
	return 0;
}