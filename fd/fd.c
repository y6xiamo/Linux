#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
    close(0);
	int fd = open("myfile",O_RDONLY);
	if(fd < 0)
	{
		perror("open");
		return 1;
	}
	printf("fd:%d\n",fd);
	fflush(stdout);

    close(fd);
	exit(0);
}
