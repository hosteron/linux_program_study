#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
int main(int argc , char **argv)
{
	if(argc != 3)
	{
		printf("should %s filename cnt\n", argv[0]);
		return -1;
	}
	int cnt = atoi(argv[2]);
	int fd = open(argv[1], O_RDWR|O_CLOEXEC);
	if(fd == -1)
	{
		printf("open  %s fail, %s \n", argv[1], strerror(errno));
		return -1;
	}
	struct stat st;
	fstat(fd , &st);
	char *ptr = (char *)mmap(NULL, st.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd ,0);
	if(ptr == MAP_FAILED)
	{
		printf("mmap fail, %s\n", strerror(errno));
		close(fd);
		return -1;
	}
	char *buf = malloc(st.st_size);
	if(!buf)
	{
		close(fd);
		munmap(ptr, st.st_size);
		printf("malloc fail\n");
		return -1;
	}
	read(fd , buf, st.st_size);
	while(cnt-- >= 2)
	{
		int i;
		for(i = 0; i < st.st_size;i++)
		{
			printf("%c", *(ptr+i));
		}
		printf("\n");
		if(memcmp(ptr, buf,st.st_size))
		{
			printf("buffer is different\n");
			break;
		}
		memset(buf, 'b'+cnt%3, st.st_size);
		lseek(fd, 0, SEEK_SET);
		write(fd, buf,st.st_size);
	}
	close(fd);
	munmap(ptr, st.st_size);
	free(buf);

}
