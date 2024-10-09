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
	// 2）两线程分别打开管道文件（注意文件打开方式，一读一写） open
	int fd = open(argv[1], O_WRONLY);
	if (-1 == fd)
	{
		printf("打开管道文件失败：%m\n");
		unlink(argv[1]);
		return -1;
	}
	printf("打开管道文件成功\n");
	// 3）数据传输	write
	char buff[256];
	while(1)
	{
		printf("输入要发送的内容：");
		scanf("%s",buff);
		int r = write(fd,buff,strlen(buff));
		printf("已发送 %d 字节数据\n",r);
		if (0 == strcmp(buff, "close"))
					break;
	}
	// 4）关闭管道 close
	close(fd);
    return 0;
}