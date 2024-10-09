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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <poll.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <bits/pthreadtypes.h>
#include <aio.h>
#include <netdb.h>
#include <netinet/ip_icmp.h>
#include <termios.h>

// 写文件
//  void writeFile(int argc, char *argv[])
//  {
//  	if (argc < 2)
//  	{
//  		printf("请命令行输入文件名\n");
//  		exit(-1);
//  	}
//  	int fd = open(argv[1], O_WRONLY);
//  	if (-1 == fd)
//  	{
//  		// 错误信息会直接通过%m输出出来
//  		printf("打开%s失败：%m\n", argv[1]);
//  		fd = open(argv[1], O_WRONLY | O_CREAT, 0666);
//  		if (-1 == fd)
//  		{
//  			printf("创建%s失败：%m\n", argv[1]);
//  			exit(-1);
//  		}
//  		printf("创建文件成功\n");
//  	}
//  	printf("打开文件成功\n");
//  	char name[100];
//  	memset(name, 0, sizeof(name));
//  	char temp[20];
//  	memset(temp, 0, sizeof(temp));
//  	int age;
//  	double score;
//  	write(1, "请输入姓名：", strlen("请输入姓名：") + 1);
//  	read(0, name, 100);
//  	write(1, "请输入年龄：", strlen("请输入年龄：") + 1);
//  	read(0, temp, 20);
//  	age = atoi(temp);
//  	write(1, "请输入成绩：", strlen("请输入成绩：") + 1);
//  	bzero(temp, 0);
//  	read(0, temp, 20);
//  	score = atof(temp);
//  	char s[100];
//  	memset(s, 0, sizeof(s));
//  	sprintf(s, "%s同学今年%d岁了，考了%f分", name, age, score);
//  	// write(1,s,100);
//  	write(fd, s, 100);
//  	close(fd);
//  }

// 读文件
// void readFile(int argc, char *argv[])
// {
// 	if (argc < 2)
// 	{
// 		printf("请命令行输入文件名\n");
// 		exit(-1);
// 	}
// 	int fd = open(argv[1], O_RDONLY);
// 	if (-1 == fd)
// 	{
// 		printf("打开%s失败：%m\n", argv[1]);
// 		exit(-1);
// 	}
// 	printf("打开文件成功\n");
// 	char arr[100];
// 	read(fd, arr, 100);
// 	printf("%s\n", arr);
// 	close(fd);
// }

// 读取文件状态
// void fileStat(int argc, char *argv[])
// {
// 	if (argc < 2)
// 	{
// 		printf("请命令行输入文件名\n");
// 		exit(-1);
// 	}
// 	struct stat st;
// 	int ret = stat(argv[1], &st);
// 	if (-1 == ret)
// 	{
// 		printf("获取文件状态失败：%m\n");
// 		exit(-1);
// 	}
// 	printf("最终修改时间：%ld %ld\n", st.st_atim.tv_sec, st.st_atim.tv_nsec);
// 	struct tm *t = localtime(&st.st_atim);
// 	printf("%d-%d-%d %d:%d:%d 星期%d\n", t->tm_year, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, t->tm_wday);
// 	printf("文件类型%d\n", st.st_mode);
// 	if (st.st_mode & S_IFDIR)
// 	{
// 		printf("%s是个目录\n", argv[1]);
// 	}
// 	else
// 	{
// 		printf("%s是个文件\n", argv[1]);
// 	}
// 	printf("文件大小%ld\n", st.st_size);
// }

// 拷贝文件
// void fileCp(int argc, char *argv[])
// {
// 	if (argc < 3)
// 	{
// 		printf("请命令行输入文件名和拷贝后的文件名\n");
// 		exit(-1);
// 	}
// 	// 拷贝argv[1] 为 argv[2]
// 	int fdSrc = open(argv[1], O_RDONLY);
// 	if (-1 == fdSrc)
// 	{
// 		printf("打开待拷贝文件失败:%m");
// 		exit(-1);
// 	}
// 	int fdDst = open(argv[2], O_WRONLY | O_CREAT, 0666);
// 	if (-1 == fdDst)
// 	{
// 		printf("打开拷贝后的文件失败:%m");
// 		exit(-1);
// 	}
// 	// 循环读取并写入
// 	int r;
// 	char temp[1024];
// 	while (1)
// 	{
// 		r = read(fdSrc, temp, 1024);
// 		if (r <= 0)
// 			break;			   // 没读到就退出
// 		write(fdDst, temp, r); // 读到多少写多少
// 	}
// 	close(fdDst);
// 	close(fdSrc);
// 	printf("拷贝完毕\n");
// 	system("ls");
// }

// 移动文件
// void fileMv(int argc, char *argv[])
// {
// 	if (argc < 3)
// 	{
// 		printf("请命令行输入文件名和拷贝后的文件名\n");
// 		exit(-1);
// 	}
// 	struct stat st;
// 	int ret = stat(argv[2], &st);
// 	if (-1 == ret)
// 	{
// 		printf("获取文件状态失败：%m\n");
// 		exit(-1);
// 	}
// 	int fdSrc = open(argv[1], O_RDONLY);
// 	if (-1 == fdSrc)
// 	{
// 		printf("打开待拷贝文件失败:%m");
// 		exit(-1);
// 	}
// 	int fdDst;
// 	if (st.st_mode & S_IFDIR)
// 	{ // 是目录,移动，拷贝到指定目录后删除
// 		char dstName[256] = {0};
// 		sprintf(dstName, "%s/%s", argv[2], argv[1]);
// 		fdDst = open(dstName, O_WRONLY | O_CREAT, 0666);
// 		if (-1 == fdDst)
// 		{
// 			printf("目录if内\n");
// 			printf("打开拷贝后的文件失败:%m\n");
// 			exit(-1);
// 		}
// 	}
// 	else
// 	{
// 		// 不是目录，重命名，复制到当前目录后后删除
// 		printf("else内\n");
// 		fdDst = open(argv[2], O_WRONLY | O_CREAT, 0666);
// 		if (-1 == fdDst)
// 		{
// 			printf("打开拷贝后的文件失败:%m\n");
// 			exit(-1);
// 		}
// 	}
// 	// 循环读取并写入
// 	int r;
// 	char temp[1024];
// 	while (1)
// 	{
// 		r = read(fdSrc, temp, 1024);
// 		if (r <= 0)
// 			break;			   // 没读到就退出
// 		write(fdDst, temp, r); // 读到多少写多少
// 	}
// 	unlink(argv[1]); // 删除当前源
// 	close(fdDst);
// 	close(fdSrc);
// 	printf("移动完毕\n");
// 	system("ls");
// }

