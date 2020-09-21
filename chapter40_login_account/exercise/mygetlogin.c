#include <utmp.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
char *mygetlogin()
{
		static char rebuf[64] = {0};
		memset(rebuf, 0, sizeof(rebuf));
		char *ptty = ttyname(STDIN_FILENO);
		if(!ptty)
		{
				printf("ptty is null : %s\n", strerror(errno));
				return NULL;
		}
		printf("tty = %s\n", ptty);
		setutent();
		struct utmp *ut;
		while((ut = getutent()) != NULL)
		{
				printf("line:%s\n", ut->ut_line);
				 if(ut->ut_type == USER_PROCESS && !strcmp(ut->ut_line, &ptty[5]))
				 {
						strncpy(rebuf, ut->ut_user, sizeof(rebuf));
						return rebuf;
				}
		}
		endutent();
		return NULL;
}
int main()
{
	char *p = mygetlogin();
	printf("ret:%s\n", p);
}
