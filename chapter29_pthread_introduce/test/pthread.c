#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
void *func(void *arg)
{
	int cnt = 0;
	while(1)
	{
		printf("%d\n", cnt++);
		sleep(1);
		if(cnt > 3)
		{
			return (void *)1;
		}
	}
}
int main()
{
	pthread_t  thid;
	int ret = pthread_create(&thid, NULL, func, NULL);
	void *ret1 = NULL;
	if(ret == 0)
	{
		pthread_join(thid, &ret1);
		printf("thread exit ret :%d\n", (long) ret1);
	}
	
	printf("main exit\n");
}
