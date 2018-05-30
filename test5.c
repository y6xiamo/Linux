#include <stdio.h>
#define row 3
#define col 3
int find(int arr[row][col],int size,int to_find)
{
    if(arr == NULL)
    {
        return 0;
    }
    if(size <= 0)
    {
        return 0;
    }
    int i = 0;
    int j = col - 1;
    while(i <= row && j >= 0)
    {
        if(to_find < arr[i][j])
        {
            j--;
        }
        else if(to_find > arr[i][j])
        {
            i++;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}
int main()
{
    int arr[row][col] = {{1,2,3},
                     {5,6,7},
                     {8,9,10}};
    int size = sizeof(arr)/sizeof(arr[0][0]);
    int to_find = 16;
    int ret = find(arr,size,to_find);
    if(ret == 1)
    {
        printf("找到了该元素\n");
    }
    else
    {
        printf("该元素不存在\n");
    }
    return 0;

}

