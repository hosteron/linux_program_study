#include <stdio.h>
#include <sched.h>
int main()
{
		int min  = sched_get_priority_min(SCHED_RR);
		int max = sched_get_priority_max(SCHED_RR);
		printf("SCHED_RR:%d~%d\n", min, max);
		min = sched_get_priority_min(SCHED_FIFO);
		max = sched_get_priority_max(SCHED_FIFO);
		printf("SCHED_FIFO:%d~%d\n", min, max);
}
