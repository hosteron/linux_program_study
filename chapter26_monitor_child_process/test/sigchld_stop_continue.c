#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
void handler(int sig)
{
		printf("recieve sig:%d, %s\n", sig,strsignal(sig));
		int savedErrno  = errno;
		while(waitpid(-1, NULL, WNOHANG) > 0)
			continue;
		errno = savedErrno;
}
int main()
{
		printf("parent pid = %d\n", getpid());
		struct sigaction sa;
		sa.sa_handler = handler;
		sa.sa_flags = SA_NOCLDSTOP;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGCHLD, &sa, NULL);
		sigset_t set;
		sigaddset(&set, SIGCHLD);
		sigprocmask(SIG_SETMASK, &set, NULL);
		pid_t  pid = fork();
		if(pid == -1)
		{
				printf("fork fail\n");
				return -1;
		}
		else if(pid == 0)
		{
			printf("children pid = %d\n", getpid());
			raise(SIGSTOP);
			_exit(0);
		}
		sigemptyset(&set);
		while(1)
		{
				if(sigsuspend(&set) == -1 && errno != EINTR)
				{
						printf("sigsuspend fail\n");
						return -1;
				}
		}
		
		
}
