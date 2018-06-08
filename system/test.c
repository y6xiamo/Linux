#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>

int system(const char* command)
{
	pid_t pid;
	int status;

	if(command == NULL)
	{
		return (1);//command为空，返回非0，一般为1
	}

	if((pid = fork) < 0)
	{
		status = -1;//fork失败，返回-1
	}
	else if(pid = 0)//子进程
	{
		exec("/bin/sh","sh","-c",command,(char*)0);
		_exit(127);//exec失败返回127，成功这个进程就没了，失败才返回
	}
	else//父进程
	{
		while(waitpid(pid,&status,0) < 0)
		{
			if(status!= EINTER)
			{
				status = -1;
				break;
			}

			
		}
	}
	return status;//成功，返回子进程的状态
}
int main()
{
	system("pwd");
	return 0;
}
