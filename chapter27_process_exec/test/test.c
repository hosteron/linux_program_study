#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
int mysystem(const char *command)
{
		sigset_t blockMask, origMask;
		struct sigaction saIgnore,saOrigQuit,saOrigInt,saDefault;
		pid_t childPid;
		int status,savedErrno;
		if(command == NULL)
			return mysystem(":") == 0;
		sigemptyset(&blockMask);
		sigaddset(&blockMask, SIGCHLD);
		sigprocmask(SIG_BLOCK, &blockMask, &origMask);
		
		saIgnore.sa_handler = SIG_IGN;
		saIgnore.sa_flags = 0;
		sigemptyset(&saIgnore.sa_mask);
		sigaction(SIGINT, &saIgnore, &saOrigInt);
		sigaction(SIGQUIT, &saIgnore, &saOrigQuit);
		switch(childPid = fork())
		{
				case -1:
					status = -1;
					break;
				case 0:
				saDefault.sa_handler = SIG_DFL;
				saDefault.sa_flags = 0;
				sigemptyset(&saDefault.sa_mask);
				if(saOrigInt.sa_handler != SIG_IGN)
					sigaction(SIGINT, &saDefault, NULL);
				if(saOrigQuit.sa_handler != SIG_IGN)
					sigaction(SIGQUIT, &saDefault, NULL);
				sigprocmask(SIG_SETMASK, &origMask, NULL);
				execl("/bin/sh","sh","-c", command, (char *)NULL);
				_exit(127);
				default:
					while(waitpid(childPid, &status, 0) == -1)
					{
							if(errno != EINTR)
							{
								status = -1;
								break;
							}
							
					}
					break;
		}
		savedErrno = errno;
		sigprocmask(SIG_SETMASK, &origMask, NULL);
		sigaction(SIGINT, &saOrigInt, NULL);
		sigaction(SIGQUIT, &saOrigQuit, NULL);
		errno = savedErrno;
		return status;
}
int main(int argc, char **argv)
{
	//int r = chroot("/tmp");
	//printf("chroot ret:%d, %s\n", r, strerror(errno));
	printf("argv[1]= %s\n", argv[1]);
	//int ret = system(argv[1]);
	int ret = mysystem(argv[1]);
	printf("ret = %d\n", ret);
	return 2;
}
