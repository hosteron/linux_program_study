#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
void printItimerval(struct itimerval *val)
{
		if(!val)return ;
		printf("it_interval:%ld, %ld; it_value:%ld, %ld\n", val->it_interval.tv_sec, val->it_interval.tv_usec, val->it_value.tv_sec, val->it_value.tv_usec);
}
int main()
{
		struct itimerval val;
		int ret = 0;
		val.it_interval.tv_sec = 5;
		val.it_interval.tv_usec = 0;
		val.it_value.tv_sec = 2;
		val.it_value.tv_usec = 0;
		ret = setitimer(ITIMER_PROF, &val, NULL);
		printf("setitimer ret : %d\n", ret);
		ret = getitimer(ITIMER_REAL, &val);
		printf("ret = %d\n",  ret);
		printItimerval(&val);
		ret = getitimer(ITIMER_VIRTUAL, &val);
		printf("ret = %d\n",  ret);
		printItimerval(&val);
		#if 1
		val.it_interval.tv_sec = 0;
		val.it_interval.tv_usec = 0;
		val.it_value.tv_sec = 0;
		val.it_value.tv_usec = 0;
		ret = setitimer(ITIMER_VIRTUAL, &val, NULL); // 你这个which要指向相同的which值　ret = setitimer(ITIMER_PROF, &val, NULL);
		printf("setitimer ret : %d\n", ret);
		
		#endif
		ret = getitimer(ITIMER_PROF, &val);
		printf("ret = %d\n",  ret);
		printItimerval(&val);
		
		sleep (2);
		ret = getitimer(ITIMER_PROF, &val);
		printf("ater sleep ret = %d\n",  ret);
		printItimerval(&val);
}
