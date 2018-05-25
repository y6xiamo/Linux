#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int data = 10;

int main()
{
	pid_t pid = vfork();
	if(pid < 0)
	{
		perror("fork");
	}
	else if(pid == 0)//子进程
	{
		sleep(1);
		data = 20;
		printf("child data is %d\n",data);
		//exit(0);
		return 0;

	}
	else
	{
		printf("father data is %d\n",data);
	}
}