// 创建文件夹
// void makedir(int argc, char *argv[])
// {
// 	if (argc < 2)
// 	{
// 		printf("请输入要创建的目录名\n");
// 		exit(-1);
// 	}
// 	if (2 == argc)
// 	{
// 		printf("创建1个目录:%s\n", argv[1]);
// 		mkdir(argv[1], 0777);
// 	}
// 	else
// 	{
// 		printf("创建%d个目录\n", argc - 1);
// 		for (int i = 1; i < argc; i++)
// 		{
// 			mkdir(argv[i], 0777);
// 		}
// 	}
// 	printf("创建完毕\n");
// 	system("ls");
// }

// 遍历目录
// void traveldir(int argc, char *argv[])
// {
// 	if (argc < 2)
// 	{
// 		printf("请输入要遍历的目录名\n");
// 		exit(-1);
// 	}
// 	DIR *pDir = opendir(argv[1]);
// 	if (NULL == pDir)
// 	{
// 		printf("opendir %s 失败\n", argv[1]);
// 		perror(":");
// 		return;
// 	}
// 	printf("打开目录成功\n");
// 	int num = 0;
// 	struct dirent *pd = NULL;
// 	while (1)
// 	{
// 		pd = readdir(pDir);
// 		if (NULL == pd)
// 			break;
// 		num++;
// 		printf("这是 %s 里第 %d 个文件%s\n", argv[1], num, pd->d_name);
// 	}
// 	printf("遍历完成\n");
// 	closedir(pDir);
// }

// 递归遍历目录
// void DFS_traveldir(char *pathName)
// {
// 	char fileName[256] = {0};
// 	DIR *pDir = opendir(pathName);
// 	if (NULL == pDir)
// 	{
// 		printf("opendir %s 失败\n", pathName);
// 		perror(":");
// 		return;
// 	}
// 	// printf("打开目录成功\n");
// 	int num = 0;
// 	struct dirent *pd = NULL;
// 	while (1)
// 	{
// 		pd = readdir(pDir);
// 		if (NULL == pd)
// 			break;
// 		sprintf(fileName, "%s/%s", pathName, pd->d_name);
// 		if (DT_DIR == pd->d_type)
// 		{
// 			printf("---%d:%s\n", num, fileName);
// 			// 如果是目录就递归调用
// 			if (strcmp(".", pd->d_name) == 0 || strcmp("..", pd->d_name) == 0)
// 				continue;
// 			DFS_traveldir(fileName);
// 		}
// 		else
// 		{
// 			printf("+++%d:%s\n", num, fileName);
// 		}
// 		num++;
// 		// printf("这是 %s 里第 %d 个文件%s\n", argv[1], num, pd->d_name);
// 	}
// 	closedir(pDir);
// }

// 文件映射虚拟内存进行读写
// struct Student
// {
// 	char name[20];
// 	int age;
// 	double score;
// } stu = {"张三", 18, 60.1};
// void writeFilemmap()
// {
// 	int NUM = 1000;
// 	// 1.打开文件
// 	int fd = open("stu.dat", O_RDWR);
// 	if (-1 == fd)
// 	{
// 		// 错误信息会直接通过%m输出出来
// 		printf("打开%s失败：%m\n", "stu.dat");
// 		fd = open("stu.dat", O_WRONLY | O_CREAT, 0666);
// 		if (-1 == fd)
// 		{
// 			printf("创建%s失败:%m\n", "stu.dat");
// 			exit(-1);
// 		}
// 		printf("创建文件成功\n");
// 	}
// 	printf("打开文件成功\n");
// 	// 2.因为是要写入，所以要调整文件大小
// 	int r = ftruncate(fd, NUM * sizeof(stu));
// 	if (-1 == r)
// 	{
// 		printf("调整文件大小失败: %m\n");
// 		close(fd);
// 		return;
// 	}
// 	printf("调整文件大小成功\n");
// 	// 3.文件映射成虚拟内存
// 	struct Student *p = mmap(NULL, NUM * sizeof(stu), PROT_WRITE, MAP_SHARED, fd, 0);
// 	if (MAP_FAILED == p)
// 	{
// 		printf("映射文件失败: %m\n");
// 		close(fd);
// 		return;
// 	}
// 	printf("映射文件成功\n");
// 	struct timeval oldtime, newtime;
// 	gettimeofday(&oldtime, NULL);
// 	// 4.写入
// 	struct Student *pTemp = p;
// 	// 不用write了，直接内存操作
// 	for (int i = 0; i < NUM; i++)
// 	{
// 		memcpy(pTemp, &stu, sizeof(stu));
// 		pTemp++;
// 	}
// 	gettimeofday(&newtime, NULL);
// 	printf("%d %u\n", newtime.tv_sec - oldtime.tv_sec, newtime.tv_usec - oldtime.tv_usec);
// 	// 5.解除映射
// 	munmap(p, NUM * sizeof(stu));
// 	// 6.关闭文件
// 	close(fd);
// 	// 使用映射：0 41ms
// 	// 使用文件io：1 331627ms
// }
// void readFilemmap()
// {
// 	int NUM = 1000;
// 	// 1.打开文件
// 	int fd = open("stu.dat", O_RDONLY);
// 	if (-1 == fd)
// 	{
// 		// 错误信息会直接通过%m输出出来
// 		printf("打开%s失败：%m\n", "stu.dat");
// 		return;
// 	}
// 	printf("打开文件成功\n");
// 	// 2.读，不用调整大小
// 	// 3.文件映射成虚拟内存
// 	struct Student *p = mmap(NULL, NUM * sizeof(stu), PROT_READ, MAP_SHARED, fd, 0);
// 	if (MAP_FAILED == p)
// 	{
// 		printf("映射文件失败: %m\n");
// 		close(fd);
// 		return;
// 	}
// 	printf("映射文件成功\n");
// 	// 4.读
// 	printf("读：%s %d %lf\n", p->name, p->age, p->score);
// 	printf("读：%s %d %lf\n", (p + 1)->name, (p + 1)->age, (p + 1)->score);
// 	// 5.解除映射
// 	munmap(p, NUM * sizeof(stu));
// 	// 6.关闭文件
// 	close(fd);
// }

// exec进程
// void _exec(int argc, char *argv[])
// {
// 	printf("exec启动\n");
// 	execl(argv[1], "启动进程名%s", argv[1]);
// }

// fork创建子进程
// void _fork()
// {
// 	printf("当前进程id: %u\n", getpid());
// 	sleep(3);
// 	// 创建子进程
// 	int pid = fork();
// 	printf("被创建子进程id: %u\n", pid);
// 	if (pid) // 父进程
// 	{
// 		while (1)
// 			printf("我是父进程：%u %u\n", getpid(), getppid());
// 		sleep(1);
// 	}
// 	else
// 	{
// 		while (1)
// 			printf("---我是子进程: %u %u\n", getpid(), getppid());
// 		sleep(1);
// 	}
// }

