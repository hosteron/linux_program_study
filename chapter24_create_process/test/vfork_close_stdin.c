#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
		pid_t pid = vfork();
		int num = 0;
		switch(pid)
		{
				case -1:
				printf("vfork fail\n");
				break;
				case 0:
				printf("child:%d\n", getpid());
				close(STDIN_FILENO);
				printf("hase closed STDIN_FILENO\n");
				_exit(EXIT_SUCCESS);
				break;
				default:
				printf("parent:%d\n", getpid());
				scanf("%d", &num);
				printf("num=%d\n", num);
				break;
		}
}
