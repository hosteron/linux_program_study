#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
static int glob = 0;
typedef struct thread_arg
{
	int id;
	int cnt;
}thread_arg_t;
static void *threadFunc(void *func)
{
	 thread_arg_t *para = (thread_arg_t *)func;
	 int loc, j;
	 for(j  = 0; j < para->cnt; j++)
	 {
			loc = glob;
			loc++;
			glob = loc;
			printf("thread %d glob =%d\n", para->id, glob);
	}
	return NULL;
}

int main(int argc ,char **argv)
{
		pthread_t t1, t2;
		thread_arg_t arg1, arg2;
		arg1.id = 1;
		arg2.id = 2;
		arg1.cnt = atoi(argv[1]);
		arg2.cnt = atoi(argv[2]);
		pthread_create(&t1, NULL, threadFunc, &arg1);
		pthread_create(&t2, NULL, threadFunc, &arg2);
		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
		printf("glob= %d\n", glob);
}
