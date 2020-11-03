#include <signal.h>
#include "fifo_seqnum.h"
int main(int argc, char **argv)
{
	int serverFd,dummyFd,clientFd;
	char clientFifo[CLIENT_FIFO_NAME_LEN];
	struct request req;
	struct response resp;
	int seqNum = 0;
	umask(0);
	if(mkfifo(SERVER_FIFO,S_IRUSR|S_IWUSR|S_IWGRP)==-1 && errno != EEXIST)
	{
		printf("%s\n", strerror(errno));
		exit(-1);
	}
	serverFd = open(SERVER_FIFO, O_RDONLY);
	if(serverFd == -1)
	{
		printf("%s\n", strerror(errno));
		exit(-1);
	}
#if 0
	dummyFd = open(SERVER_FIFO, O_WRONLY);
	if(dummyFd == -1)
	{
		printf("%s\n", strerror(errno));
		exit(-1);
	}
#endif
	if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
	{
		printf("%s\n", strerror(errno));
		exit(-1);
	}
	int ret = 0;
	for(;;)
	{
		if((ret = read(serverFd, &req, sizeof(struct request))) == 0)
		{
			close(serverFd);
			serverFd = open(SERVER_FIFO, O_RDONLY);
			if(serverFd == -1)
        		{
                		printf("reopen fifo error,%s\n", strerror(errno));
                		exit(-1);
        		}
			continue;
		}
		else if(ret !=  sizeof(struct request))
		{
			printf("error reading requst;discarding\n");
			continue;
		}
#if 0
		if(read(serverFd, &req, sizeof(struct request)) != sizeof(struct request))
		{
			printf("error reading requst;discarding\n");
			continue;
		}
#endif		
		snprintf(clientFifo, CLIENT_FIFO_NAME_LEN, CLIENT_FIFO_TEMPLATE, (long)req.pid);
		clientFd = open(clientFifo, O_WRONLY);
		if(clientFd == -1)
		{
			printf("open  %s fail \n", clientFifo);
			continue;
		}
		resp.seqNum = seqNum;
		if(write(clientFd, &resp, sizeof(struct response)) != sizeof(struct response))
		{
			printf("error writing to FIFO %s\n", clientFifo);
		}
		if(close(clientFd) == -1)
		{
			printf("close %s\n", strerror(errno));
		}
		seqNum += req.seqLen;
	}
}
