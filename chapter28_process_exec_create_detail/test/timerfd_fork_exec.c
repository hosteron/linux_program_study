#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
int main(int argc, char **argv)
{
		printf("parent pid = %d\n", getpid());
		int fd = timerfd_create(CLOCK_MONOTONIC,0);
		if(fd < 0 )
		{
				printf("create timer fail\n");
				return -1;
		}
		struct itimerspec value;
		value.it_interval.tv_sec = 2;
		value.it_interval.tv_nsec = 0;
		value.it_value.tv_sec = 1;
		value.it_value.tv_nsec = 0;
		timerfd_settime(fd, 0, &value, NULL);
		printf("timerfd = %d\n", fd);
		#if 0
		pid_t pid = fork();
		if(pid == -1)
		{
				printf("fork fail\n");
				exit(EXIT_FAILURE);
		}
		#else
		if(argv[1] == NULL)
		{
			printf ("argv 1 is NULL fail\n");
			exit(EXIT_FAILURE);
		}
		execl(argv[1], argv[1], "hello","world",NULL);
		#endif
		uint64_t t;
		while(1)
		{
				int ret  = 0;
				ret = read(fd, &t, sizeof(t));
				printf("pid=%d,read %d, %lu\n", getpid(),ret, t);
		}
}
