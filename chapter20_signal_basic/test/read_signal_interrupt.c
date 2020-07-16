#include  <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
void  handler(int sig)
{
		printf("signal = %d\n", sig);
}
int main()
{
		int fd[2] = {0};
		pipe(fd);
		char buf[32] = {0};
		printf("read from pipe\n");
		printf("PID:%d\n", getpid());
		signal(SIGUSR1,handler);
		int ret = read(fd[0], buf, sizeof(buf));
		if(ret < 0)
		{
				printf("read fail\n");
				//perror("read fail");
		}
		else
		{
				printf("read = %d\n", ret);
		}
}
