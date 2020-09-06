#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
int main(int argc ,char **argv)
{
		int opt;
		int prio;
		int flag = 0;
		int f = 0;
		while((opt = getopt(argc, argv, "n:")) != -1)
		{
				switch(opt)
				{
						case 'n':
						prio = atoi(optarg);
						flag = 1;
						printf("set prority:%d\n", prio);
						f = 1;
						break;
						default:
						//printf("error opt:%c\n", opt);
						return -1;
						optind--;
						f = 1;
						break;
				}
				if(f == 1)
				break;
		}
		if(!flag)
		{
				prio  = getpriority(PRIO_PROCESS, 0);
				printf("priority:%d\n", prio);
				return 0;
		}
		
		int ret = setpriority(PRIO_PROCESS, 0, prio);
		if(ret == -1)
		{
				printf("setpriority fail:%s\n", strerror(errno));
				return -1;
		}
		if(argc - optind <= 0)
		{
				printf("you should be ./%s [option ] [command args] \n", argv[0]);
				return -1;
		}
		
		char *command = argv[optind];
		printf("command:%s\n", command);
		int num = argc - optind -1;
		printf("num = %d\n", num);
		char **argvs = (char **)malloc(sizeof(char *)*(num+1+1));
		memset(argvs, 0, sizeof(char *)*(num+1));
		argvs[0] = command;
		if(num)
		
		{
				
				int i;
				for(i = optind+1;i < argc;i++)
				{
						argvs[i - optind] = argv[i];
						printf("%s\n", argv[i]);
				}
				
		}
		 execvp(command, argvs);
		printf("execvp error:%s\n", strerror(errno));
}
