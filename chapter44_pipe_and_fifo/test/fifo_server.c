#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	int fd = open("/tmp/fifo_test", O_RDONLY);
	if(fd == -1)
	{
		printf("open /tmp/fifo_test fail\n");
		return -1;
	}
	printf("server open /tmp/fifo_test success, client connected here\n");
	sleep(10);
	printf("after sleep\n");
	char buf[32] = {0};
	while(1)
	{
		int num = 0;
		num = read(fd, buf, sizeof(buf));
		if(num == -1)
		{
			printf("read fail\n");
			return -1;
		}
		else if(num == 0)
		{
			printf("read end\n");
			break;
		}
		else
		{
			printf("read:%d->%s\n", num, buf);
		}
	}

	close(fd);
}
