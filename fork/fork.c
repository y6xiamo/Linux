#include<stdio.h>
#include<unistd.h>

int main()
{
	printf("Before:pid is %d\n",getpid());

	pid_t pid = fork();
	if(pid < 0)
	{
		perror("fork");
	}
	printf("After:pid is %d,fork return %d\n",getpid(),pid);
    sleep(1);
	return 0;
}
