#include "fifo_seqnum.h"
#include <signal.h>
static  char clientFifo[CLIENT_FIFO_NAME_LEN];
static void removeFifo(void)
{
	unlink(clientFifo);
}
void handler(int sig)
{
	psignal(sig, "recieve:");
}
int main(int argc , char **argv)
{
	int serverFd, clientFd;
	struct request req;
	struct response resp;
	if(argc > 1 && strcmp(argv[1], "--help") == 0)
	{
		printf("%s [seq-len...]\n", argv[0]);
		return -1;
	}
	umask(0);
	struct sigaction sa;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sigaction(SIGPIPE, &sa, NULL);
	snprintf(clientFifo, CLIENT_FIFO_NAME_LEN, CLIENT_FIFO_TEMPLATE,(long)getpid());
	if(mkfifo(clientFifo, S_IRUSR|S_IWUSR|S_IWGRP) == -1 && errno != EEXIST)
	{
		printf("mkfifo %s fail, %s\n", clientFifo, strerror(errno));
		return -1;
	}
	if(atexit(removeFifo)!=0)
	{
		printf("%s\n", strerror(errno));
		return -1;
	}
	req.pid = getpid();
	req.seqLen = (argc > 1) ? atoi(argv[1]) :1;
	while(1)
	{
	serverFd = open(SERVER_FIFO,O_WRONLY);
	if(serverFd == -1)
	{
		printf("%s\n", strerror(errno));
		return -1;
	}
	if(write(serverFd, &req, sizeof(struct request)) != sizeof(struct request))
	{
		printf("write to server failed:%s\n", strerror(errno));
		return -1;
	}
	close(serverFd);

	clientFd = open(clientFifo, O_RDONLY|O_NONBLOCK);
	if(clientFd == -1)
	{
		printf("open %s fail, %s\n", clientFifo,strerror(errno));
		return -1;
	}
	int ret = 0;
	if((ret = read(clientFd, &resp, sizeof(struct  response)) )==-1 && errno != EAGAIN)
	{
		printf("read  clientfd fail, %s\n", strerror(errno));
		return -1;
	}
	else if(ret == 0)
	{
		printf("other closed\n");
		continue;
	}
	else if(ret != sizeof(struct response))
	{
		printf("read failed %d\n",ret);
		continue;
	}
	printf("%d\n", resp.seqNum);
	}
	exit(EXIT_SUCCESS);
}
