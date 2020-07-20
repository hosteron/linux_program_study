#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
int main(int argc,  char **argv)
{
	if(argc != 3)
	{
		printf("argc != 3 error\n");
		return -1;
	}
	printf("pid=%d\n", getpid());
	kill(atoi(argv[1]), atoi(argv[2]));
}
