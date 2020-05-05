#include <fcntl.h>
#include "tlpi_hdr.h"
int mydup(int oldfd)
{
		return fcntl(oldfd, F_DUPFD, 0);
}
int mydup2(int oldfd, int newfd)
{
		if(oldfd == newfd)
		{
				int flags = fcntl(oldfd, F_GETFL);
				if(flags == -1)
					errExit("oldfd do not valid");
				return oldfd;
		}
		
		int f =  fcntl(newfd, F_GETFL);
		if (f != -1)
			close(newfd);
		return fcntl(oldfd, F_DUPFD, newfd);
}
int main(int argc , char **argv)
{
		if(argc != 2 && argc !=3)
			usageErr("%s oldfd [newfd] \n", argv[0]);
		int oldfd = atoi(argv[1]);
		if(argc == 2)
		{
		int newfd = mydup(oldfd);
		if(newfd == -1)
			errExit("mydup");
		printf("newfd=%d\n", newfd);
		}
		else
		{
			int f = atoi(argv[2]);
			int newfd = mydup2(oldfd, f);
			if(newfd == -1)
				errExit("mydup2");
				printf("newfd:%d\n",newfd);
			}
		exit(EXIT_SUCCESS);
}