// kill结束进程
// void _kill(int argc, char *argv[])
// {
// 	int pid = atoi(argv[1]);
// 	kill(pid, 9);
// 	printf("给%d进程发送信号9完毕\n", pid);
// }

// 父进程等待子进程结束后再继续
// void _wait()
// {
// 	printf("当前进程id: %u\n", getpid());
// 	sleep(3);
// 	// 创建子进程
// 	int pid = fork();
// 	printf("被创建子进程id: %u\n", pid);
// 	if (pid) // 父进程
// 	{
// 		for (int i = 0; i < 3; i++)
// 		{
// 			printf("我是父进程：%u %u\n", getpid(), getppid());
// 			sleep(1);
// 		}
// 		printf("父进程的事情干完了，正在等待子进程\n");
// 		int status = 114514;
// 		pid_t r = wait(&status);
// 		printf("子进程结束，父进程继续 %d %d\n", r, status);
// 	}
// 	else
// 	{
// 		for (int i = 0; i < 5; i++)
// 		{
// 			printf("---我是子进程: %u %u\n", getpid(), getppid());
// 			sleep(1);
// 		}
// 		printf("子进程结束\n");
// 		return 123;
// 	}
// }

// 守护进程
// void _daemon()
// {
// 	// 1）重设当前文件权限		umask
// 	umask(0);
// 	// 2）创建子进程			fork
// 	int ret = fork();
// 	if (ret < 0)
// 	{
// 		printf("创建进程失败%m\n");
// 		exit(-1);
// 	}
// 	// 3）让父进程结束
// 	if (ret > 0)
// 	{
// 		exit(0);
// 	}
// 	printf("pid:%d\n", getpid());
// 	// 4）创建新会话			setsid
// 	setsid();
// 	// 5）忽略一些信号			主要忽略SIGCHLD、SIGHUP
// 	signal(SIGCHLD, SIG_IGN);
// 	signal(SIGHUP, SIG_IGN);
// 	// 6）改变当前工作目录		chdir
// 	chdir("/");
// 	// 7）重定向文件描述符号	dup2	为了屏蔽终端干扰
// 	//	/dev/null 是黑洞设备，什么东西往这里一丢就没了
// 	int fd = open("/dev/null", O_RDWR);
// 	dup2(fd, 0);
// 	dup2(fd, 1);
// 	// 模拟守护进程工作
// 	while (1)
// 	{
// 		sleep(1); // 2852
// 	}
// }

// 使用匿名管道
// void _pipe()
// {
// 	// 1）准备仅有两个元素的描述符号数组
// 	int fd_arr[2];
// 	// 2）把数组变成管道
// 	pipe(fd_arr);
// 	// 3）创建子进程
// 	if (fork())
// 	{
// 		// 4）父进程 使用管道（读
// 		char buff[256];
// 		int n = 0;
// 		int r;
// 		while (1)
// 		{
// 			printf("父进程 读管道：");
// 			r = read(fd_arr[0], buff, 255);
// 			if (r > 0)
// 			{
// 				buff[r] = 0; // 添加结束符号
// 				n++;
// 				printf("%d: %s\n", n, buff);
// 				if (0 == strcmp(buff, "close"))
// 					break;
// 			}
// 		}
// 	}
// 	else
// 	{
// 		// 4）子进程 使用管道（写
// 		char buff[256];
// 		while (1)
// 		{
// 			bzero(buff, 256);
// 			scanf("%s", buff);
// 			write(fd_arr[1], buff, strlen(buff));
// 			if (0 == strcmp(buff, "close"))
// 				break;
// 		}
// 		printf("子进程结束\n");
// 	}
// 	// 5）关闭管道
// 	printf("关闭管道\n");
// 	close(fd_arr[0]);
// 	close(fd_arr[1]);
// 	printf("父进程结束\n");
// }

// 使用有名管道
// 见 test_fifo/mkfifo_read.c 和 test_fifo/mkfifo_write.c

// 使用有名管道传文件
// 见test_fifo/test_fifo_file/receiver 和 test_fifo/test_fifo_file/sender

// 信号
// void hand(int s)
// {
// 	printf("收到信号：%d\n", s);
// }
// void _signal()
// {
// 	signal(2, hand);
// 	int n = 0;
// 	while (1)
// 	{
// 		printf("%d\n", n++);
// 		sleep(1);
// 	}
// }

// shmctl删除共享内存
// void _shmctl()
// {
// 	// 1.创建key		ftok
// 	key_t key = ftok("./", 'm');
// 	if (-1 == key)
// 	{
// 		printf("创建key失败%m\n");
// 		return -1;
// 	}
// 	printf("创建key成功\n");
// 	// 2.创建共享内存	shmget
// 	int shmid = shmget(key, 4096, IPC_CREAT | 0666);
// 	if (-1 == shmid)
// 	{
// 		printf("创建共享内存失败%m\n");
// 		return -1;
// 	}
// 	printf("创建共享内存成功\n");
// #if 0
// 	//3.删除共享内存
// 	int r = shmctl(shmid,IPC_RMID,NULL);
// 	if (-1 == r)
//     {
//         printf("删除共享内存失败%m\n");
//         return -1;
//     }
//     printf("删除共享内存成功\n");
// #else
// 	// 获取共享内存状态
// 	struct shmid_ds ds = {0};
// 	int r = shmctl(shmid, IPC_STAT, &ds);
// 	if (-1 == r)
// 	{
// 		printf("获取共享内存失败%m\n");
// 		return -1;
// 	}
// 	printf("获取共享内存成功\n");
// 	printf("挂载数：%d\n", ds.shm_nattch);
// 	printf("创建进程id：%d\n", ds.shm_cpid);
// 	printf("大小：%d\n", ds.shm_segsz);
// #endif
// }

// select
void _select()
{
	fd_set fds;
	fd_set fdsOut;

	// FD_ZERO(&fds);
	FD_ZERO(&fdsOut);
	// FD_SET(0,&fds);
	FD_SET(1, &fdsOut);

	int r;
	char buff[1024];
	while (1)
	{
		FD_ZERO(&fds);
		FD_SET(0, &fds);
		r = select(2, &fds, &fdsOut, NULL, NULL);
		if (r > 0)
		{
			if (FD_ISSET(0, &fds))
			{
				printf("是0有动静\n");
				scanf("%s", buff);
			}

			if (FD_ISSET(1, &fdsOut))
			{
				printf("是1有动静\n");
				FD_CLR(1, &fdsOut);
				FD_ZERO(&fdsOut);
			}
			printf("r:%d\n", r);
		}
		else if (0 == r)
		{
			printf("没有动静\n");
		}
		else
		{
			printf("错误:%m\n");
		}
		// 处理完之后要清除
		//  FD_CLR(0,&fds);
		// 再重新放回去
		//  FD_SET(0,&fds);
	}
}

