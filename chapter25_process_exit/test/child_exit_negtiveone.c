#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
		pid_t pid =fork();
		if(pid == -1)
		{
				printf("fork fail\n");
				return -1;
		}
		else if(pid == 0)
		{
				exit(-1);
		}
		else 
		{
				int status;
				wait(&status);
				printf("wait status : %d\n"，status);
		}
}
