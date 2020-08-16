#include <pthread.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
pthread_mutex_t mtx= PTHREAD_MUTEX_INITIALIZER;
void *func(void *arg)
{
	int ret = pthread_mutex_unlock(&mtx);
	printf("func ret = %d, %s\n", ret, strerror(ret));
}
int main()
{
	pthread_t thid;
	int ret = pthread_create(&thid, NULL, func, NULL);
	printf("pthread create ret = %d\n", ret);
	ret = pthread_mutex_lock(&mtx);
	printf("main lock ret = %d\n", ret);
	while(1)
	{
		sleep(1);
	}
}
