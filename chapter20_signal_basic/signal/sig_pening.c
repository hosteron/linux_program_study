#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
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
void handler(int sig)
{
		static int a = 0;
		a ++;
	printf("sig = %d, a=%d\n", sig, a);
	sleep(10);
	printf("sig = %d exit a=%d\n", sig, a);
}
int main()
{
		#if 0
		sigset_t empty;
		sigemptyset(&empty);
		sigaddset(&empty, SIGINT);
		sigprocmask(SIG_SETMASK, &empty, NULL);
		printf("pid=%d\n", getpid());
		sleep(10);
		sigset_t pending;
		sigpending(&pending);
		printSigSet(stdout, "\t\t", &pending);
		signal(SIGINT,SIG_IGN);
		printf("exit\n");
		#endif
		struct sigaction act;
		act.sa_handler = handler;
		sigemptyset(&act.sa_mask);
		//act.sa_flags = SA_NODEFER;
		act.sa_flags = 0;
		sigaction(SIGINT, &act, NULL);
		while(1)
		{
				pause();
		}
	
}
