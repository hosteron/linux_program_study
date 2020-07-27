#define _POSIX_C_SOURCE 199309
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
void handler(int sig, siginfo_t *info, void *context)
{
		printf("recive sig:%d, pid = %ld\n", sig,(long)getpid());
}
int main()
{
		printf("%d, %d, %d,%d\n", getuid(), getgid(), getpid(), getpgrp());
		struct sigaction sa;
		sa.sa_sigaction = handler;
		sa.sa_flags = SA_SIGINFO;
		sigaction(SIGINT, &sa, NULL);
		pid_t pid = fork();
		if(pid == -1)
		{
				printf("fork()fail\n");
				return -1;
		}
		else if(pid == 0)
		{

				printf("child :%d exit\n", getpid());
				while(1)
					pause();
				raise(SIGSTOP);
				_exit(2);
		}
		else
		{
				printf("parent :%d exit\n", getpid());
				while(1)
					pause();
				sleep(2);
				int status;
				pid_t  p = waitpid(pid, &status, WUNTRACED);
				printf("parent wait %d, status:%d\n", p,status);
		}
		return 1;
}
