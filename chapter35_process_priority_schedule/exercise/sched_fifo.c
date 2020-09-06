#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>

#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/times.h>
            /* See feature_test_macros(7) */
       #include <sched.h>

int main()
{
		struct tms buf;
		struct tms buf_bk;
		printf("sysconf(_SC_CLK_TCK) = %ld\n", sysconf(_SC_CLK_TCK));
		struct sched_param param;
		param.sched_priority = 80;
		int ret = sched_setscheduler(0,SCHED_FIFO,&param);
		if(ret == -1)
		{
				printf("setscheduler fail:%s\n", strerror(errno));
				return -1;
		}
		//
		//
		//
		//如果是多核的系统,一定要指定了某个CPU,这样才能达到程序SCHED_FIFO的轮训调度,不能可能一个进程在0CPU,一个进程在1CPU两者还是互相不相关的队列
		cpu_set_t set;
		CPU_ZERO(&set);
		CPU_SET(0, &set);
		ret = sched_setaffinity(0, sizeof(cpu_set_t ), &set);
		if(ret == -1)
		{
				printf("sched_setaffinity fail:%s\n", strerror(errno));
				return -1;
		}
		 pid_t pid = fork();
		if(pid == -1)
		{
				printf("fork fail\n");
				exit(0);
		}
		else if(pid == 0)
		{
			times(&buf_bk);
				//child
				struct tms buf1;
				struct tms buf2;
				times(&buf1);
				times(&buf2);
				while(1)
				{
						times(&buf);
						if((buf.tms_utime+buf.tms_stime - (buf_bk.tms_utime+buf_bk.tms_stime))>= sysconf(_SC_CLK_TCK)/4)
						{
								printf("child:%ld, %d, %d\n", (long)getpid(), buf.tms_utime,buf.tms_stime);
								buf_bk = buf;
						}
						else if((buf.tms_utime+buf.tms_stime - (buf1.tms_utime+buf1.tms_stime))>= sysconf(_SC_CLK_TCK))
						{
								buf1 = buf;
								sched_yield();
						}
						else if((buf.tms_utime+buf.tms_stime - (buf2.tms_utime+buf2.tms_stime))>= sysconf(_SC_CLK_TCK)*3)
						{
								printf("child exit\n");
								_exit(0);
						}
				}
		}
		else
		{
			times(&buf_bk);
				//parent
				struct tms buf1;
				struct tms buf2;
				times(&buf1);
				times(&buf2);
				while(1)
				{
						times(&buf);
						if((buf.tms_utime+buf.tms_stime - (buf_bk.tms_utime+buf_bk.tms_stime))>= sysconf(_SC_CLK_TCK)/4)
						{
								printf("parent:%ld, %d, %d\n", (long)getpid(), buf.tms_utime,buf.tms_stime);
								buf_bk = buf;
						}
						else if((buf.tms_utime+buf.tms_stime - (buf1.tms_utime+buf1.tms_stime))>= sysconf(_SC_CLK_TCK))
						{
								buf1 = buf;
								sched_yield();
						}
						else if((buf.tms_utime+buf.tms_stime - (buf2.tms_utime+buf2.tms_stime))>= sysconf(_SC_CLK_TCK)*3)
						{
								printf("parent exit\n");
								_exit(0);
						}
				}
		}
}
