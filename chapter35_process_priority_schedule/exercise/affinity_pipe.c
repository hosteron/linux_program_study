#define _GNU_SOURCE
#include <sched.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
int main()
{
		cpu_set_t set;
		CPU_ZERO(&set);
		int fds[2] = {0};
		int r = pipe(fds);
		if(r == -1)
		{
				printf("pipe fail:%s\n", strerror(errno));
				return -1;
		}
		pid_t pid = fork();
		
		if(pid == -1)
		{
				printf("fork fail\n");
				exit(-1);
		}
		else if(pid == 0)
		{
				//child
				close(fds[0]);
				printf("child %ld \n", (long)getpid());
				CPU_SET(0, &set);
				int ret = sched_setaffinity(0, sizeof(cpu_set_t), &set);
				if(ret == -1)
				{
						printf("child setaffinity fail : %s\n", strerror(errno));
						_exit(-1);
				}
				int i;
				char buf[32] = "helloworld";
				for(i = 0; i < 1000000 ; i++)
				{
						//printf("write,%s\n", buf);
						write(fds[1], buf, strlen(buf));
				}
				#if 0
				char tmp[32] = {0};
				int num = read(fds[0], tmp, sizeof(tmp));
				printf("num=%d, %s\n", num, tmp);
				#endif
				close(fds[1]);
				printf("child exit\n");
		}
		else
		{
				close(fds[1]);
				//parent
				printf("parent %ld \n", (long)getpid());
				CPU_SET(1, &set);
				int ret = sched_setaffinity(0, sizeof(cpu_set_t), &set);
				if(ret == -1)
				{
						printf("parent setaffinity fail : %s\n", strerror(errno));
						_exit(-1);
				}
				char buf[32] = {0};
				while(1)
				{
						//printf("prepare to read\n");
						int num = read(fds[0], buf, sizeof(buf));
						if(num <= 0)
						{
								//printf("read end, num=%d\n", num);
								_exit(0);
						}
						else
						{
								//printf("num:%d, %s\n", num, buf);
						}
				}
				printf("parent exit\n");
		}
}
