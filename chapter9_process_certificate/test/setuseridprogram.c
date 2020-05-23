#include <stdio.h>
#include <sys/types.h>
       #include <unistd.h>
int main()
{
	printf("pid:%ld\n", getpid());
	
	sleep(30);
}
