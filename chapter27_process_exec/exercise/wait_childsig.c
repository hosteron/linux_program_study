#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
void handler(int sig)
{
		pid_t pid;
		int status;
		printf("sig %d, %s\n", sig, strsignal(sig));
		while((pid = wait(&status)) > 0)
		{
				printf("child %d exit, status=%d\n", pid, status);
		}
}
int main()
{
		struct sigaction  sa;
		sa.sa_handler = handler;
		sa.sa_flags = 0;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGCHLD, &sa, NULL);
		sigset_t  set, orig;
		sigaddset(&set, SIGCHLD);
		sigprocmask(SIG_BLOCK, &set, &orig);
		system("sleep 3");
		sigprocmask(SIG_SETMASK, &orig, NULL);
		#if 0
		pid_t  pid = fork();
		if(pid == -1)
		{
				printf("fork fail\n");
				exit(EXIT_FAILURE);
		}
		else if(pid == 0)
		{
				printf("child exit\n");
				_exit(1);
		}
		else
		{
				int status;
				pid_t child = waitpid(pid, &status, 0);
				if(child == -1 )
				{
						printf("waitpid fail %s\n", strerror(errno));
						exit(1);
				}
				printf("wait %d, status = %d\n", child, status);
				sigprocmask(SIG_SETMASK, &orig, NULL);
		}
		#endif
}
