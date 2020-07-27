#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>
int main()
{
	printf("hello world\n");
	int status;
	pid_t pid = wait(&status);
	printf("pid=%d, %s\n", pid, strerror(errno));
	_exit(0);
}
