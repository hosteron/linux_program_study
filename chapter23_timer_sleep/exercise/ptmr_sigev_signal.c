#define _POSIX_C_SOURCE 199309
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define TIMER_SIG SIGRTMAX
void itimerspecFromStr(char *str, struct itimerspec *tsp)
{
		char *cptr, *sptr;
		cptr = strchr(str, ':');
		if(cptr != NULL)
			*cptr = '\0';
		sptr = strchr(str, '/');
		if(sptr != NULL)
			*sptr = '\0';
		tsp->it_value.tv_sec = atoi(str);
		tsp->it_value.tv_nsec = (sptr != NULL) ? atoi(sptr+1) : 0;
		if(cptr == NULL){
				tsp->it_interval.tv_sec  =0;
				tsp->it_interval.tv_nsec =0;
			}
		else
		{
				sptr = strchr(cptr + 1, '/');
				if(sptr != NULL)
				*sptr = '\0';
				tsp->it_interval.tv_sec = atoi(cptr+1);
				tsp->it_interval.tv_nsec = (sptr != NULL)  ? atoi(sptr+1): 0;
		}
}
static void handler(int sig, siginfo_t *si, void *uc)
{
		timer_t *tidptr;
		tidptr = si->si_value.sival_ptr;
		time_t t = time(NULL);
		printf("%s Got signal %d\n", ctime(&t), sig);
		printf("	*sigval_ptr			= %ld\n", (long)*tidptr);
		printf("	timer_getoverrun()  = %d\n", timer_getoverrun(*tidptr));
		struct itimerspec curr;
		timer_gettime((timer_t)*tidptr, &curr);
		printf("	%ld:%ld %ld:%ld\n", curr.it_value.tv_sec, curr.it_value.tv_nsec, curr.it_interval.tv_sec, curr.it_interval.tv_nsec);
}
int main(int argc, char **argv)
{
	struct itimerspec ts;
	struct sigaction sa;
	struct sigevent sev;
	timer_t *tidlist;
	int j;
	if(argc < 2)
	{
			printf("%s ....\n", argv[0]);
			return -1;
	}
	tidlist = calloc(argc -1 , sizeof(timer_t));
	if(tidlist == NULL)
	{
			printf("calloc fail\n");
			return -1;
	}
	#if 0
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	if(sigaction(TIMER_SIG, &sa, NULL) == -1)
	{
			printf("sigaction fail\n");
			return -1;
	}
	#endif
	sigset_t  mask;
	sigemptyset(&mask);
	sigaddset(&mask, TIMER_SIG);
	sigprocmask(SIG_SETMASK, &mask, NULL);
	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = TIMER_SIG;
	for(j = 0; j < argc - 1; j++)
	{
			itimerspecFromStr(argv[j+1], &ts);
			sev.sigev_value.sival_ptr = &tidlist[j];
			//if(timer_create(CLOCK_REALTIME, &sev, &tidlist[j]) == -1)
			#if 0  //如果下面使用的是TIMER_ABSTIME设置的timer_settime来设置绝对时间的话，则需要计算clock_gettime得来的时间
			struct timespec now;
			clock_gettime(CLOCK_MONOTONIC, &now);
			ts.it_value.tv_sec += now.tv_sec;
			ts.it_value.tv_nsec += now.tv_nsec;
			#endif
			if(timer_create(CLOCK_MONOTONIC, &sev, &tidlist[j]) == -1)
			{
					printf("timer create fail\n");
					return -1;
			}
			printf("Timer ID:%ld (%s)\n", (long)tidlist[j], argv[j+1]);
			if(timer_settime(tidlist[j], 0/*TIMER_ABSTIME*/, &ts, NULL) == -1)
			{
					printf("timer_settime fail\n");
					return -1;
			}
	}
	
	for(;;)
	{
				siginfo_t info;
				int sig = sigwaitinfo(&mask, &info);
				printf("sig = %d\n", sig);
				siginfo_t *si = &info;
				timer_t *tidptr;
		tidptr = si->si_value.sival_ptr;
		time_t t = time(NULL);
		printf("%s Got signal %d\n", ctime(&t), sig);
		printf("	*sigval_ptr			= %ld\n", (long)*tidptr);
		printf("	timer_getoverrun()  = %d\n", timer_getoverrun(*tidptr));
		struct itimerspec curr;
		timer_gettime((timer_t)*tidptr, &curr);
		printf("	%ld:%ld %ld:%ld\n", curr.it_value.tv_sec, curr.it_value.tv_nsec, curr.it_interval.tv_sec, curr.it_interval.tv_nsec);

	}
}
