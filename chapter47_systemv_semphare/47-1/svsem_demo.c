#include <sys/types.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include "semun.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc ,char **argv)
{
	int semid;
	if(argc < 2 || argc > 3 || strcmp(argv[1], "--help" ) == 0)
	{
		printf("%s init-value\n 	or:%s semid optation \n", argv[0],argv[0]);
		return -1;
	}
	if(argc == 2)
	{
		printf("PID=%ld\n", (long)getpid());
		union semun arg;
		semid = semget(IPC_PRIVATE,1, S_IRUSR|S_IWUSR);
		if(semid == -1)
		{
			printf("create sem fail %s\n", strerror(errno));
			return -1;
		}
		arg.val = atoi(argv[1]);
		if(semctl(semid, 0, SETVAL, arg) == -1)
		{
			printf("semctl setval fail\n");
			return -1;
		}
		pid_t pid = semctl(semid, 0, GETPID, arg);
		printf("Semaphore ID = %d, %d\n", semid, pid);
	}
	else
	{
		struct sembuf sop;
		semid = atoi(argv[1]);
		sop.sem_num = 0;
		sop.sem_op = atoi(argv[2]);
		sop.sem_flg = 0;
		time_t tim ;
		tim = time(NULL);
		printf("%ld:about to semop at %s\n", (long)getpid(), ctime(&tim));
		if(semop(semid, &sop, 1) == -1)
		{
			printf("semop fail %s\n", strerror(errno));
			return -1;
		}
		tim = time(NULL);
		printf("%ld:semop completed at %s\n", (long)getpid(), ctime(&tim));
	}
	exit(EXIT_SUCCESS);
}
