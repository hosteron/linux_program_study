#include <sys/types.h>
#include <sys/sem.h>
#include "semun.h"
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	int semid = semget(IPC_PRIVATE, 1, IPC_CREAT | S_IRUSR| S_IWUSR);
	if(semid == -1)
	{
		printf("semget fail %s\n", strerror(errno));
		return -1;
	}
	union semun arg;
	struct sembuf buf;
	arg.val = 0;
	if(semctl(semid, 0, SETVAL, arg) == -1)
	{
		printf("semctl fail %s\n", strerror(errno));
		return -1;
	}

	printf("semaphore id = %d\n", semid);
	switch(fork())
	{
		case -1:
		printf("fork fail\n");
		exit(-1);
		case 0:
		
		sleep(10);
		buf.sem_op = 1;
		buf.sem_num = 0;
		buf.sem_flg = 0;
		semop(semid, &buf, 1);
		printf("child about to  exit\n");
		_exit(EXIT_SUCCESS);
		default:
		buf.sem_op = -1;
		buf.sem_num = 0;
		buf.sem_flg = 0;
		semop(semid, &buf, 1);
		printf("parent abort to delete semaphore %d\n", semid);
		semctl(semid, 0, IPC_RMID, arg);
		exit(EXIT_SUCCESS);
		
	}
}
