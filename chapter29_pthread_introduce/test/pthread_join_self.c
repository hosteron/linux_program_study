#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
void *func(void *arg)
{
	printf("join self start\n");
	int ret = pthread_join(pthread_self(), NULL);
	printf("join self end =%d, %s\n", ret, strerror(ret));
}
int main()
{
	pthread_t thid;
	pthread_create(&thid, NULL, func, NULL);
	while(1)
	{
		sleep(1);
	}
}
