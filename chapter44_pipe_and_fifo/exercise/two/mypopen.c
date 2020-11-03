#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
static pid_t pidBuf[1024] = {0};
FILE *mypopen(const char *command, const char *type)
{
	if(!command || !type)
		return NULL;
	int isRead = 0;
	if(*type == 'w')
	    isRead = 0;
	else if(*type == 'r')
		isRead = 1;
	else
	{
		printf("type = %s is must equal r or w\n", type);
		return NULL;
	}
	int fds[2] = {0};
	if(pipe(fds) == -1)
	{
			perror("pipe");
			return NULL;
	}
	pid_t childid ;
	switch((childid=fork()))
	{
			case -1:
			perror("fork");
			exit(-1);
			case 0://child
			if(isRead)
			{
				close(fds[0]);
				//printf("read commad:%s, fd:%d\n", command, fds[1]);
				if(STDOUT_FILENO != fds[1])
				{
					//printf("start to dup fd1\n");
					if(dup2(fds[1], STDOUT_FILENO)== -1)
					{
							perror("dup2");
							close(fds[1]);
							_exit(-1);
					}
					close(fds[1]);
				}
				//setbuf(stdout, NULL);
				//write( STDOUT_FILENO, "sadas", 5);
				//_exit(0);
				execlp("/bin/sh", "sh","-c", command, NULL);
			}
			else
			{
				close(fds[1]);
				printf("write commad:%s\n", command);
				if(STDIN_FILENO != fds[0]);
				{
						if(dup2(fds[0], STDIN_FILENO)==-1)
						{
								perror("dup2");
								close(fds[0]);
								_exit(-1);
						}
						close(fds[0]);
				}
				fsync(STDIN_FILENO);
				printf("run in %s\n", command);
				execlp("/bin/sh", "sh","-c", command, NULL);
			}
			break;
			default: //parent
			if(isRead)
			{
				close(fds[1]);
				pidBuf[fds[0]] = childid;
				//printf("[%s:%d]open %d, pid:%ld\n", __func__, __LINE__, fds[0], (long)childid) ;
				return fdopen(fds[0], "r");
				
			}
			else
			{
				close(fds[0]);
				pidBuf[fds[1]] = childid;
				//printf("[%s:%d]open %d, pid:%ld\n", __func__, __LINE__, fds[1],(long)childid) ;
				return fdopen(fds[1], "w");
			}
			
			break;
	}
}
int mypclose(FILE *stream)
{
		if(!stream)
			return -1;
		int fd = fileno(stream);
		pid_t childpid = pidBuf[fd];
		int status;
		close(fd);
		//printf("[%s:%d] close %d, pid=%ld\n", __func__, __LINE__, fd, (long)wpid);
		pidBuf[fd] = 0;
		pid_t wpid = waitpid(childpid, &status,WUNTRACED|WCONTINUED);
		
		return status;
}
int main(int argc ,char **argv)
{
		//setbuf(stdout, NULL);
		if(argc < 3)
		{
				printf("you should  %s <command> <r|w> [text for write]\n", argv[0]);
				return -1;
		}
		if(*argv[2] == 'w' && argc != 4)
		{
				printf("you should  %s <command> <r|w> [text for write]\n", argv[0]);
				return -1;	
		}
		FILE *pf = mypopen(argv[1], argv[2]);
		if(!pf)
		{
				printf("mypopen fail ,%s\n", strerror(errno));
				return -1;
		}
        //printf("fileno=%d\n", fileno(pf));
        setbuf(pf, NULL);
		FILE *pf1 = mypopen("uptime", "r");
		if(!pf1)
		{
			printf("mypopen fail ,%s\n", strerror(errno));
			mypclose(pf);
			return -1;	
		}
        //printf("fileno=%d\n", fileno(pf1));
        setbuf(pf1, NULL);
		char buf[128] = {0};
		if(*argv[2] == 'w')
		{
				int len = strlen(argv[3]);
				fwrite(argv[3], len, 1, pf);
				fflush(pf);
				//write(fileno(pf), argv[3], len);
		}
		else
		{
			printf("first\n");
			while(1)
			{
					//int ret  = fread(buf, sizeof(buf), 1, pf);
					int ret = read(fileno(pf), buf, sizeof(buf));
					printf("ret = %d\n", ret);
					if(ret <= 0)
					break;
					printf("%s", buf);
					memset(buf, 0, sizeof(buf));
			}
			printf("\n");
		}

		printf("second\n");
		while(1)
		{
				//int ret  = fread(buf, sizeof(buf), 1, pf1);
				int ret = read(fileno(pf1), buf, sizeof(buf));
				if(ret <= 0)
				break;
				printf("%s", buf);
				memset(buf, 0, sizeof(buf));
		}
       // sleep(20);
		mypclose(pf);
		mypclose(pf1);
}
