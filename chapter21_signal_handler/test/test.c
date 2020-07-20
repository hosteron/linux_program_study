#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
static sigjmp_buf senv;
volatile sig_atomic_t sflag = 0;
void handler(int sig)
{
		printf("int the handler\n");
		sflag = 1;
		siglongjmp(senv, 1);
		printf("never run this way\n");
}
int main()
{
		printf("start\n");
		struct sigaction sa;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags =0;
		sa.sa_handler = handler;
		sigaction(SIGABRT, &sa, NULL);
		if(sigsetjmp(senv, 1) == 0)
		{
					printf("init sigsetjmp\n");
		}
		else
		{
				printf("return from handler\n");
		}
		if(!sflag)
		{
			printf("invoke  abort()\n");
			abort();
		}
		printf("after abort, it means  abort() fail\n");
}
