#include<stdio.h>
//sda
#include<string.h>

/*int main()
{
	FILE *fp =fopen("myfile","r");
	if(!fp)
	{
		printf("fopen error");
	}

	char buf[1024];
	const char * msg = "hello bit\n";

	while(1)
	{
		ssize_t s = fread(buf,1,strlen(msg),fp);
		if(s > 0)
		{
			buf[s] = 0;
			printf("%s",buf);
		}
		if(feof(fp))
		{
			break;
		}
	}
	fclose(fp);
	return 0;
}
*/
int main()
{
	const char* msg = "hello fwrite\n";
	fwrite(msg,strlen(msg),1,stdout);

	printf("hello printf\n");
	fprintf(stdout,"hello fprintf\n");
	return 0;

}
