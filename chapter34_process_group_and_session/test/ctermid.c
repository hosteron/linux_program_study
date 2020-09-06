#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	if(fork() != 0 )
		exit(0);
	if(setsid() == -1)
	{
		printf("setsid fail\n");
		_exit(0);
	}
	printf("pid:%ld, pgid:%ld, sid:%ld\n", getpid(), getpgrp(),getsid(0));
	char buf[32] = {0};
	char *p = ctermid(buf);
	if(p)
		printf("tty:%s\n", buf);
	else
		printf("get control tty is null\n");
	sleep(60);
}
