#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <paths.h>
#include <utmp.h>
#include <stdlib.h>
int main(int argc , char **argv)
{
		struct utmp *ut;
		if(argc > 1 && strcmp(argv[1], "--help") == 0)
		{
				printf("%s [utmp pathname]\n", argv[0]);
				return -1;
		}
		if(argc > 1)
		{
				if(utmpname(argv[1]) == -1)
				{
						printf("utmpname:%s", strerror(errno));
						return -1;
				}
		}
		setutent();
		printf("user	type	PID	line	id	host	data/time\n");
		while((ut = getutent())!= NULL)
		{
				printf("%-8s ",ut->ut_user);
				printf("%-9.9s ",
				(ut->ut_type == EMPTY)?		"EMPTY":
				(ut->ut_type == RUN_LVL)?	"RUN_LVL":
				(ut->ut_type == BOOT_TIME)?	"BOOT_TIME":
				(ut->ut_type == NEW_TIME)?	"NEW_TIME":
				(ut->ut_type == OLD_TIME)?	"OLD_TIME":
				(ut->ut_type == INIT_PROCESS)?"INIT_PR":
				(ut->ut_type == LOGIN_PROCESS)?"LOGIN_PR":
				(ut->ut_type == USER_PROCESS)?"USER_PR":
				(ut->ut_type == DEAD_PROCESS)?"DEAD_PR":"???"
				);
				printf("%5ld %-6.6s %-3.5s %-9.9s ",(long)ut->ut_pid, ut->ut_line,ut->ut_id, ut->ut_host);
				char *p = ctime((time_t *)&(ut->ut_tv.tv_sec));
				printf("%s", p);
				if(p)
					memset(p, 0, strlen(p));
		}
		endutent();
		exit(EXIT_SUCCESS);
}
