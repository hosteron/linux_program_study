#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
void handler(int sig)
{
	printf("recieve signal :%d\n", sig);
}
int main()
{
		pid_t pid =fork();
		if(pid == 0)
		{
				sleep(5);
				printf("child eixt\n");
				_exit(0);
		}
		struct sigaction  sa;
		sa.sa_handler = handler;
		sa.sa_flags = 0;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGCHLD, &sa, NULL);
		sigset_t mask;
		sigemptyset(&mask);
		sigset_t  org;
		sigaddset(&mask, SIGCHLD);
		sigprocmask(SIG_BLOCK, &mask, &org);
		int status;
		int ret  = wait(&status);
		printf("%d, %d\n", ret, status);
		sigprocmask(SIG_SETMASK, &org, NULL);
}
