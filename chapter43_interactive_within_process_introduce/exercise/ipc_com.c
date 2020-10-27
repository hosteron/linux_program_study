#include <stdio.h>
#include <time.h>
#include <unistd.h>
//#include <pipe.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
int main(int argc , char **argv)
{
		if(argc != 3 )
		{
			printf("%s size num\n", argv[0]);
			return -1;	
		}
		int size  = atoi(argv[1]);
		int cnt = atoi(argv[2]);
		printf("size=%d, cnt=%d\n", size , cnt);
		int fds[2] = {0};
		int ret = pipe(fds);
		if(ret == -1)
		{
				printf("pipe : %s\n", strerror(errno));
				return -1;
		}
		ret = fork();
		
		if(ret == -1)
		{
				printf("fork : %s\n", strerror(errno));
				return -1;
		}
		else if(ret == 0)
		{
			close(fds[0]);
			char *p = (char *)malloc(size);
			if(!p)
			{
					printf("malloc  fail \n");
					return -1;
			}
			memset(p, '8', size);
			int i = 0;
			for(i = 0; i < cnt; i++)
			{
					int send = 0;
					//int num = 0;
					while((send += write(fds[1], &p[send], size - send)) != size);
			}
			free(p);
			close(fds[1]);
		}
		else
		{
				close(fds[1]);
				char *p = (char *)malloc(size);
				if(!p)
				{
						printf("malloc  fail \n");
						return -1;
				} 
				struct timespec tm;
				clock_gettime(CLOCK_MONOTONIC, &tm);
				int num = 0;
				while((num = read(fds[0], p, size)) > 0)
				{
					
				}
				struct timespec tm1;
				clock_gettime(CLOCK_MONOTONIC, &tm1);
				printf("%lld, %lld\n", (long long)tm.tv_sec, (long long)tm.tv_nsec);
				printf("%lld, %lld\n", (long long)tm1.tv_sec, (long long)tm1.tv_nsec);
		}
}
