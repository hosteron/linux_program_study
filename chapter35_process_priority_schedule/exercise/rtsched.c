#include <stdio.h>
#include <sys/resource.h>
#define _GNU_SOURCE         /* See feature_test_macros(7) */
       #include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <shadow.h>
#include <crypt.h>

#define _GNU_SOURCE
#include <sched.h>
int main(int argc , char **argv)
{
		if(argc < 4)
		{
			printf("you should be ./%s policy priority command arg..\n", argv[0]);
			return -1;
		}
		int policy = 0;
		int priority = 0;
		char *command = NULL;
		char **argvs = NULL;
		int num = 0;
		if(argv[1][0] == 'r')
		{
			policy = SCHED_RR;
			printf("SCHED_RR\n");
		}
		else if(argv[1][0] == 'f')
		{
			policy = SCHED_FIFO;
			printf("SCHED_FIFO\n");
		}
		else
		{
				printf("argv 1 %s do not support\n", argv[1]);
				return -1;
		}
		
		priority = atoi(argv[2]);
		command = argv[3];
		num = argc - 4;
		argvs = malloc(sizeof(char *)*(num+2));
		memset(argvs, 0, sizeof(char *)*(num+2));
		argvs[0] = command;
		int i;
		for(i = 4; i < argc; i++)
		{
				argvs[i+1-4] = argv[i];
		}
		printf("priority=%d\n", priority);
		printf("command:%s\n", command);
		printf("num=%d\n", num);
		for(i = 0; i < num+2; i++)
		{
				printf("%s ", argvs[i]);
		}
		printf("\n");
		printf("real user name:%d\n", getuid());
		struct  passwd *pw =  getpwuid(getuid());
		if(!pw)
		{
				printf("get pw fail \n");
				return -1;
		}
		printf("user name:%s\n", pw->pw_name);
		struct spwd *sp = getspnam(pw->pw_name);
		if(!sp)
		{
			printf("getspnam:%s\n", strerror(errno));
			return -1;
		}
		char *ppass = getpass("input your  password:\n");
		//printf("ppass:%s\n", ppass);
		char *p = crypt(ppass, sp->sp_pwdp);
		//printf("p:%s\n", p);
		//printf("%s\n", sp->sp_pwdp);
		if(!strcmp(p, sp->sp_pwdp))
		{
				printf("login success\n");
		}
		else
		{
				printf("password error\n");
				return -1;
		}
		struct sched_param sched_param;
		sched_param.sched_priority = priority;
		int  r = sched_setscheduler(0, policy, &sched_param);
		if(r == -1)
		{
				printf("sched_setscheduler:%s\n", strerror(errno));
				return -1;
		}
		int ruid,euid,suid;
		getresuid(&ruid, &euid, &suid);
		printf("%d %d %d\n", ruid, euid, suid);
		setuid(getuid());
		printf("after set :\n");
		getresuid(&ruid, &euid, &suid);
		printf("%d %d %d\n", ruid, euid, suid);
		 execvp(command, argvs);
		 printf("execvp error:%s\n", strerror(errno));
}	 

