#include <stdio.h>
#include <sched.h>
int main()
{
		int policy = sched_getscheduler(0);
		printf("sched_policy:");
		if(policy == SCHED_RR)
			printf("RR\n");
		else if(policy == SCHED_FIFO)
			printf("FIFO\n");
		else if(policy == SCHED_OTHER)
			printf("OTHER\n");
		else
			printf("??\n");
		struct sched_param param;
		int ret = sched_getparam(0, &param);
		printf("ret:%d, priority:%d\n",ret, param.sched_priority);
}
