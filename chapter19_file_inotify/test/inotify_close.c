#include <stdio.h>
#include <sys/inotify.h>
#include <unistd.h>
int main()
{
	printf("pid=%d\n", getpid());
	int fd = inotify_init();
	printf("fd = %d\n",fd);
	sleep(10);
	int ret = close(fd);
	printf("ret = %d\n", ret);
	sleep(10);
}
