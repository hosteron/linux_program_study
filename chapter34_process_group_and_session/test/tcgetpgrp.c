#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
int main()
{
		int fd = open("/dev/ttyFIQ0", O_RDWR);
		if(fd == -1)
		{
				perror("open");
				return -1;
		}
		pid_t pid = tcgetpgrp(fd);
		printf("cur pid:%ld,foregroud pid:%ld\n", (long)getpid(),(long)pid);
}
