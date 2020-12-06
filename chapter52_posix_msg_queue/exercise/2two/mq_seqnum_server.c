#include <mqueue.h>
#include <signal.h>
#include "tlpi_hdr.h"
struct mq_seqnum{
	int pid;
	int length;
};
void handler(int sig)
{

}
void handler1(int sig)
{
	exit(1);
}
void func()
{
	printf("run in this way\n");
	mq_unlink("/mq_server");
}
int main(int argc ,char **argv)
{
	int seq = 0;
	mqd_t mqd;
	mqd = mq_open("/mq_server", O_RDONLY|O_CREAT|O_NONBLOCK, 0664, NULL);
	if(mqd == (mqd_t)-1)
		errExit("mq_open");
	atexit(func);
	struct mq_attr attr;
	if(mq_getattr(mqd, &attr) == -1)
		errExit("mq_getattr");
	void *buffer = malloc(attr.mq_msgsize);
	if(!buffer)
		errExit("malloc");
	sigset_t blockMask, emptyMask;
	struct sigaction sa;
	sigemptyset(&blockMask);
	sigaddset(&blockMask,  SIGUSR1);
	sigprocmask(SIG_BLOCK, &blockMask, NULL);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	sigaction(SIGUSR1,&sa, NULL);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	sigaction(SIGINT, &sa, NULL);
	struct sigevent sev;
	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIGUSR1;
	if(mq_notify(mqd, &sev) == -1)
		errExit("mq_notify");
	
	sigemptyset(&emptyMask);
	int numRead = 0;
	for(;;)
	{
		sigsuspend(&emptyMask);
		if(mq_notify(mqd, &sev) == -1)
			errExit("mq_notify");
		while((numRead = mq_receive(mqd, buffer, attr.mq_msgsize, NULL)) >=0)
		{
			if(numRead != sizeof(struct mq_seqnum))
			{
				printf("recieve err\n");
				return -1;
			}

			struct mq_seqnum *req = (struct mq_seqnum *)buffer;
			printf("pid=%d, len = %d\n", req->pid, req->length);
			char buf[32] = {0};
			snprintf(buf, sizeof(buf), "/client_%ld", (long)req->pid);
			mqd_t mqd_c = mq_open(buf, O_WRONLY);
			if(mqd_c == (mqd_t) -1)
				errExit("mq_open 2");
			seq += req->length;
			int ret= mq_send(mqd_c, &seq, sizeof(seq), 0);
			printf("send = %d\n", ret);
			mq_close(mqd_c);
		}

		if(errno != EAGAIN)
			errExit("mq_recieve");
	}

}
