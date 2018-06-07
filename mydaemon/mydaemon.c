#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<time.h>


void mydaemon()
{
	int fd;

	//struct sigaction sa;
	//调用umask将文件模式创建屏蔽字设为0
	umask(0);

	 // 保证子进程不是一个进程组的组长进程
	pid_t pid = fork();//创建子进程
	if(pid < 0)
	{
		perror("fork");
	}
	else if(pid > 0)
	{
		exit(0);//父进程退出
	}
	
	if(setsid() == -1)
	{
		perror("setsid");//创建一个新的会话
	}

	/*sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flag = 0;

	if(sigaction(SIGCHID,&sa,NULL) < 0)
	{
		return;
	}
	*/
	signal(SIGCHLD,SIG_IGN);

	//禁止进程重新打开控制终端
	pid = fork();
	if(pid < 0)
	{
		perror("error");
	}
	else if(pid > 0)
	{
		exit(0);
	}


	if(chdir("/") < 0)//将当前工作目录更改为根目录
	{
		printf("chdir error\n");
		return;
	}
    // 关闭不需要的文件描述符,或者重定向到/dev/null
	close(0);
	fd = open("/dav/null",O_RDWR);
	dup2(fd,1);
	dup2(fd,2);

}
int main()
{
	time_t t;
	int fd,i;

	mydaemon();

	//往日志里循环打印当前的时间信息
	fd = open("./mydaemon.log",O_RDWR,0644);//创建并打开日志文件
	if(fd < 0)
	{
		perror("open error");//打开失败
	}

	for(i = 0;i < 3;i++)
	{
		t = time(0);
		char * buf = asctime(localtime(&t));//将时间信息转化为字符串
//		char *buf = "hahaha\n";
		write(fd,buf,strlen(buf));//往文件里写
		sleep(5);
    }
	close(fd);
	return 0;
}
