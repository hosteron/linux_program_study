#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include "tlpi_hdr.h"
int main(int argc , char **argv)
{
		int fd;
		struct iovec iov[3];
		struct stat myStruct;
		int x;
		#define STR_SIZE 100
		char str[STR_SIZE];
		ssize_t numRead, totRequired;
		if(argc != 2  || strcmp(argv[1], "--help") == 0)
			usageErr("%s file\n", argv[0]);
		fd = open(argv[1], O_RDONLY);
		if(fd == -1)
			errExit("open");
		off_t cur_off = lseek(fd, 0, SEEK_CUR);
		printf("cur_off:%ld\n", cur_off);
		totRequired = 0;
		iov[0].iov_base = &myStruct;
		iov[0].iov_len = sizeof(struct stat);
		totRequired += iov[0].iov_len;
		iov[1].iov_base = &x;
		iov[1].iov_len = sizeof(x);
		totRequired += iov[1].iov_len;
		iov[2].iov_base = str;
		iov[2].iov_len = STR_SIZE;
		totRequired += iov[2].iov_len;
		numRead = preadv(fd, iov, 3, 200);
		if(numRead == -1)
			errExit("readv");
		if(numRead < totRequired)
			printf("Read fewer bytes than required\n");
		cur_off =  lseek(fd, 0, SEEK_CUR);
		printf("after readv cur_offset:%ld\n", cur_off);
		printf("total bytes requested:%ld; bytes read:%ld\n", (long)totRequired, (long)numRead);
		exit(EXIT_SUCCESS);
}
