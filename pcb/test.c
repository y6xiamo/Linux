#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	pid_t pid = fork();//创建子进程
    if(pid < 0)
	{
		perror("fork error");
		exit(1);
	}
	else if(pid == 0)//子进程
	{
        printf("child process [%d] is running!\n",getpid());
		sleep(5);
		exit(EXIT_SUCCESS);
	}
	else//父进程
	{
		printf("I am father!\n");
        sleep(20);
		printf("father process [%d] is running!\n",getpid());

	}
	return 0;
}
