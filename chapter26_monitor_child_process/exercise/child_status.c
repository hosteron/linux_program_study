#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
void print(siginfo_t *info)
{
		if(!info)
			return ;
		switch(info->si_code)
		{
				case CLD_EXITED:
				printf("CLD_EXITED ");
				break;
				case CLD_KILLED:
				printf("CLD_KILLED ");
				break;
				case CLD_STOPPED:
				printf("CLD_STOPPED ");
				break;
				case CLD_CONTINUED:
				printf("CLD_CONTINUED ");
				break;
		}
		printf("pid:%d, sig:%d, status:%d, uid:%d\n", info->si_pid, info->si_signo, info->si_status, info->si_uid);
}
int main(int argc ,char **argv)
{
		int status;
		int ret;
		siginfo_t info;
		switch(fork())
		{
				case -1:
					printf("fork fail\n");
					return -1;
				case 0:
				printf("Child started with PID=%ld\n", (long)getpid());
				if(argc > 1)
					exit(atoi(argv[1]));
				else
					for(;;)
						pause();
				exit(EXIT_FAILURE);
				default:
					for(;;){
						ret = waitid(P_ALL, 1, &info, WEXITED | WSTOPPED| WCONTINUED);
						if(ret == -1)
						{
								printf("waitid fail\n");
								return -1;
						}
						print(&info);
						if(info.si_code == CLD_EXITED || info.si_code == CLD_KILLED)
						exit(EXIT_SUCCESS);
					}
		}
}
