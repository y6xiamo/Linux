#include<stdio.h>
#include"add.h"
#include"sub.h"

int main()
{
	int a = 20;
	int b = 10;
	printf("add(%d,%d) = %d\n",a,b,add(a,b));

	printf("sub(%d,%d) = %d\n",a,b,sub(a,b));

	printf("mul(%d,%d) = %d\n",a,b,mul(a,b));

	printf("div(%d,%d) = %d\n",a,b,div(a,b));
	return 0;
}
