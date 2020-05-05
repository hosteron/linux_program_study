#include <fcntl.h>
#include "tlpi_hdr.h"
int main()
{
		int fd1 = open("/tmp/f1", O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
		int fd2 = dup(fd1);
		int fd3= open("/tmp/f1", O_RDWR);
		write(fd1, "Hello,", 6);
		write(fd2, "world", 6);
		lseek(fd2, 0, SEEK_SET);
		write(fd1, "HELLO,",6);
		write(fd3, "Gidday",6);
}
