#include<stdio.h>
#include<stdlib.h>
int main(int argc,char* argv[])
{
	char buf[128];
	FILE* fp = popen("ls -l","w");
    if(fp == NULL)
	{
		perror("popen");
		exit(1);
	}
	while(fgets(buf,sizeof(buf),fp))
	{
		printf("%s",buf);
	}
	pclose(fp);
	return 0;
}
