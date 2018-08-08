#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int main()
{
    int fds[2];
    char buf[100];
    int len;

    if(pipe(fds) == -1)
    {
        perror("pipe");
        exit(1);
    }
    
    //从stdin读
    while(fgets(buf,100,stdin))
    {
        len = strlen(buf);
        if(write(fds[1],buf,len) != len)
        {
            perror("write");
            break;
        }
    }
    memset(buf,0x00,sizeof(buf));

    //从管道读
    if((len = read(fds[0],buf,100)) == -1)
    {
        perror("read");
 //       break;
    }

    //往stdout上写
    if(write(1,buf,len) != len)
    {
        perror("write");
//        break;
    }

}

