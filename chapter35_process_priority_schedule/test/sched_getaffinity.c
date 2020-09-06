#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
int main()
{
		cpu_set_t set;
		int ret = sched_getaffinity(0, sizeof(cpu_set_t ), &set);
		printf("ret = %d, CPU_SETSIZE=%d\n",ret,CPU_SETSIZE);
		int i;
		for(i = 0; i < CPU_SETSIZE; i++)
		{
				if(CPU_ISSET(i, &set))
				{
						printf("%d\n", i);
				}
		}
}
