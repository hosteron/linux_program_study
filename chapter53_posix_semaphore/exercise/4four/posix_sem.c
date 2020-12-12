#include <semaphore.h>
#include "tlpi_hdr.h"
#include <fcntl.h>
#include <pthread.h>
sem_t *sem;
void *func(void *arg)
{
	int *num = (int *)arg;
	int i ; 
	for(i = 0; i < *num  ; i ++)
	{
		sem_post(sem);
	}
}
void *func1(void *arg)
{
	int *num = (int *)arg;
}
int main(int argc, char **argv)
{
	int num = atoi(argv[1]);
	sem = sem_open("/sem", O_CREAT|O_EXCL, S_IRUSR|S_IWUSR,0);
	int i;
	pthread_t id;
	pthread_create(&id, NULL, func, &num);
	pthread_t  id1;
	pthread_create(&id1, NULL, func1, &num);
	for(i = 0; i < num ; i ++)
	{
		sem_wait(sem);
	}

}
