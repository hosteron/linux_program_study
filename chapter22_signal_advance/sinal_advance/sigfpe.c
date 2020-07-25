//#define _POSIX_C_SOURCE 199309
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
volatile sig_atomic_t  a  = 0;
void handler(int sig, siginfo_t *info, void *context)
{
		if(a++ > 0)
		 _exit(2);
		printf("recive sig:%d, %s\n",sig, strsignal(sig));
		psiginfo(info,"psiginfo:");
}
int main()
{
		int a  = 1;
		printf("pid=%d\n", getpid());
		struct sigaction sa;
		sa.sa_sigaction = handler;
		sa.sa_flags = SA_SIGINFO;
		sigemptyset(&sa.sa_mask);
		int ret = sigaction(SIGRTMIN, &sa, NULL);
		//ret = a / 0;
		pause();
}
