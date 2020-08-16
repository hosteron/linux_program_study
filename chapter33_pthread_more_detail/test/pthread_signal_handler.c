#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
void *func(void *arg)
{
		printf("thread %s \n", __func__);
		#if 0
		char *p = NULL;
		*p = 'a';
		int a = 10 / 0;
		#endif
		
		printf("func1 exit, %s\n",strsignal(SIGFPE));
		//raise(SIGTERM);
}
void * normal(void *arg)
{
		while(1)
		{
				printf("thread %s \n", __func__);
				sleep(1);
		}
}
void handler(int sig)
{
	  printf("recieve sig =%d, %s\n", sig, strsignal(sig));
	}
int main()
{
		struct sigaction sa;
		sa.sa_handler =  handler;
		sa.sa_flags = 0;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGPIPE, &sa, NULL);
		pthread_t t1,t2;
		pthread_create(&t1, NULL, func, NULL);
		pthread_create(&t2, NULL, normal, NULL);
		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
		printf("main exit\n");
}
