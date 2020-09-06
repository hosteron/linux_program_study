#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
int main()
{
	if(fork()!=0)
		_exit(0);
	if(setsid() == -1)
	{
			printf("setsid fail\n");
			exit(0);
	}
	#if 1
	int fd1 = open("/dev/pts/3", O_RDWR|O_NOCTTY);
	if(fd1 == -1)
	{
			perror("open1 tty fail\n");
			return -1;
	}
	printf("fd1:%d\n", fd1);
	//ioctl(fd1, TIOCNOTTY);
	#endif
	printf("PID=%ld,PGID=%ld, SID=%ld\n", (long)getpid(), (long)getpgrp(), (long)getsid(0));
	printf("12345\n");
	sleep(60);
	#if 0
	int a = 0    ;
	sleep(5);
	printf("a=%d\n", a);
	
	int ret = 0;
	char buf[32] = {0};
	while(ret = read(0, buf, sizeof(buf)) )
	{
	printf("ret = %d, read=%s\n", ret, buf);
	}
	sleep(40);
	int fd = open("/dev/tty", O_RDWR);
	if(fd == -1)
	{
			perror("open tty fail\n");
			return -1;
	}
	printf("open tty success\n");
	#endif
}
