#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#if 0
int main()
{
		printf("hello world\n");
		write(STDOUT_FILENO, "Ciao\n", 5);
		if(fork() == -1)
		{
				printf("fork fail\n");
				return -1;
		}
		exit(EXIT_SUCCESS); 	 	
}
#else
int main()
{
		printf("hello1 world\n");
		write(STDOUT_FILENO, "Ciao\n", 5);
		pid_t pid = fork();
		if(pid == -1)
		{
				printf("fork fail\n");
				return -1;
		}
		else if(pid == 0)
		{
				_exit(0);
		}
		else
		{
			exit(EXIT_SUCCESS); 	 	
		}
}
#endif
