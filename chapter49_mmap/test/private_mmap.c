#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "binary_sem.h"
int main(int argc ,char **argv)
{
	int fd = open(argv[1], O_RDWR);
	if(fd == -1)
	{
		printf("open %s fail\n", argv[1]);
		return -1;
	}
	struct stat st;
	fstat(fd, &st);
	
	int semid = semget(SEM_KEY, 2,IPC_CREAT|S_IRUSR | S_IWUSR);
	if(semid==-1)
	{
		printf("semget fail\n");
		return -1;
	}
	initSemInUse(semid, WRITER);
	initSemAvailable(semid, READER);

	char *ptr = (char *)mmap(NULL, st.st_size, PROT_READ|PROT_WRITE, MAP_PRIVATE , fd, 0);
	if(ptr ==  MAP_FAILED)
	{
		printf("mmap fail\n");
		return -1;
	}
	
	int i;
	int cnt  = 0;
	while(1)
	{
		if(cnt++ > 3)
			break;
		reserveSem(semid, READER);
		for(i = 0; i < st.st_size; i++)
		{
			printf("%c ", *(ptr+i));
		}
		printf("\n");
		if(cnt == 1)
		{
			*ptr = 'x';
		}

		releaseSem(semid, WRITER);
	}
	
	union semun arg;
	semctl(semid, 0, IPC_RMID,arg);
	munmap(ptr,st.st_size);
}
