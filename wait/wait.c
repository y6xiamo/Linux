#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
	pid_t pid = fork();
	if(pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if(pid == 0)
	{
		printf("pid: %d,ppid: %d\n",getpid(),getppid());
		sleep(20);
		exit(10);
	}
	else
	{
		int status;
		int ret = wait(&status);
	    if(ret > 0 && (status & 0x7F) == 0)
		{
			printf("child exit code: %d\n",(status>>8) & 0xFF);
		}
		else if(ret > 0)
		{
			printf("sig code: %d\n",status & 0x7F);
		}
	}
	return 0;
}
