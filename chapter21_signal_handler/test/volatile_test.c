#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
volatile int a = 0;
void *func(void *arg)
{
	int i;
	for(i = 0;  i < 1000 ; i++)
	{
			a ++;
	}
	printf("thread %d exit\n", arg);
}
int main()
{
	//	int a;
		int i;
		for(i = 0; i < 10; i++)
		{
			pthread_t  thid;
			pthread_create(&thid, NULL, func, i);
		}
		sleep(5);
		printf("a = %d\n",a);
}
