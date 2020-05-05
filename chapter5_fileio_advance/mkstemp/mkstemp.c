#include <fcntl.h>
#include "tlpi_hdr.h"
int main()
{
		int fd;
char template[] = "/tmp/somestringXXXXXX";
fd = mkstemp(template);
if(fd == -1)
	errExit("mkstemp");
printf("generated filename was : %s\n", template);
unlink(template);
sleep(30);
if(close(fd) == 1)
	errExit("close");
	exit(EXIT_SUCCESS);
}