// poll
void _poll()
{
	// 1.创建结构体数组
	struct pollfd fds[200] = {0};
	// 2.设置要监视的描述符号
	int num = 0; // 已有的需要监视的fd数量
	fds[0].fd = 0;
	fds[0].events = POLLIN;
	num++; // 添加了一个就+1

	// 3.监视
	char buff[1024];
	while (1)
	{
		int r = poll(fds, num, 0);
		if (-1 == r)
		{
			printf("poll 异常：%m\n");
			return -1;
		}
		else if (0 == r)
		{
			continue;
		}
		else
		{
			// 4.根据返回值响应
			printf("poll 接收到了返回值\n");
			if (fds[0].events & POLLIN)
			{
				memset(buff, 0, 1024);
				scanf("%s", buff);
				printf("接收到：%s\n", buff);
			}
		}
	}
}

// epoll
void _epoll()
{
	// 1.创建epoll
	int epfd = epoll_create(100);
	if (-1 == epfd)
	{
		printf("创建epfd失败：%m\n");
		return;
	}
	printf("创建epfd成功\n");
	// 2.注册fd对应的事件
	struct epoll_event ev = {0};
	ev.events = EPOLLIN;
	ev.data.fd = 0;
	int r = epoll_ctl(epfd, EPOLL_CTL_ADD, 0, &ev);
	if (-1 == r)
	{
		printf("注册事件失败：%m\n");
		close(epfd);
		return;
	}
	printf("注册事件成功\n");

	// 3.等待
	struct epoll_event evs[100] = {0};
	while (1)
	{
		int ret = epoll_wait(epfd, evs, 100, 0);
		if (-1 == ret)
		{
			printf("epoll_wait失败：%m\n");
			close(epfd);
			return;
		}
		else if (0 == ret)
		{
			// printf("没动静\n");
		}
		else
		{
			char buff[1024] = {0};
			scanf("%s", buff);
			printf("有动静%d,%s\n", ret, buff);
		}
	}

	// 4.检查和事件响应
}

// pthread
void *func(void *arg)
{
	int n = 0;
	while (1)
	{
		printf("分支线程：%d\n", n--);
		sleep(2);
	}
}
void _pthread()
{
	int n = 0;
	pthread_t pt = 0;
	printf("pt: %u\n", pt);
	pthread_create(&pt, NULL, func, NULL);
	while (1)
	{
		printf("主线程：%d\n", n++);
		sleep(2);
	}
}

// 1.创建互斥量
pthread_mutex_t mutex;
int num = 0;
void f_mutex()
{
	for (size_t i = 0; i < 1000; i++)
	{
		// 3.使用互斥量前加锁
		pthread_mutex_lock(&mutex);
		num++;
		// 用完解锁
		pthread_mutex_unlock(&mutex);
	}
}
void _pthread_mutex()
{
	pthread_t t1, t2;

	/// 2.初始化互斥量
	pthread_mutex_init(&mutex, NULL);

	pthread_create(&t1, NULL, f_mutex, NULL);
	pthread_create(&t2, NULL, f_mutex, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	printf("%d\n", num);

	// 4.销毁互斥量
	pthread_mutex_destroy(&mutex);
}
//////////////////////////////////////////////////////////////////////////
// 互斥量与条件变量一起用
pthread_mutex_t mutex_1;
pthread_cond_t cond_1;
void f1()
{
	while (1)
	{
		pthread_mutex_lock(&mutex_1);
		pthread_cond_wait(&cond_1, &mutex_1);
		printf("===线程1===\n");
		sleep(1);
		pthread_mutex_unlock(&mutex_1);
	}
}
void f2()
{
	while (1)
	{
		pthread_mutex_lock(&mutex_1);
		pthread_cond_wait(&cond_1, &mutex_1);
		printf("---线程2---\n");
		sleep(1);
		pthread_mutex_unlock(&mutex_1);
	}
}
void f3()
{
	while (1)
	{
		pthread_mutex_lock(&mutex_1);
		pthread_cond_wait(&cond_1, &mutex_1);
		printf("+++线程3+++\n");
		sleep(1);
		pthread_mutex_unlock(&mutex_1);
	}
}
void _pthread_mutexAndCond()
{
	pthread_t t1, t2, t3;

	/// 2.初始化
	pthread_mutex_init(&mutex_1, NULL);
	pthread_cond_init(&cond_1, NULL);

	pthread_create(&t1, NULL, f1, NULL);
	pthread_create(&t2, NULL, f2, NULL);
	pthread_create(&t3, NULL, f3, NULL);

	while (1)
	{
		pthread_cond_signal(&cond_1);
		sleep(1);
	}

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);

	// 4.销毁
	pthread_mutex_destroy(&mutex_1);
	pthread_cond_destroy(&cond_1);
}

// aio异步操作
// 异步读
void _aio_read()
{
	// 1.准备缓冲区
	struct aiocb cb = {0};
	int fd = open("1.txt", O_RDONLY);
	if (-1 == fd)
	{
		printf("打开文件失败%m\n");
		return;
	}
	printf("打开文件成功\n");
	cb.aio_fildes = fd;						// 绑定文件描述符号
	cb.aio_buf = calloc(1024, sizeof(int)); // 开辟缓冲区
	cb.aio_nbytes = 1023;					// 要收的字节数

	// 2.异步操作(读)
	int r = aio_read(&cb);
	if (-1 == r)
	{
		printf("读取文件失败%m\n");
		return;
	}
	printf("读取文件成功\n");

	// 3.检查是否操作完毕
	// while (aio_error(&cb))
	// 	;

	// 用另一种方式
	struct aiocb *cb_list[2] = {0};
	cb_list[0] = &cb;
	// 里面可以放多个cb，比如把写也放进来
	r = aio_suspend(cb_list, 2, NULL); // 但是只要有一个结束了，它就返回了
	if (-1 == r)
	{
		printf("aio_suspend失败%m\n");
		return;
	}
	printf("aio_suspend结束\n");

	// 4.得到数据
	r = aio_return(&cb);
	if (r > 0)
	{
		printf("读到了%d字节数据:%s\n", r, cb.aio_buf);
	}
	// 5.收尾
	free(cb.aio_buf);
	close(fd);
}

// 异步写
void _aio_write()
{
	// 1.准备缓冲区
	struct aiocb cb = {0};
	int fd = open("2.txt", O_WRONLY | O_APPEND);
	if (-1 == fd)
	{
		printf("打开文件失败%m\n");
		return;
	}
	printf("打开文件成功\n");
	cb.aio_fildes = fd;								// 绑定文件描述符号
	cb.aio_buf = calloc(1024, sizeof(int));			// 开辟缓冲区
	strcpy(cb.aio_buf, "aio追加写：hello world\n"); // 将要写入的数据放入缓冲区
	cb.aio_nbytes = strlen(cb.aio_buf);				// 要写的字节数

	// 2.异步操作(写)
	int r = aio_write(&cb);
	if (-1 == r)
	{
		printf("写文件失败%m\n");
		return;
	}
	printf("写文件成功\n");

	// 3.检查是否操作完毕
	while (aio_error(&cb))
		;
	// 4.得到数据
	r = aio_return(&cb);
	if (r > 0)
	{
		printf("写入了%d字节数据\n", r);
	}
	// 5.收尾
	free(cb.aio_buf);
	close(fd);
}

