#include <stdio.h>
#include<stdlib.h>
int main()
{
    int* ptr = NULL;
    ptr = (int*)malloc(10*sizeof(int));
    if(ptr != NULL)
    {
        int i = 0;
        for( ;i < 10;i++)
        {
            *(ptr + i) = 0;
        }
    }
    free(ptr);
    ptr = NULL;
    return 0;
}
