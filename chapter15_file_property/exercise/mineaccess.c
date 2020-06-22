#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <sys/stat.h>
int main(int argc , char **argv)
{
	struct stat st;
	int ret = stat(argv[1], &st);
	if(ret!= 0)
	{
		perror("");
		return -1;
	}
	printf("program:UID=%d\n", getuid());
	if(argc != 3) return -1;
	if(!strcmp(argv[2], "R"))
	{
		if(st.st_mode & S_IRUSR)
		{
			return 0;
		}
		else
		{
				return -1;
		}
	}
	else if(!strcmp(argv[2], "W"))
	{
			if(st.st_mode &S_IWUSR)
			{
			return 0;
		}
		else
		{
				return -1;
		}
	}
	else if(!strcmp(argv[2], "X"))
	{
			if(st.st_mode &S_IXUSR)
			{
			return 0;
		}
		else
		{
				return -1;
		}
	}
	return -1;
}
