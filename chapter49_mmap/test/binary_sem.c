#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include "binary_sem.h"

int initSemInUse(int semId, int which)
{
	union semun arg;
	arg.val = 0;
	return semctl(semId, which, SETVAL, arg);
}

int initSemAvailable(int semId, int which)
{
	union semun arg;
	arg.val = 1;
	return semctl(semId, which, SETVAL, arg);
}

int reserveSem(int semId, int which)
{
	struct sembuf buf;
	buf.sem_num = which;
	buf.sem_flg = 0;
	buf.sem_op = -1;
	return semop(semId, &buf, 1);
}

int releaseSem(int semId, int which)
{
	struct sembuf buf;
	buf.sem_num = which;
	buf.sem_op = 1;
	buf.sem_flg = 0;
	return semop(semId, &buf, 1);
}
