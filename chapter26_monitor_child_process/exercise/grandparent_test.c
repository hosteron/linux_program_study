#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
		printf("grandfather:%d\n", getpid());
		pid_t pid = fork();
		if(pid == -1)
		{
				printf("fork()fail\n");
				return -1;
		}
		else if(pid == 0)
		{
				printf("father:%d\n", getpid());
				pid = fork();
				if(pid == -1)
				{
						printf("father fork()fail\n");
						return -1;
				}
				else if(pid == 0)
				{
						printf("child:%d\n", getpid());
						pause();
				}
				_exit(0);
		}
		else
		{
				while(wait(NULL) != -1)
					continue;
		}
		
}
