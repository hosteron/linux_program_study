#include <fcntl.h>
#include "tlpi_hdr.h"
int main(int argc, char **argv)
{
	int opt;
	int a = 0;
	int flags = O_WRONLY;
	if(argc < 2 )
		usageErr("argc < 2 ");
	while((opt = getopt(argc, argv,"a")) != -1)
	{
			switch (opt){
					case 'a':
						flags |= O_APPEND;
						a = 1;
						break;
					default:
						cmdLineErr("unkown option");
						break;
			}
	}
	printf("a=%d, optind =%d\n", a, optind);
	if(a == 1)
	{
		if(optind >= argc)
			usageErr("must indicate filename");
	}
	else
	{
		if(optind >= argc)
			usageErr("must indicate filename");
	}
	int fd = open(argv[optind], O_WRONLY|O_NOFOLLOW);
	if(fd == -1)
	{
			printf("file %s do not exist\n", argv[optind]);
			fd = open(argv[optind], flags | O_CREAT,0755);
			if(fd == -1)
				errExit("open");
	}
	else
	{
			printf("file %s exist\n", argv[optind]);
			close(fd);
			fd = -1;
			if(!a)
				flags |= O_TRUNC;
			fd = open(argv[optind], flags);
			if(fd == -1)
				errExit("open");
	}
	int num = 0;
	char buf[32] = {0};
	while((num = read(STDIN_FILENO, buf, sizeof(buf))) > 0)
	{
			//printf("read :%s\n", buf);
			write(fd, buf, num);
	}
	close(fd);
	return 0;
}
