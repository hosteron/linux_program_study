#define _BSD_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <limits.h>
int main(int argc, char **argv)
{
	char *filename =NULL;
	
	if(argc == 2)
	{
		printf("file name = %s \n", argv[1]);
		filename = argv[1];
	}
	else if(argc == 1)
	{
		printf("filename = %s \n", "/dev/zero");
		filename = "/dev/zero";
	}
	else
	{
		printf("invalid input\n");
	}

	int fd = open(filename , O_RDWR);
	if(fd == -1)
	{
		printf("open fail, %s\n",strerror(errno));
		return -1;
	}

	char *ptr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd , 0);
	if(ptr == MAP_FAILED)
	{
		printf("mmap fail, %s \n", strerror(errno));
		return -1;
	}
	int i;
	for(i = 0; i < 4096; i ++)
	{
		printf("%c", *(ptr+i));
	}
	printf("\n");
	printf("about to change map\n");
	for(i = 0; i < 4096; i++)
	{
		*(ptr + i) = '+';
	}
	printf("after change ...\n");
	for(i = 0; i < 4096; i ++)
        {
                printf("%c", *(ptr+i));
        }
        printf("\n");
	int ret =madvise(ptr, 4096, MADV_DONTNEED);
	if(ret)
	{
		printf("madvise, %s \n", strerror(errno));
		return -1;
	}
	printf("after madvise ...\n");
	for(i = 0; i < 4096; i ++)
	        {
		                printf("%c", *(ptr+i));
				        }
					        printf("\n");
	

}
