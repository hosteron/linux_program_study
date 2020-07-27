#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int flag = 0;
void exit1()
{
		printf("parent exit\n");
		flag = 1;
}
int main()
{
		pid_t pid = fork();
		if(pid == -1)
		{
				printf("fork()fail\n");
				return -1;
		}
		else if(pid == 0)
		{
				printf("child pid = %d, parent=%d\n", getpid(), getppid());
				sleep(5);
				printf("ppid:%d\n", getppid());
				//pause();
		}
		atexit(exit1);
		exit(0);
}
