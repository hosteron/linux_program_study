#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
int main(int argc ,char **argv)
{
	if(argc != 2)
	{
		printf("should %s filename\n", argv[0]);
		return -1;
	}
	int fd = open(argv[1], O_RDONLY|O_CLOEXEC);
	if(fd==-1)
	{
		printf("open fail, %s\n", strerror(errno));
		return -1;
	}
	void *ptr = mmap(NULL, 4096*3, PROT_READ, MAP_ANONYMOUS|MAP_SHARED, -1,0);
	if(ptr == MAP_FAILED)
	{
		close(fd);
		printf("mmap fail, %s\n\n", strerror(errno));
		return -1;
	}
	struct stat st;
	fstat(fd , &st);
	char *p = (char *)mmap(ptr, 4096, PROT_READ, MAP_FIXED|MAP_PRIVATE, fd, 4096*2);
	if(p == MAP_FAILED)
	{
		printf("mmap fail, %s\n\n", strerror(errno));
		munmap(ptr, 4096);
	close(fd);
		return -1;
	}
	char *p1 = (char *)mmap(ptr+4096*2, 4096, PROT_READ, MAP_FIXED|MAP_PRIVATE, fd, 0);
	if(p1 == MAP_FAILED)
	{
		printf("mmap fail, %s\n\n", strerror(errno));
		munmap(p, 4096);
	close(fd);
		return -1;
	}

	char *p2 = (char *)mmap(ptr+4096, 4096, PROT_READ, MAP_FIXED|MAP_PRIVATE, fd, 4096);
	if(p2 == MAP_FAILED)
	{
		printf("mmap fail, %s\n\n", strerror(errno));
		munmap(p, 4096);
		munmap(p1,4096);
	close(fd);
		return -1;
	}
	int i;
	for(i = 0;i < 3*4096;i++)
	{
		printf("%c", *(p+i));
	}
	printf("\n");
	close(fd);
	munmap(p, 4096*3);
}
