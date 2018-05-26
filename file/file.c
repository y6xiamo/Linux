#include<stdio.h>
#include<string.h>

int main()
{
    const char* msg1 = "hello fprintf\n";
	const char* msg2 = "hello fwrite\n";
	const char* msg3 = "hello writre\n";

	printf("%s",msg1);
	fwrite(msg2,strlen(msg2),1,stdout);
	write(1,msg3,strlen(msg3));

	fork();
	return 0;
}