// 实现ping
// 计算校验和 crc32(格式都是固定的，看一下就行了)
u_short get_cksum(u_short *icmp, int packSize)
{
	int nleft = packSize;
	int sum = 0;
	u_short *w = icmp;
	u_short ans = 0;
	while (nleft > 1)
	{
		sum += *w++;
		nleft -= 2;
	}
	if (nleft == 1)
	{
		*(unsigned char *)(&ans) = *(unsigned char *)w;
		sum += *(u_char *)w;
		sum += ans;
	}
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	ans = ~sum;
	return ans;
}

// 打包
// 包的大小
#define PACKET_SIZE 4096
// ICMP结构体大小
#define ICMP_DATA_SIZE 56
// 要发送的包
char sendPacket[PACKET_SIZE] = {0};
int pack(int curSend)
{
	struct icmp *picmp = (struct icmp *)sendPacket;
	picmp->icmp_type = ICMP_ECHO;
	picmp->icmp_code = 0;
	picmp->icmp_cksum = 0;
	picmp->icmp_id = getuid();
	picmp->icmp_seq = curSend;
	int packSize = 8 + ICMP_DATA_SIZE;
	struct timeval *tval = (struct timeval *)picmp->icmp_data;
	gettimeofday(tval, NULL); // 发送事件设置到附加数据
	picmp->icmp_cksum = get_cksum((u_short *)picmp, packSize);
	return packSize;
}

// 最大发包量
#define MAX_PACKETS 4
int curSend = 0; // 当前已发包量
// 发包
void send_packet(int sfd, struct sockaddr_in *dest_addr, int len)
{
	int packet_size;
	while (curSend <= MAX_PACKETS)
	{
		curSend++;
		packet_size = pack(curSend);
		int r = sendto(sfd, sendPacket, packet_size, 0, (struct sockaddr *)dest_addr, len);
		if (r < 0)
		{
			printf("第%d个sendto失败\n", curSend);
			continue;
		}
		printf("第%d个sendto成功\n", curSend);
	}
	sleep(1);
}
// 收包
// 要接收的包
char recvPacket[PACKET_SIZE] = {0};
int curRecv = 0; // 当前已收包量
struct sockaddr_in fromAddr = {0};
struct timeval recvtimeVal = {0};
void signalrmHand(int s)
{
	printf("======ping======\n");
	printf("%d个包发送成功，%d个包接收成功\n", curSend, curRecv);
	printf("================\n");
	exit(-1);
}

// 解包
// 计算时间差，结果赋值到第一个参数
void tv_sub(struct timeval *out, struct timeval *in)
{
	if ((out->tv_usec -= in->tv_usec) < 0)
	{
		--out->tv_usec;
		out->tv_usec += 1000000;
	}
	out->tv_sec -= in->tv_sec;
}
int unpack(int len, int id)
{
	// 获取ip地址头长度
	struct ip *ip = (struct ip *)recvPacket;
	int iphdrlen = ip->ip_hl << 2;
	// 往后偏移，得到smtp地址头
	char *buf = recvPacket;
	struct icmp *icmp = (struct icmp *)(buf + iphdrlen);
	len -= iphdrlen;
	if (len < 8)
	{
		printf("icmp包小于8\n");
		return -1;
	}
	struct timeval *tvsend;
	if ((ICMP_ECHOREPLY == icmp->icmp_type) && (id == icmp->icmp_id))
	{
		tvsend = (struct timeval *)(icmp->icmp_data);
		tv_sub(&recvtimeVal, tvsend);
		printf("%d byte from %s:icmp_seq:%u ttl=%.3f ms\n",
			   len, inet_ntoa(fromAddr.sin_addr),
			   icmp->icmp_seq, ip->ip_ttl,
			   recvtimeVal.tv_sec * 1000 + recvtimeVal.tv_usec / 1000);
	}
	else
	{
		return -1;
	}
	return 0;
}
void recv_packet(int sfd)
{
	// 注册信号放置收包超时
	signal(SIGALRM, signalrmHand);
	int r;
	int recvlen = 0;
	while (curRecv < curSend)
	{
		alarm(5); // 最大延迟时间
		r = recvfrom(sfd, recvPacket, PACKET_SIZE - 1, 0, (struct sockaddr *)&fromAddr, &recvlen);
		if (r < 0)
		{
			printf("recvfrom失败%m\n");
			continue;
		}
		gettimeofday(&recvtimeVal, NULL);
		if (-1 == unpack(r, getuid()))
			continue;
		curRecv++;
	}
}
void _ping(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("请输入要ping的ip地址\n");
		exit(-1);
	}

	// 1.创建socket
	struct protoent *protocal = getprotobyname("icmp");
	if (protocal == NULL)
	{
		printf("getprotobyname失败\n");
		exit(-1);
	}
	int sfd = socket(AF_INET, SOCK_RAW, protocal->p_proto);
	if (-1 == sfd)
	{
		printf("创建socket失败\n");
		exit(-1);
	}
	printf("创建socket成功\n");
	// 	2.设置套字节
	int size = 1024 * 50;
	setsockopt(sfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));
	if (-1 == sfd)
	{
		printf("设置套字节失败\n");
		exit(-1);
	}
	printf("设置套字节成功\n");
	// 	3.设置接收ip
	struct sockaddr_in dest_addr = {0};
	dest_addr.sin_family = AF_INET;
	in_addr_t iaddr = inet_addr(argv[1]);
	struct hostent *host = NULL;
	if (iaddr == INADDR_NONE)
	{
		// 说明不是一个ip
		// 检查是否是一个域名
		host = gethostbyname(argv[1]);
		if (host == NULL)
		{
			printf("错误的ip地址\n");
			exit(-1);
		}
		memcpy(&(dest_addr.sin_addr), host->h_addr_list[0], host->h_length);
		printf("域名解析成功:%s\n", inet_ntoa(dest_addr.sin_addr));
	}
	else
	{
		// 是一个ip地址
		dest_addr.sin_addr.s_addr = iaddr;
		printf("ip地址解析成功:%s\n", inet_ntoa(dest_addr.sin_addr));
	}

	// 	4.打包 5.发包
	send_packet(sfd, &dest_addr, sizeof(dest_addr));

	// 	6.收包 7.解包
	recv_packet(sfd);

	// 	8.统计并输出
}

// 简易线程池

