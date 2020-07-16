#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc,  char **argv)
{
		int numSigs, sig, j;
		pid_t  pid;
		if(argc  < 4 || strcmp(argv[1], "--help") == 0)
		{
				printf("%s pid num-sigs sig-num [sig-num-2]\n", argv[0]);
				return -1;
		}
		pid = atoi(argv[1]);
		numSigs = atoi(argv[2]);
		sig = atoi(argv[3]);
		printf("%s:sending signal %d to process %ld %d times\n", argv[0], sig, (long)pid, numSigs);
		for(j = 0; j < numSigs; j++)
		{
				
				if(kill(pid,sig)== -1)
				{
						printf("kill fail\n");
						return -1;
				}
		}
		if(argc > 4)
		{
			if(kill(pid, atoi(argv[4])) == -1)
			{
					printf("kill to %d %s fail\n", pid, strsignal(atoi(argv[4])));
					return -1;
			}
		}
		printf("%s:exiting\n", argv[0]);
		exit(EXIT_SUCCESS);
}
