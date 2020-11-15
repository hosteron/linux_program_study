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
int main()
{
	union semun arg;
	struct seminfo buf;
	arg.__buf = &buf;
	int maxind = semctl(0, 0, SEM_INFO, arg);
	printf("maxind = %d\n", maxind);
	
	int i;
	struct semid_ds ds;
	arg.buf = &ds;
	for(i = 0; i <= maxind; i++)
	{
		int semid = semctl(i, 0, SEM_STAT, arg);
		if(semid == -1)
		{
			if(errno != EINVAL &&errno != EACCES)
			{
				printf("err %s\n", strerror(errno));
				return -1;
			}
			continue;
		}
		printf("%4d %8d 0x%08lx %7ld\n", i, semid, ds.sem_perm.__key, ds.sem_nsems);
	}
}
