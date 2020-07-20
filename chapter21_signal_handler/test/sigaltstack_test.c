#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
void handler(int sig)
{
		int ret = 0;
		printf("ret addr = %p\n", &ret);
}
int main()
{
		printf("pid:%d\n", getpid());
		stack_t new_stack;
		new_stack.ss_sp = malloc(SIGSTKSZ);
		new_stack.ss_flags = 0;
		new_stack.ss_size = SIGSTKSZ;
		sigaltstack(&new_stack, NULL);
		printf("start : %p\n", new_stack.ss_sp);
		struct sigaction sa;
		sa.sa_handler = handler;
		sa.sa_flags = SA_ONSTACK;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGINT, &sa, NULL);
		pause();
		sigaction(SIGTERM, &sa,NULL);
		pause();
}
