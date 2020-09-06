#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
void handler(int sig)
{
	printf("recieve sig : %d, %s\n", sig, strsignal(sig));
}
int main()
{
	struct sigaction sa;
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGHUP, &sa, NULL);
	while(1)
	{
		char buf[32] = {0};
		int ret = read(0, buf, sizeof(buf));
		printf("ret = %d, %s\n", ret, buf);
	}
}
