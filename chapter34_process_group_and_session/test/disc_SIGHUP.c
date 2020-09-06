#define _GNU_SOURCE
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
static void handler(int sig, siginfo_t *info, void *context)
{
	printf("PID %ld:caught signal %2d (%s)\n", (long)getpid(), sig, strsignal(sig));
	psiginfo(info, "");
	
}
int main(int argc, char **argv)
{
		pid_t parentPid, childPid;
		int j;
		struct sigaction sa;
		if(argc < 2 )
		{
				printf("should be %s (d|s)", argv[0]);
				return -1;
		}
		setbuf(stdout, NULL);
		parentPid = getpid();
		printf("PID of parent is :		%ld\n", (long)parentPid);
		printf("Foregroud process group ID is: %ld, sid=%ld\n",(long)tcgetpgrp(STDIN_FILENO), (long)getsid(parentPid));
		for(j = 1; j < argc; j++)
		{
				childPid = fork();
				if(childPid == -1)
				{
						_exit(-1);
				}
				if(childPid == 0)
				{
					if(argv[j][0] == 'd')
						if(setpgid(0,0) == -1)
							_exit(-2);
					sigemptyset(&sa.sa_mask);
					sa.sa_flags = SA_SIGINFO;
					sa.sa_sigaction = handler;
					sigaction(SIGHUP, &sa, NULL);
					break;
				}
		}
		alarm(60);
		printf("PID:%ld PGID=%ld\n", (long)getpid(), (long)getpgrp());
		for(;;)
			pause();
}
