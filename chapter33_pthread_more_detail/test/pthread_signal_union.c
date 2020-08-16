#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
void printsig(sigset_t set)
{
		int i;
		for(i = 1; i < NSIG; i++)
		{
				if(sigismember(&set, i))
				{
						printf("%d ", i);
				}
		}
		printf("\n");
}
void *func(void *arg)
{
	sigset_t set, org;
	sigemptyset(&set);
	sigaddset(&set, SIGBUS);
	pthread_sigmask(SIG_BLOCK, &set, &org);
	
	printf("func msk:\n");
	printsig(org);
	 pthread_sigmask(SIG_BLOCK, NULL, &org);
	 printf("func now:\n");
	printsig(org);
	int cnt = 0;
	while(cnt++ < 5)
	{
			sleep(1);
	}
	sigpending(&set);
	printf("func pending:\n");
	printsig(set);	
}
int main()
{
		sigset_t set, org;
		sigemptyset(&set);
		sigaddset(&set, SIGTERM);
		sigaddset(&set, SIGPIPE);
		sigaddset(&set, SIGINT);
		sigprocmask(SIG_SETMASK, &set, &org);
		printf("mask now:\n");
		printsig(set);
		printf("mask org:\n");
		printsig(org);
		
		pthread_t t1;
		pthread_create(&t1, NULL, func, NULL);
		sleep(2);
		raise(SIGTERM);
		//kill(getpid(), SIGTERM);
		pthread_join(t1, NULL);
		sigpending(&set);
		printf("main ping:\n");
		printsig(set);
}
