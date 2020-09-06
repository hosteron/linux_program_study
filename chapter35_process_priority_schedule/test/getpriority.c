#include <sys/resource.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
int main()
{
		int nice =  sysconf(RLIMIT_NICE);
		printf("RLIMIT_NICE:%d,%d\n", nice, RLIMIT_NICE);
		int ret = setpriority(PRIO_PROCESS, 0, 10);
		printf("ret = %d, errno=%d, %s\n", ret, errno,strerror(errno));
		int prio = getpriority(PRIO_PROCESS, 0);
		printf("prio = %d\n", prio);
}
