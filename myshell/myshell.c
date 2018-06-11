#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<ctype.h>
#include<string.h>

char *my_arg[32];

void do_execute()
{

        pid_t id = fork();
		if(id < 0)
		{
			perror("fork");
			return;
		}
		else if(id == 0)//子进程做其他事
        {
			int i = 0;
			int flag = 0;
			//判断命令是否含输入输出重定向
			for( ;my_arg[i] != NULL;i++)
			{
				//输出重定向
				if(strcmp(my_arg[i],">") == 0)
				{
					flag =1;
					break;
				}
				//输入重定向
				if(strcmp(my_arg[i],"<") == 0)
				{
					flag = 2;
					break;

				}
			}
			//处理输出重定向
			if(flag == 1)
			{
				my_arg[i] = NULL;


				int oldfd = open(my_arg[i+1],O_WRONLY|O_CREAT,0777);
				if(oldfd < 0)
				{
					perror("open");


					exit(1);
				}
				close(1);
				int newfd = dup(oldfd);
				if(newfd < 0)
				{
					perror("dup");

					exit(1);
				}			
			}
			//处理输入重定向
			if(flag == 2)
			{

				my_arg[i] = NULL;
				int oldfd = open(my_arg[i+1],O_RDONLY,0644);
				if(oldfd < 0)
				{
					perror("open");
					exit(1);
				}
				close(0);
				int newfd = dup(oldfd);
				if(newfd < 0)
				{
					perror("dup");
					exit(1);
				}
				
			}

			execvp(my_arg[0],my_arg);		
        }

        else
        {   //父进程等子进程退出
             int status = 0;
             pid_t ret = waitpid(id,&status,0);
             if(ret>0)
             {
                    printf("sig: %d,exit code: %d\n",status&0x7F,(status>>8)&0xFF);
             } 
             else
             {
                    printf("waitpid running error\n");
             }
		}
	

}
void do_parse(char* cmd)
{

		 cmd[strlen(cmd)-1] = 0;

		 char *p = cmd;
		 int i = 1;
		 my_arg[0] = cmd;
		 while(*p)
		 {
			  if(isspace(*p))
			  {
				   *p = 0;
				   p++;

				   my_arg[i++] = p;
			  }
			  else
			  { 
				   p++;
		
			  }
		 }
		 my_arg[i] = NULL;
}

int main()
{
   char cmd[128];
   
   while(1)
   {
        printf("[myshell#] ");
        fgets(cmd,sizeof(cmd),stdin);
        do_parse(cmd);
		do_execute();
   }
    return 0;
}




                    




