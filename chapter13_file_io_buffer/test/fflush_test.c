#include <stdio.h>
int main()
{
	printf("%d\n", getpid());
	printf("hello world");
	//fclose(stdout);a
	sleep(6);
	printf("start to fflush stdin");
	fflush(stdin);
	char buf[32] = {0};
	fgets(buf, 32, stdin);
	//int a = 20;
	//scanf("%d", &a);
	printf("buf=%s\n", buf);
	sleep(20);
}
