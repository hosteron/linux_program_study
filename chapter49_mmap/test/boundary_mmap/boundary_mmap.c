#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
int main(int argc ,char **argv)
{
	printf("pagesize=%d\n", sysconf(_SC_PAGESIZE));
	int fd = open(argv[1], O_RDWR);
	if(fd == -1)
	{
		printf("open %s fail\n", argv[1]);
		return -1;
	}

	struct stat st;
	fstat(fd, &st);
	printf("filezie = %d\n", st.st_size);
	char *ptr = (char *)mmap(NULL, /*st.st_size */8191, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(ptr == MAP_FAILED)
	{
		printf("mmap fail\n");;
		return -1;
	}

	int i;
	for(i = 0; i < 4096; i++)
	{
		printf("%d", *(ptr+i));
		if(i >= st.st_size)
			*(ptr+i) = 'a';
	}
	printf("\n");
	ftruncate(fd, 8192);
	printf("about to read index %d addr ...\n", i);
	printf("%d\n", *(ptr+i));
	*(ptr+i) = 'a';

	munmap(ptr, st.st_size);
}
