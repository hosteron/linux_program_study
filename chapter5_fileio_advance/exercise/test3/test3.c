#include <fcntl.h>
#include "tlpi_hdr.h"
int main(int argc, char **argv)
{
		if(argc !=3 && argc !=4)
			usageErr("%s filename numbytes [x]\n",argv[0]);
		int flags = 0;
		if(argc == 3)
			flags |= O_APPEND;
		int fd = open(argv[1], O_CREAT|O_RDWR|flags , 0644);
		if(fd == -1)
			errExit("open");
		if(fcntl(fd, F_GETFL) & O_APPEND)
			printf("O_APPEND\n");
		else
			printf("no O_APPEND\n");
		int size = atol(argv[2]);
		int i;
		if(argc == 3)
		{
			for(i = 0; i < size ; i++)
			{
					if(write(fd, "1", 1) == -1)
						errExit("write");
			}
		}
		else
		{
				for(i = 0; i < size ; i++)
				{
						lseek(fd, 0, SEEK_END);
						if(write(fd, "1", 1) == -1)
							errExit("write");
				}
		}
		close(fd);
		exit(EXIT_SUCCESS);
}
