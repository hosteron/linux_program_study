#define _POSIX_C_SOURCE 199309
#define  _XOPEN_SOURCE 600
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	printf("CLOCK_REALTIME:%d,CLOCK_MONOTONIC:%d, CLOCK_PROCESS_CPUTIME_ID:%d,CLOCK_THREAD_CPUTIME_ID:%d\n", CLOCK_REALTIME, CLOCK_MONOTONIC, CLOCK_PROCESS_CPUTIME_ID,CLOCK_THREAD_CPUTIME_ID);
	time_t t = time(NULL);
	printf("time = %ld \n", t);
	struct timespec ts;
	int ret = clock_gettime(CLOCK_REALTIME, &ts);
	printf("clock_gettime ret = %d, sec :%ld, usec:%ld\n", ret, ts.tv_sec, ts.tv_nsec);
	ret = clock_gettime(CLOCK_MONOTONIC, &ts);
	printf("clock_gettime ret = %d, sec :%ld, usec:%ld\n", ret, ts.tv_sec, ts.tv_nsec);
	ret = clock_getres(CLOCK_MONOTONIC, &ts);
	printf("clock_gettime ret = %d, sec :%ld, usec:%ld\n", ret, ts.tv_sec, ts.tv_nsec);
	#if 0
	int cnt = 0;
	while(1)
	{
			if(cnt++ > 100900000)
			break;
	}
	#endif
	clockid_t cid;
	clock_getcpuclockid(0, &cid);
	printf("cpu clock cid :%d\n", cid);
	ret = clock_gettime(cid, &ts);
	printf("clock_gettime ret = %d, sec :%ld, usec:%ld\n", ret, ts.tv_sec, ts.tv_nsec);
	//pthread_getcpuclockid()
}
