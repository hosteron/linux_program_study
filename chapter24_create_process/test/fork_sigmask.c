#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
void printmask(sigset_t *mask)
{
		if(!mask) return;
		int i;
		for(i = 1; i < NSIG; i++)
		{
				if(sigismember(mask, i))
				{
						printf("sig=%d, %s\n", i, strsignal(i));
				}
		}
}
void handler(int sig)
{
	
}
int main()
{
		sigset_t mask, premask;
		sigemptyset(&mask);
		sigaddset(&mask, SIGUSR1);
		sigaddset(&mask, SIGUSR2);
		sigprocmask(SIG_SETMASK, &mask, &premask);
		struct sigaction sa;
		sa.sa_handler = handler;
		sa.sa_flags  = 0;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGUSR1, &sa, NULL);
		pid_t pid = fork();
		int i;
		switch(pid)
		{
				case  -1:
				printf("fork fail\n");
				break;
				case 0:
				sigemptyset(&mask);
				if(sigsuspend(&mask) == -1 && errno != EINTR)
				{
						printf("sigsuspend fail\n");
						return -1;
				}
				printf("child:%d\n", getpid());
				sigprocmask(SIG_SETMASK, NULL, &mask);
				printmask(&mask);
				
				break;
				default:
				
				
				printf("parent:%d\n", getpid());
				sigprocmask(SIG_SETMASK, NULL, &mask);
				printmask(&mask);
				kill(pid, SIGUSR1);
				break;
		}
}
