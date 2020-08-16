#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
static __thread int a = 0;
//pthread_attr_t attr;
void *func(void *arg)
{
		printf("thread a =%p\n", &a);
		//int size;
		//pthread_attr_getstacksize(&attr, &size);
		//printf("stack size = %d", size);
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		size_t size;
		
		int ret = pthread_attr_setstacksize(&attr, 16*1024);
		printf("ret=%d, %s\n", ret, strerror(ret));
		pthread_attr_getstacksize(&attr, &size);
		printf("size=%ld\n", size);
}
int main()
{
		pthread_t  t;
		pthread_create(&t, NULL, func, NULL);
		
		printf("main a = %p\n", &a);
		pthread_join(t, NULL);
		
}