// 任务类(也是任务池类)
struct job
{
	void *(*callback_func)(void *arg); // 任务函数
	void *arg;						   // 数据（函数参数）
	struct job *pNext;
};

// 线程池类
struct pthreadPool
{
	pthread_t *pthreads; // 数组方式存储所有线程id
	struct job *phead;	 // 任务池头节点
	struct job *ptail;	 // 任务池尾节点

	int curNum; // 当前线程数
	int maxNum; // 最大线程数限制

	// 线程同步
	pthread_mutex_t mutex;		   // 互斥量
	pthread_cond_t pool_empty;	   // 当前池空了
	pthread_cond_t pool_not_empty; // 当前池不空
	pthread_cond_t pool_not_full;  // 当前池不满
	pthread_cond_t pool_full;	   // 当前池满

	int job_nums;	 // 当前任务数
	int job_closed;	 // 是否关闭任务池
	int pool_closed; // 是否关闭线程池
};

// 任务函数
void *work(void *arg)
{
	char *str = (char *)arg;
	printf("``````````任务函数:%s开始\n", str);
	sleep(5); // 模拟任务
	printf("``````````任务函数:%s结束\n", str);
}

// 线程函数
void *pthread_func(void *arg)
{
	// 拿到线程池
	struct pthreadPool *pool = (struct pthreadPool *)arg;
	if (NULL == pool)
	{
		return NULL;
	}
	// 获取具体的任务
	struct job *pjob = NULL;

	while (1)
	{
		// 核心就是锁的操作
		// 加锁
		pthread_mutex_lock(&(pool->mutex));

		// 这里进行监督线程工作
		// 如果队列为空就阻塞，非空就继续执行
		while ((0 == pool->job_nums) && (0 == pool->job_closed))
		{
			printf("队列为空，阻塞\n");
			pthread_cond_wait(&(pool->pool_not_empty), &(pool->mutex));
		}
		// 如果线程池关闭了就结束线程
		if (pool->pool_closed)
		{
			printf("线程池关闭了，结束线程\n");
			pthread_mutex_unlock(&(pool->mutex));
			pthread_exit(NULL);
		}
		// 如果队列不为空就执行任务，当前任务数-1
		pool->job_nums--;
		pjob = pool->phead;
		if (0 == pool->job_nums)
		{
			pool->phead = pool->ptail = NULL;
			printf("任务队列为空，销毁线程函数\n");
			pthread_cond_signal(&(pool->pool_empty));
		}
		else
		{
			pool->phead = pjob->pNext;
		}
		// 如果任务队列不满，就添加新任务
		if (pool->job_nums < pool->maxNum)
		{
			printf("任务队列不满，添加新任务\n");
			pthread_cond_broadcast(&(pool->pool_not_full));
		}

		// 解锁
		pthread_mutex_unlock(&(pool->mutex));

		// 执行线程函数
		(*(pjob->callback_func))(pjob->arg);
		// 释放任务对象
		free(pjob);
		pjob = NULL;
	}
}

// 创建并初始化线程池
struct pthreadPool *pthreadPool_init(int pthread_nums, int max_nums)
{
	// 开内存
	struct pthreadPool *pool = (struct pthreadPool *)calloc(1, sizeof(struct pthreadPool));
	if (NULL == pool)
	{
		printf("pthreadPool_init:内存分配失败:%m\n");
		return NULL;
	}

	// 成员赋值
	pool->curNum = pthread_nums;
	pool->maxNum = max_nums;
	pool->job_nums = 0;						 // 当前0任务
	pool->job_closed = pool->job_closed = 0; // 非关闭状态
	pool->pthreads = (pthread_t *)calloc(pool->curNum, sizeof(pthread_t));
	pthread_mutex_init(&(pool->mutex), NULL);
	pthread_cond_init(&(pool->pool_empty), NULL);
	pthread_cond_init(&(pool->pool_not_empty), NULL);
	pthread_cond_init(&(pool->pool_not_full), NULL);
	pthread_cond_init(&(pool->pool_full), NULL);

	pool->phead = pool->ptail = NULL;

	// 创建线程，阻塞在这里
	for (int i = 0; i < pool->curNum; i++)
	{
		pthread_create(&(pool->pthreads[i]), NULL, pthread_func, (void *)pool);
	}

	// 返回
	return pool;
}

// 添加任务到线程池中
int add_job(struct pthreadPool *pool, void *(*callback_func)(void *arg), void *arg)
{
	if (NULL == pool || NULL == callback_func || NULL == arg)
	{
		printf("pthread_pool:参数错误\n");
		return -1;
	}
	pthread_mutex_lock(&(pool->mutex));
	// 阻塞
	while ((pool->job_nums >= pool->maxNum) && !(pool->job_closed || pool->pool_closed))
	{
		printf("任务队列已满，阻塞\n");
		pthread_cond_wait(&(pool->pool_not_full), &(pool->mutex));
	}
	// 关闭
	if (pool->job_closed || pool->pool_closed)
	{
		pthread_mutex_unlock(&(pool->mutex));
		return -1;
	}

	// 往任务池中添加任务
	struct job *pjob = (struct job *)calloc(1, sizeof(struct job));
	if (NULL == pjob)
	{
		printf("pthread_pool:内存分配失败:%m\n");
		pthread_mutex_unlock(&(pool->mutex));
		return -1;
	}
	pjob->callback_func = callback_func;
	pjob->arg = arg;
	pjob->pNext = NULL;
	if (NULL == pool->phead)
	{
		pool->phead = pool->ptail = pjob;
		// 发信号 队列非空
		pthread_cond_signal(&(pool->pool_not_full));
	}
	else
	{
		pool->ptail->pNext = pjob;
		pool->ptail = pjob;
	}
	pool->job_nums++;

	pthread_mutex_unlock(&(pool->mutex));
}

// 销毁线程池
int destory_pthreadPool(struct pthreadPool *pool)
{
	if (NULL == pool)
	{
		return -1;
	}
	printf("销毁线程池\n");
	// 释放id内存
	free(pool->pthreads);
	// 如果还有任务，也释放掉
	struct job *pjob = pool->phead;
	while (pjob)
	{
		pool->phead = pjob->pNext;

		free(pjob);

		pjob = pool->phead;
	}
	// 释放本身
	free(pool);
	return 0;
}

