#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
void func1()
{
		printf("%s\n", __func__);
}
void func2()
{
	printf("%s\n", __func__);
}
void func3()
{
	printf("%s\n", __func__);
	raise(SIGQUIT);
}
void handler(int sig)
{
		printf("recieve sig :%d\n", sig);
}
int main()
{
		struct sigaction sa;
		sa.sa_handler = handler;
		sa.sa_flags = 0;
		sigemptyset(&sa.sa_mask);
		//sigaction(SIGQUIT, &sa, NULL);
		atexit(func1);
		//exit(0);
		atexit(func2);
		atexit(func3);
}
