#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
void handler(int sig)
{
	printf("recive signal %d, %s\n", sig, strsignal(sig));
	char buf[32] = {0};
	int ret =read(STDIN_FILENO, buf, sizeof(buf));
	printf("read ret = %d\n", ret);
}
int main()
{
	printf("pid=%d\n", getpid());
	struct sigaction sa;
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	int ret = sigaction(SIGINT, &sa, NULL);
	printf("ret = %d, %s\n", ret, strerror(errno));
	ret = sigaction(SIGQUIT, &sa, NULL);
	printf("ret = %d, %s\n", ret, strerror(errno));
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	ret = sigprocmask(SIG_SETMASK, &set, NULL);
	printf("sigprocmask ret = %d, %s\n", ret, strerror(errno));
	sleep(15);
	printf("after sleep\n");
	sigemptyset(&set);
	sigpending(&set);
	int i;
	for(i = 1; i < NSIG; i++)
	{
			if(sigismember(&set, i))
			{
					printf("sig %d, %s is pending\n", i, strsignal(i));
			}
	}

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	ret = sigprocmask(SIG_UNBLOCK, &set, NULL);
	pause();
}
