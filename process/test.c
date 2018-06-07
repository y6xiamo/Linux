#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	pid_t pid = fork();//创建子进程
	if(pid < 0)
	{
		perror("fork error");
	}
	else if(pid == 0)//子进程
	{
		printf("I am child [%d] ,I am running.[%d] is my father!\n",getpid(),getppid());
		sleep(20);
	}
	else//父进程
	{
		printf("I am father [%d],I will die soon!\n",getpid());
		sleep(10);
		exit(EXIT_SUCCESS);
	}
	return 0;
}
