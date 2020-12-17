#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
int print_fcntl_flk(int fd )
{
	struct flock flockstr;
	flockstr.l_type = F_WRLCK;
	flockstr.l_whence = SEEK_SET;
	flockstr.l_start = 0;
	flockstr.l_len = 0;
	int ret = fcntl(fd, F_GETLK, &flockstr);
	if(ret == -1)
	{
		printf("fcnt getlk fail:%s\n", strerror(errno));
		return -1;
	}

	if(flockstr.l_type != F_UNLCK)
	{
		printf("l_type:");
		if(flockstr.l_type == F_WRLCK)
			printf("F_WRLCK\n");
		else
			printf("F_RDLCK\n");
		printf("l_whence:");
		if(flockstr.l_whence == SEEK_SET)
			printf("SEEK_SET\n");
		else if(flockstr.l_whence == SEEK_CUR)
			printf("SEEK_CUR\n");
		else if(flockstr.l_whence == SEEK_END)
			printf("SEEK_END\n");
		printf("l_start:%ld\n",(long) flockstr.l_start);
		printf("l_len:%ld\n", (long)flockstr.l_len);
		printf("l_pid:%ld\n", (long)flockstr.l_pid);
	}	
}
int main(int argc ,char **argv)
{
	printf("PID:%ld\n", (long)getpid());
	if(argc != 2)
	{
		printf("%s filename\n", argv[0]);
		return -1;
	}
	int fd = open(argv[1], O_RDWR);
	if(fd == -1)
	{
		printf("open:%s\n", strerror(errno));
		return -1;
	}
	ftruncate(fd, 100);

	struct flock flockstr;

	flockstr.l_type = F_WRLCK;
	flockstr.l_whence = SEEK_SET;
	flockstr.l_start = 0;
	flockstr.l_len = 50;
	int ret = fcntl(fd, F_SETLK, &flockstr);
	if(ret == -1)
	{
		printf("fcntl setlk %s\n", strerror(errno));
		return -1;
	}
	if(flockstr.l_type == F_WRLCK)
			printf("F_WRLCK\n");
		else
			printf("F_RDLCK\n");
	print_fcntl_flk(fd);
	flockstr.l_whence = SEEK_SET;
	flockstr.l_start = 20;
	flockstr.l_len = 50;
	ret = fcntl(fd , F_SETLK,&flockstr);
	if(ret == -1)
	{
		printf("fcntl2 setlk %s\n", strerror(errno));
		return -1;
	}

	 print_fcntl_flk(fd);

	 sleep(60);
}
