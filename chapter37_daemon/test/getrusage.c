#include <sys/resource.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
void printRusage(struct rusage *usage)
{
		if(!usage) return;
		printf("user:%ld.%ld\n", (long)usage->ru_utime.tv_sec, (long)usage->ru_utime.tv_usec);
		printf("sys :%ld.%ld\n", (long)usage->ru_stime.tv_sec, (long)usage->ru_stime.tv_usec);
}
int main()
{
		pid_t pid = fork();
		if(pid == -1)
		{
				return -1;
		}
		else if(pid == 0)
		{
			  int i = 0;
			  int cnt = 0;
			  for(i = 0; i < 1000000; i++)
			  {
					  cnt+=1;
				}
				printf("cnt = %d\n", cnt);
				_exit(1);
		}
		else
		{
			struct rusage usage;
			getrusage(RUSAGE_CHILDREN, &usage);
			printRusage(&usage);
			int status;
			wait(&status);
			printf("status:%d\n", status);
			getrusage(RUSAGE_CHILDREN, &usage);
			printRusage(&usage);
		}
}