void pthread_pool()
{
	// 创建线程池
	struct pthreadPool *pool = pthreadPool_init(5, 20);
	// 添加任务
	add_job(pool, work, "第1个任务");
	add_job(pool, work, "第2个任务");
	add_job(pool, work, "第3个任务");
	add_job(pool, work, "第4个任务");
	add_job(pool, work, "第5个任务");
	add_job(pool, work, "第6个任务");
	add_job(pool, work, "第7个任务");
	add_job(pool, work, "第8个任务");
	add_job(pool, work, "第9个任务");
	add_job(pool, work, "第10个任务");
	add_job(pool, work, "第11个任务");
	add_job(pool, work, "第12个任务");
	add_job(pool, work, "第13个任务");
	add_job(pool, work, "第14个任务");
	add_job(pool, work, "第15个任务");
	add_job(pool, work, "第16个任务");
	add_job(pool, work, "第17个任务");
	add_job(pool, work, "第18个任务");
	add_job(pool, work, "第19个任务");
	add_job(pool, work, "第20个任务");

	sleep(20);
	destory_pthreadPool(pool);
}

// 复杂一点的线程池（封装严密一些的）

// 封装线程函数参数
struct tp_work_arg_s
{
	void *arg;
};
// 封装线程的工作函数
struct tp_work_s
{
	void *(*process_job)(void *arg);
};
// 为了方便使用起别名
typedef struct tp_work_arg_s tp_work_arg;
typedef struct tp_work_s tp_work;
// 线程类
struct tp_thread_info_s
{
	pthread_t id;  // 线程id
	int status;	   // 线程状态 0-空闲 1-工作中
	int need_exit; // 线程是否需要退出 1-需要退出 0-不需要退出

	pthread_mutex_t thread_lock; // 互斥线程锁
	pthread_cond_t thread_cond;	 // 条件变量

	tp_work *work;
	tp_work_arg *work_arg;

	struct tp_thread_info_s *next;
	struct tp_thread_info_s *prev;
};
// 线程池类
struct tp_thread_pool_s
{
	int max_thread_num;	 // 最大线程数
	int cur_thread_num;	 // 当前线程数
	int min_thread_num;	 // 最小线程数
	int idle_thread_num; // 空闲线程数

	pthread_mutex_t pool_lock;			  // 整个线程池的互斥锁
	pthread_t manager_id;				  // 线程池管理线程id
	struct tp_thread_info_s *thread_head; // 线程链表头
};
// 起别名
typedef struct tp_thread_info_s tp_thread_info;
typedef struct tp_thread_pool_s tp_thread_pool;
// 创建线程池中的线程
tp_thread_info *create_thread(int num)
{
	if (num <= 0)
		return NULL;
	// 双链表
	tp_thread_info *head;
	tp_thread_info *cur;
	tp_thread_info *prev;
	// 头节点
	head = (tp_thread_info *)calloc(1, sizeof(tp_thread_info));
	if (NULL == head)
	{
		printf("create_thread中calloc创建head线程失败:%m\n");
		return NULL;
	}
	num--;
	// 头节点之后的节点
	cur = head;
	prev = NULL;
	while (num--)
	{
		cur->prev = prev;
		cur->next = (tp_thread_info *)calloc(1, sizeof(tp_thread_info));
		prev = cur;
		cur = cur->next;
	}
	cur->next = NULL;
	return head;
}
// 管理线程的函数
void *tp_manager_thread(void *arg)
{
	// 空闲线程数过多，就删掉一些
	// 空闲线程过少，就创建一些
	int cur;	  // 当前线程数
	int idle;	  // 空闲线程数
	int min;	  // 最小线程数
	int exit_num; // 退出线程数
	tp_thread_pool *pool = (tp_thread_pool *)arg;
	// 统计三次
	int idle_arg[3] = {0};
	int averIdle = 0;
	while (1)
	{
		cur = pool->cur_thread_num;
		idle = pool->idle_thread_num;
		min = pool->min_thread_num;
		exit_num = 0;
		idle_arg[2] = idle;
		averIdle = (idle_arg[0] + idle_arg[1] + idle_arg[2]) / 3;
		printf("==========服务器当前状态==========");
		printf("总线程数:%d\n", cur);
		printf("空闲线程数:%d\n", idle);
		printf("平均空闲线程数:%d\n", averIdle);

		// 空闲线程过多
		if (averIdle > (cur / 2))
		{
			exit_num = cur / 5;
		}
		// 修正
		if (cur - exit_num < min)
		{
			exit_num = cur - min;
		}
		printf("退出线程数:%d\n", exit_num);
		// 循环销毁(跳过第一个，第一个不好操作)
		tp_thread_info *phead;
		for (phead = pool->thread_head->next; phead != NULL && exit_num > 1; phead = phead->next)
		{
			if (0 != phead->status)
			{
				pthread_mutex_unlock(&(phead->thread_lock));
				continue;
			}
			phead->need_exit = 1; // 标记为退出线程
			pthread_mutex_unlock(&(phead->thread_lock));
			exit_num--;
			pthread_cond_signal(&(phead->thread_cond));

			idle_arg[0] = idle_arg[1];
			idle_arg[1] = idle_arg[2];
		}
		sleep(5); // 每五秒检测一次
	} // end of while (1)
}
// 工作函数
void *myWork(void *arg)
{
	// tp_work_arg *a = (tp_work_arg *)arg;
	// int val = *(int *)a->arg;
	// printf("```````线程%ld开始执行任务%d\n", pthread_self(), val);
	printf("=========start of work==========\n");
	sleep(5); // 模拟耗时操作
	printf("=========end of work==========\n");
	// printf("```````线程%ld执行任务%d完成\n", pthread_self(), val);
}
// 初始化线程 返回0表示失败
int init_thread(tp_thread_pool *pool, tp_thread_info *thread)
{
	// 锁
	pthread_mutex_init(&(thread->thread_lock), NULL);
	pthread_cond_init(&(thread->thread_cond), NULL);

	int r = pthread_create(&(thread->id), NULL, myWork, pool);
	if (-1 == r)
	{
		printf("init_thread中创建线程失败:%m\n");
		return 0;
	}
	// 设置线程分离(自动释放)
	pthread_detach(thread->id);
	thread->status = 0;
	return 1;
}
// 初始化线程池
int init_thread_pool(tp_thread_pool *pool)
{
	tp_thread_info *phead = pool->thread_head;
	// 创建并初始化线程池中的线程对象
	while (phead != NULL)
	{
		if (init_thread(pool, phead))
		{
			printf("初始化线程成功：%lu\n", phead->id);
		}
		else
		{
			printf("初始化线程失败:%m\n");
			return 0;
		}
		phead = phead->next;
	}
	// 创建管理线程
	int ret = pthread_create(&(pool->manager_id), NULL, tp_manager_thread, pool);
	if (-1 == ret)
	{
		printf("创建管理线程失败:%m\n");
		return 0;
	}
	else
	{
		printf("创建管理线程成功:%lu\n", pool->manager_id);
	}
}
// 创建线程池
tp_thread_pool *creatd_thread_pool(int min, int max)
{
	tp_thread_pool *pool = (tp_thread_pool *)calloc(1, sizeof(tp_thread_pool));
	if (NULL == pool)
	{
		printf("calloc创建线程池失败:%m\n");
		return NULL;
	}
	pool->max_thread_num = max;
	pool->min_thread_num = min;
	pool->idle_thread_num = min;

	pthread_mutex_init(&(pool->pool_lock), NULL);

	if (pool->thread_head)
		free(pool->thread_head);
	// 开内存
	pool->thread_head = create_thread(pool->min_thread_num);
	if (NULL == pool->thread_head)
	{
		printf("create_thread创建线程失败:%m\n");
		free(pool);
		return NULL;
	}
	// 初始化线程池
	init_thread_pool(pool);

	return pool;
}
// 通知管理线程增加一个线程
tp_thread_info *tp_add_pthread(tp_thread_pool *pool)
{
	// 加一个线程到线程链表的末尾
	if (pool->cur_thread_num >= pool->max_thread_num)
	{
		printf("线程池中线程数达到最大值，无法再增加线程\n");
		return NULL;
	}
	tp_thread_info *pnew = (tp_thread_info *)calloc(1, sizeof(tp_thread_info));
	tp_thread_info *phead = pool->thread_head;
	while (phead->next != NULL)
	{
		phead = phead->next;
	}
	phead->next = pnew;
	pnew->prev = phead;
	pnew->next = NULL;
	pnew->status = 0;
	pnew->need_exit = 0;
	pnew->work = NULL;
	pnew->work_arg = NULL;
	pthread_mutex_init(&(pnew->thread_lock), NULL);
	pthread_cond_init(&(pnew->thread_cond), NULL);
	pool->cur_thread_num++;
	int r = pthread_create(&(pnew->id), NULL, myWork, pool);
	if (-1 == r)
	{
		printf("tp_add_pthread创建线程失败:%m\n");
		free(pnew);
		return NULL;
	}
	pthread_detach(pnew->id);
	pool->idle_thread_num++;
	return pnew;
}
// 向线程池中添加任务
int tp_add_job(tp_thread_pool *pool, tp_work *worker, tp_work_arg *arg)
{
	// 去线程池中找空闲线程，把任务分配给空闲线程并执行任务
	tp_thread_info *phead;
	tp_thread_info *pnew;
	while (1)
	{
		for (phead = pool->thread_head; phead != NULL; phead = phead->next)
		{
			if (0 == phead->status)
			{
				printf("找到空闲线程%lu\n", phead->id);
				// 设置为非空闲状态
				phead->status = 1;
				pool->idle_thread_num--;
				pthread_mutex_unlock(&(phead->thread_lock));
				phead->work = worker;
				phead->work_arg = arg;
				// 唤醒该线程
				pthread_cond_signal(&(phead->thread_cond));
			}
		} // end of for(phead=pool->thread_head;phead!=NULL;phead=phead->next)

		// 到这里说明没有空闲线程，就需要新增线程
		// 这里创建新线程并开内存，在监督线程启动
		pthread_mutex_lock(&(pool->pool_lock));
		pnew = tp_add_pthread(pool);
		if (pnew)
		{
			pnew->work = worker;
			pnew->work_arg = arg;
			pthread_cond_signal(&(pnew->thread_cond));
			pthread_mutex_unlock(&(pool->pool_lock));
			return 1;
		}
		// 没创建成功就解锁，进行新一轮循环
		pthread_mutex_unlock(&(pool->pool_lock));
	}
	return 1;
}

