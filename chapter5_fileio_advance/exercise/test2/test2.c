#include <fcntl.h>
#include <sys/stat.h>
#include "tlpi_hdr.h"
int main(int argc ,char **argv)
{
	if(argc != 2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s filename\n", argv[0]);
	struct stat file_stat;
	if(stat(argv[1], &file_stat) < 0)
		errExit("%s do not exist", argv[1]);
	int fd = open(argv[1], O_CREAT|O_RDWR|O_APPEND, 0644);
	if(fd == -1)
		errExit("open");
	off_t cur_off = lseek(fd, 0, SEEK_CUR);
	printf("file off:%ld\n", cur_off);
	off_t off = lseek(fd, 0, SEEK_SET);
	printf("lseek_offset:%ld\n", (long)off);
	write(fd, "test", 4);
	close(fd);
	exit(EXIT_SUCCESS);
}
