#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
static int sigCnt[NSIG];
static volatile sig_atomic_t gotSigint = 0;
void printSigSet(FILE *of, const char *prefix,const sigset_t *sigset)
{
	int sig, cnt;
	cnt = 0;
	for(sig = 1 ; sig < NSIG; sig++)
	{
			if(sigismember(sigset, sig))
			{
					cnt++;
					fprintf(of, "%s%d (%s)\n", prefix, sig, strsignal(sig));
			}
	}
	if(cnt == 0)
	{
			fprintf(of, "%s<empty signal set>\n", prefix);
	}
}
static void handler(int sig)
{
		//static volatile sig_atomic_t a  = 0;
		if(sig == SIGINT)
		{
			gotSigint = 1;
			printf("got sig int\n");
		}
		else
		{
			//a++;
			//printf("before sleep caught %d sig %d %s time=%ld\n", a, sig, strsignal(sig), time(NULL));
			#if 0
			while(1)
			{
					sleep(1);
			}
			#else
			//sleep(10);
			#endif
			
			//printf("after sleep %d time=%ld\n", a, time(NULL));
			sigCnt[sig]++;
		}
}
int main(int argc ,  char *argv[])
{
		int n, numSecs;
		sigset_t pendingMask, blockingMask, emptyMask;
		printf("%s: PID is %ld\n", argv[0], (long)getpid());
		for(n = 1; n < NSIG; n++)
		{
				#if 0
				struct sigaction act;
				act.sa_handler = handler;
				sigemptyset(&act.sa_mask);
				act.sa_flags = 0;
				sigaction(n, &act, NULL);
				#else
				(void)signal(n, handler);
				#endif
				
		}
		if(argc > 1)
		{
				numSecs = atoi(argv[1]);
				sigfillset(&blockingMask);
				if(sigprocmask(SIG_SETMASK, &blockingMask,NULL) == -1)
				{
					printf("sigmask fail\n");
					return -1;
				}
				printf("%s:sleeping for %d seconds\n", argv[0], numSecs);
				sleep(numSecs);
				if(sigpending(&pendingMask) == -1)
				{
						printf("sigpendig fail\n");
						return -1;
				}
				printf("%s:pending signals are: \n", argv[0]);
				printSigSet(stdout, "\t\t", &pendingMask);
				sigemptyset(&emptyMask);
				if(sigprocmask(SIG_SETMASK, &emptyMask, NULL) == -1)
				{
						printf("sigprocmask2 fail\n");
						return -1;
				}
		}
		while(!gotSigint)
		continue;
		for(n = 1; n < NSIG;n++)
		{
				if(sigCnt[n] != 0)
					printf("%s:signal %d caught %d time%s\n", argv[0], n, sigCnt[n], (sigCnt[n] == 1)? "":"s");
		}
		exit(EXIT_SUCCESS);
}
