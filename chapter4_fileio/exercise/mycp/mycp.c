#include <fcntl.h>
#include "tlpi_hdr.h"
int main(int argc , char **argv)
{
	if(argc  != 3)
		usageErr("%s src dst\n", argv[0]);
	int fd_src = open(argv[1], O_RDONLY);
	if(fd_src == -1)
		errExit("open");
	int fd_dst = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC|O_APPEND, 0644);
	if(fd_dst == -1)
		errExit("open");
	int size = lseek(fd_src, 0, SEEK_END);
	if(size == -1)
		errExit("lseek");
	printf("size=%d\n", size);
	int num = 0;
	char buf[32] = {0};
	int readed = 0;
	lseek(fd_src, 0, SEEK_SET);
	while((num = read(fd_src, buf, sizeof(buf))) > 0)
	{
			
			write(fd_dst, buf, num);
	}
	
	close(fd_src);
	close(fd_dst);
}