void pthread_pool_plus()
{
	int working[10] = {0};
	// 1.创建线程池
	tp_thread_pool *pool = creatd_thread_pool(3, 20);
	// 2.创建任务池
	tp_work *worker = (tp_work *)calloc(1, sizeof(tp_work));
	worker->process_job = myWork;
	for (int i = 0; i < 10; i++)
	{
		tp_work_arg *arg = (tp_work_arg *)calloc(1, sizeof(tp_work_arg));
		working[i] = i + 60;
		arg->arg = (void *)&(working[i]);
		tp_add_job(pool, worker, arg);
	}
	sleep(100);
}

// 串口信息查看
void _uart()
{
	int fd = open("/dev/ttyS0", O_RDONLY);
	if (fd < 0)
	{
		printf("open error\n");
		return;
	}
	struct termios tio = {0};
	int r = tcgetattr(fd, &tio);
	if (r < 0)
	{
		printf("tcgetattr error\n");
		return;
	}
	speed_t bps = cfgetispeed(&tio);
	switch (bps)
	{
	case B0:
		printf("波特率为B0\n");
		break;
	case B50:
		printf("B50\n");
		break;
	case B75:
		printf("B75\n");
		break;
	case B110:
		printf("B110\n");
		break;
	case B134:
		printf("B134\n");
		break;
	case B150:
		printf("B150\n");
		break;
	case B200:
		printf("B200\n");
		break;
	case B300:
		printf("B300\n");
		break;
	case B600:
		printf("B600\n");
		break;
	case B1200:
		printf("B1200\n");
		break;
	case B1800:
		printf("B1800\n");
		break;
	case B2400:
		printf("B2400\n");
		break;
	case B4800:
		printf("B4800\n");
		break;
	case B9600:
		printf("B9600\n");
		break;
	case B19200:
		printf("B19200\n");
		break;
	case B38400:
		printf("B38400\n");
		break;
	case B57600:
		printf("B57600\n");
		break;
	case B115200:
		printf("B115200\n");
		break;
	case B230400:
		printf("B230400\n");
		break;
	}

	if(tio.c_cflag & CS5)
	{
		printf("数据位为5个\n");
	}
	else if(tio.c_cflag & CS6)
	{
		printf("数据位为6个\n");
	}
	else if(tio.c_cflag & CS7)
	{
		printf("数据位为7个\n");
	}
	else if(tio.c_cflag & CS8)
	{
		printf("数据位为8个\n");
	}
	else
	{
		printf("数据位%d\n",tio.c_cflag);
	}

	close(fd);
}

int main(int argc, char *argv[])
{

	// readFile(argc,argv);
	// fileStat(argc,argv);
	// fileCp(argc,argv);
	// fileMv(argc, argv);
	// makedir(argc, argv);
	// traveldir(argc, argv);
	// if (argc < 2)
	// {
	// 	printf("请输入要遍历的目录名\n");
	// 	exit(-1);
	// }
	// DFS_traveldir(argv[1]);
	// printf("遍历完成\n");
	// writeFilemmap();
	// readFilemmap();
	// _exec(argc,argv);
	// _fork();
	// _kill(argc,argv);
	// _wait();
	// _daemon();
	// _pipe();

	// _signal();
	// _shmctl();
	// _select();
	// _poll();
	// _epoll();
	// _pthread();
	// _pthread_mutex();
	// _pthread_mutexAndCond();
	// _pthread_rwlock();
	// _aio_read();
	// _aio_write();
	// _ping(argc, argv);
	// pthread_pool();
	// pthread_pool_plus();
	_uart();
	return 0;
}
