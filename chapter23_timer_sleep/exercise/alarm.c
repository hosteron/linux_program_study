#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timerfd.h>
#include <sys/types.h>
#include <stdint.h>
#include <sys/time.h>
int myalarm(int secs)
{
		int ret = 0;
		struct itimerval val;
		getitimer(ITIMER_REAL, &val);
		if(val.it_value.tv_sec == 0 && val.it_value.tv_usec== 0)
			ret = 0;
		else
			ret = val.it_value.tv_sec;
		val.it_value.tv_sec = secs;
		val.it_value.tv_usec = 0;
		val.it_interval.tv_sec = 0;
		val.it_interval.tv_usec = 0;
		setitimer(ITIMER_REAL,&val, NULL);
		return ret;
}
void handler(int sig)
{
		printf("recive signal:%d, %s\n", sig, strsignal(sig));
}

int main()
{
		struct sigaction sa;
		sa.sa_handler = handler;
		sa.sa_flags = 0;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGALRM, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		int ret = myalarm(5);//alarm(5);
		printf("alarm ret = %d\n", ret);
		for(;;)
			pause();
}
