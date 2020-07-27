#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main()
{
		printf("parent pid = %d\n", getpid());
		//signal(SIGCHLD, SIG_IGN);
		
		
		pid_t  pid = fork();
		if(pid == -1)
		{
				printf("fork fail\n");
				return -1;
		}
		else if(pid == 0)
		{
			printf("children pid = %d\n", getpid());
			//raise(SIGSTOP);
			pid = fork();
			if(pid == 0)
			{
					printf("child３ pid = %d\n", getpid());
					pause();
			}
			_exit(0);
		}
		pid = fork();
			if(pid == 0)
			{
					printf("child2 pid = %d\n", getpid());
					pause();
			}
		int status;
		pid_t p = wait(&status);
		printf("wait :%d, status:%d, %s\n", p , status, strerror(errno));
}
