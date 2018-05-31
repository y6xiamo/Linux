#include<stdio.h>
#include<unistd.h>

int main()
{
	pid_t pid = fork();
	if(pid < 0)
	{
		perror("fork");
		return 1;
	}
	else if(pid == 0)//子进程
	{
		while(1)
		{
			printf("child (%d)# I am running!\n",getpid());
			sleep(10);
		}
	}
	else//父进程
	{
		int i = 5;
		while(i)
		{
			printf("parent (%d)# I am going to dead...%d\n",getpid(),i--);
			sleep(1);
		}
	}
	return 0;
}
