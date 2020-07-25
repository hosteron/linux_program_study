#define _POSIX_C_SOURCE 199309
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
int main(int argc , char **argv)
{
		int sig,numSigs,j,sigData;
		union sigval sv;
		if(argc < 4 || strcmp(argv[1], "--help") == 0)
		{
			printf("%s pid sig-num data [num-sigs]\n", argv[0]);
			return -1;
		}
		printf("%s: PID is %ld , UID is %ld\n", argv[0], (long)getpid(), (long)getuid());
		sig = atoi(argv[2]);
		sigData = atoi(argv[3]);
		numSigs =  1;
		if(argc > 4)
			numSigs = atoi(argv[4]);
		for(j = 0; j < numSigs; j++)
		{
				sv.sival_int = sigData + j;
				if(sigqueue(atoi(argv[1]), sig, sv) == -1)
				{
						printf("sigqueue fail, %s\n", strerror(errno));
						return -1;
				}
		}
		exit(EXIT_SUCCESS);
}
