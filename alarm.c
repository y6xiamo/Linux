#include <stdio.h>
#include<unistd.h>
int main()
{
    int count = 15;
    alarm(1);
    for( ;1; count++)
    {
        printf("count = %d\n",count);
    }
    return 0;
}
