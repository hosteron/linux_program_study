#define _POSIX_C_SOURCE 199309
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timerfd.h>
#include <sys/types.h>
#include <stdint.h>
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
int main(int argc,  char **argv)
{
		struct itimerspec  ts;
		struct timespec start, now;
		int maxExp, fd, secs, nanosecs;
		ssize_t s;
		uint64_t numExp, totalExp;
		if(argc < 2)
		{
				printf("%s ....\n", argv[0]);
			return -1;
		}
		char buf[32] = {0};
		strncpy(buf , argv[1], sizeof(buf));
		itimerspecFromStr(buf, &ts);
		maxExp = (argc > 2) ? atoi(argv[2]): 1;
		fd  = timerfd_create(CLOCK_REALTIME, 0);
		if(fd == -1)
		{
				printf("timerfd_create fail\n");
				return -1;
		}
		if(timerfd_settime(fd, 0, &ts, NULL) == -1)
		{
				printf("timerfd_settime fail\n");
				return -1;
		}
		if(clock_gettime(CLOCK_MONOTONIC, &start) == -1)
		{
				close(fd);
				printf("clock_gettime fail\n");
				return -1;
		}
		for(totalExp = 0; totalExp < maxExp;)
		{
				s = read(fd, &numExp, sizeof(uint64_t));
				if(s != sizeof(uint64_t))
				{
						printf("read fail\n");
						close(fd);
						return -1;
				}
				totalExp += numExp;
				if(clock_gettime(CLOCK_MONOTONIC, &now) == -1)
				{
						printf("clock_gettime now fail\n");
						close(fd);
						return -1;
				}
				secs = now.tv_sec - start.tv_sec;
				nanosecs = now.tv_nsec - start.tv_nsec;
				if(nanosecs < 0)
				{
					secs--;
					nanosecs +=  1000000000;
				}
				printf("%d.%03d: expirations read;%lld; total=%llu\n", secs, (nanosecs + 500000)/ 1000000, (unsigned long long)numExp, (unsigned  long long)totalExp);
		}
		exit(EXIT_SUCCESS);
}
