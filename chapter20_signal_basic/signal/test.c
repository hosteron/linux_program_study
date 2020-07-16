#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
	//sigset_t fillset;
	//sigfillset(&fillset);
	//sigprocmask(SIG_SETMASK, &fillset, NULL);
	printf("before sleep %d\n", getpid());
	//sleep(30);
	pause();
}
