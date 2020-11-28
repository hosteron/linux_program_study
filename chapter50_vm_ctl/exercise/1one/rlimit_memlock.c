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
int main()
{
	//printf("RLIMIT_MEMLOCK=%ld\n", (long)sysconf(_S_RLIMIT_MEMLOCK));
	void *ptr = mmap(NULL, 64 * 1024 , PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if(ptr == MAP_FAILED)
	{
		printf("mmap fail, %s\n", strerror(errno));
		return -1;
	}

	int ret = mlock(ptr, 64*1024);
	if(ret )
	{
		printf("mloc1 fail, %s\n", strerror(errno));
		munmap(ptr, 64*1024);
		return -1;
	}


	void *ptr1 = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if(ptr1 == MAP_FAILED)
	{
		printf("mmap fail, %s\n", strerror(errno));
		return -1;
	}

	ret = mlock(ptr1, 4096);
	if(ret)
	{
		printf("mlock2 fail , %s\n" ,strerror(errno));
		//return -1;
		printf("munmap ptr\n");
		munmap(ptr, 8*4096);
		ret = mlock(ptr1, 4096);
		if(ret)
		{
			printf("mlock3 fail, %s ", strerror(errno));
			return -1;
		}
		else
		{
			printf("mlock3 success\n");
		}
	}
	else
	{
		printf("mlock2 success \n");
	}
	
}
