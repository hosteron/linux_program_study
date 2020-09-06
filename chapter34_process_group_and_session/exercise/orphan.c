#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#if 1
void handler(int sig)
{
		printf("recieve :%d, %s\n", sig, strsignal(sig));
}
#endif
int main()
{
		if(fork() != 0)
			exit(0);
		printf("pid:%ld, ppid:%ld, pgid:%ld, sid:%ld\n", (long)getpid(), (long)getppid(),(long)getpgrp(),(long)getsid(0));
		struct sigaction sa;
		sa.sa_flags = 0;
		sa.sa_handler = handler;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGTSTP, &sa, NULL);
		//char buf[32] = {0};
		//int ret = read(STDIN_FILENO, buf, sizeof(buf));
		//printf("ret:%d, errno=%d, %s\n", ret, errno, strerror(errno));
		pause();
}
