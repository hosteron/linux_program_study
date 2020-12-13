#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "tlpi_hdr.h"
int main(int argc ,char **argv)
{
	int fd;
	char *addr;
	struct stat sb;
	if(argc != 2 || !strcmp("--help", argv[1]))
		usageErr("%s shm-name\n", argv[0]);
	
	fd = shm_open(argv[1], O_RDONLY, 0);
	if(fd == -1)
		errExit("shm_open");
	
	if(fstat(fd, &sb) == -1)
		errExit("fstat");
	
	addr = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if(addr == MAP_FAILED)
		errExit("mmap");
	
	if(close(fd) == -1)
		errExit("close");
	write(STDOUT_FILENO, addr, sb.st_size);
	printf("\n");
	exit(EXIT_SUCCESS);
	
}
