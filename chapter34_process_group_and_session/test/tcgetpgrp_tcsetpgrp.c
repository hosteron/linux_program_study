#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	printf("pid:%ld, ppid:%ld, pgrp:%ld, sid:%ld\n",(long)getpid(), (long)getppid(), (long)getpgrp(), (long)getsid(0));
	pid_t pfid = tcgetpgrp(0);
	printf("proccess foreground group id : %ld \n", (long)pfid);
	sleep(6);
	printf("changing foreground group id \n");
	int ret = tcsetpgrp(0, getppid());
	printf("ret = %d\n", ret);
	if(fork() != 0)
		exit(0);
	pfid = tcgetpgrp(0);
	printf("proccess foreground group id : %ld \n", (long)pfid);
	sleep(10);	
	printf("child exit\n");
}
