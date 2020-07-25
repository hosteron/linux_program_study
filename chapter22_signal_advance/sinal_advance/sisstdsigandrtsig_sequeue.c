#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void handler(int sig, siginfo_t  *info, void *context)
{

		printf("recived sig:%d, %s\n",sig, strsignal(sig));
		
}
int main()
{
	printf("pid=%d\n", getpid());
	struct sigaction sa;
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigfillset(&sa.sa_mask);
	int i;
	for(i = 0 ; i < NSIG; i++)
		if(i != SIGINT)
		sigaction(i, &sa, NULL);
	sigset_t set, prevMask; 
	sigfillset(&set);
	sigprocmask(SIG_SETMASK, &set, &prevMask);
	if(sigismember(&set, SIGRTMIN+1))
		printf("SIGRTMIN+1 in set\n");
	printf("before sleep\n");
	sleep(20);
	printf("after sleep\n");
	sigprocmask(SIG_SETMASK, &prevMask, NULL);
	//exit(EXIT_SUCCESS);
	while(1)
		pause();
}
