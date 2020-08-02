#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	printf("pid=%d\n", getpid());
	pause();
}
