#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
	if(argc != 3)
	{
		printf("should %s src dst\n", argv[0]);
		return -1;
	}
	int fd = open(argv[1], O_RDONLY);
	if(fd == -1)
	{
		printf("open %s fail, %s\n", argv[1],strerror(errno));
		return -1;
	}
	struct stat st;
	fstat(fd, &st);
	char *psrc = (char *)mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if(!psrc)
	{
		printf("mmap fail, %s\n", strerror(errno));
		return -1;
	}
	close(fd);
	fd = open(argv[2], O_RDWR|O_TRUNC|O_CLOEXEC);
	if(fd == -1 && errno != ENOENT)
	{
		printf("open %s fail, %s\n", argv[2],strerror(errno));
		munmap(psrc, st.st_size);
		return -1;
	}
	else if(fd == -1)
	{
		fd = open(argv[2], O_RDWR|O_CREAT|O_EXCL|O_CLOEXEC, 0664);
		if(fd == -1)
		{
			
		printf("open %s fail, %s\n", argv[2],strerror(errno));
			munmap(psrc, st.st_size);
			return -1;
		}
	}
	ftruncate(fd,  st.st_size);
	char *pdst = (char *)mmap(NULL, st.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	memcpy(pdst, psrc, st.st_size);
	msync(pdst, st.st_size, MS_SYNC);
	close(fd);
	munmap(psrc, st.st_size);
	munmap(pdst, st.st_size);
}
