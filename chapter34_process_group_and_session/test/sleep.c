#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	printf("pid:%ld\n", (long)getpid());
	sleep(60);
}
