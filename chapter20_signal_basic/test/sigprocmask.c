#include <signal.h>
#include <stdio.h>
#include <unistd.h>
int main()
{
		printf("pid:%d\n", getpid());
		sigset_t set;
		sigfillset(&set);
		sleep(15);
		printf("block sig nal\n");
		sigprocmask(SIG_BLOCK, &set, NULL);
		sleep(20);
}
