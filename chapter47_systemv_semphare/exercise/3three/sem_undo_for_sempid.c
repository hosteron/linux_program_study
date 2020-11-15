#include <sys/types.h>
#include <sys/sem.h>
#include <string.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "semun.h"

int main(int argc ,char **argv)
{
	if(argc != 2)
	{
		printf("you should %s <semid>\n", argv[0]);
		return -1;
	}
	printf("PID=%ld\n", (long)getpid());
	union semun arg;
	int semid = atoi(argv[1]);
	int pid = semctl(semid, 0, GETPID, arg);
	printf("before semop pid=%d\n", pid);
	struct sembuf buf;
	buf.sem_num = 0;
	buf.sem_op = 1;
	//buf.sem_flg = SEM_UNDO;
	buf.sem_flg = 0;
	semop(semid, &buf, 1);

	pid = semctl(semid, 0, GETPID, arg);
	printf("after semop undo pid= %d\n", pid);
}
