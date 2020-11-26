#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("should %s filename\n", argv[0]);
		return -1;
	}

	int fd = open(argv[1],O_RDWR|O_CREAT|O_EXCL|O_CLOEXEC|O_EXCL, 0664);
	if(fd == -1)
	{
		printf("open %s fail, %s\n", argv[1], strerror(errno));
		return -1;
	}

	int i;
	char buf[4096] = {0};
	int cnt = 0;
	for(i = 0; i < 3 ; i++)
	{
		memset(buf, 'a'+i, sizeof(buf));
		write(fd , buf, sizeof(buf));
	}
	fsync(fd);
	close(fd);
	return 0;
}
