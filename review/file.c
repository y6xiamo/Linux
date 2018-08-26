#include <stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

#include<string.h>

int main()
{
    int fd = open("test",O_WRONLY | O_CREAT,0644);

    if(fd < 0)
    {
        perror("open");
        return 1;
    }
//    FILE* fp = fopen("test","w");
//    if(!fp)
//    {
//        printf("fopen error!\n");
//    }
    int count = 5;
    const char* msg = "hello world!\n";
    while(count--)
    {
        write(fd,msg,strlen(msg));
 //       fwrite(msg,strlen(msg),1,fp);
    }
//    fclose(fp);

    close(fd);
    return 0;

}
