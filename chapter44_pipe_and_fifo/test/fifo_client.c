#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main(int argc ,char **argv)
{
        int fd = open("/tmp/fifo_test", O_WRONLY);
        if(fd == -1)
        {
                printf("open /tmp/fifo_test fail\n");
                return -1;
        }

        if(argc > 1)
	{
		write(fd, "hello world", strlen("hello world"));
	}
        close(fd);
}

