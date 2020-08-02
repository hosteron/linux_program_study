#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int i = 0;
	int j = 0;
	for(i = 0; i < 20 ; i++)
	{
		for(j = 0; j < i;j++)
		{
			printf("%d", i);
		}
		printf("\n");
	}
	pid_t pid = fork();
	if(pid == -1)
	{
		printf("fork fail\n");
		return -1;
	}
	else if(pid == 0)
	{
		//child
		_exit(0);
	}
	else
	{
		//parent
		exit(0);
	}
}
