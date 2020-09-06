#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
int main()
{
	int fd  = open("/dev/pts/2", O_RDWR);
	if(fd == -1)
	{
		printf("open tty fail\n");
		return -1;
	}
	while(1)
	{
		int ret = 0;
		char buf[32] = {0};
		ret = read(fd, buf, sizeof(buf));
		printf("ret:%d, %s \n", ret, buf);
	}
}
