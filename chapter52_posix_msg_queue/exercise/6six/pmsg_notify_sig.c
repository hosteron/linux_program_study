#include <signal.h>
#include <mqueue.h>
#include <fcntl.h>
#include "tlpi_hdr.h"
#define NOTIFY_SIG SIGUSR1
static void handler(int sig)
{
	;
}
int main(int argc ,  char **argv)
{
	struct sigevent sev;
	mqd_t mqd;
	struct mq_attr attr;
	void *buffer;
	ssize_t numRead;
	sigset_t  blockMask, emptyMask;
	struct sigaction sa;
	if(argc !=2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s mq-name\n", argv[0]);
	mqd = mq_open(argv[1], O_RDONLY | O_NONBLOCK);
	if(mqd ==(mqd_t)-1)
		errExit("mq_open");
	printf("create mq descriptor = %d\n", mqd);
	if(mq_getattr(mqd, &attr) == -1)
		errExit("mq_getattr");
	buffer = malloc(attr.mq_msgsize);
	if(buffer == NULL)
		errExit("malloc");
	sigemptyset(&blockMask);
	sigaddset(&blockMask, NOTIFY_SIG);
	if(sigprocmask(SIG_BLOCK, &blockMask, NULL) == -1)
		errExit("sigprocmask");
	//sigemptyset(&sa.sa_mask);
	//sa.sa_flags = 0;
	//sa.sa_handler = handler;
	//if(sigaction(NOTIFY_SIG, &sa, NULL) == -1)
		//errExit("sigaction");
	sev.sigev_notify= SIGEV_SIGNAL;
	sev.sigev_signo = NOTIFY_SIG;
	sev.sigev_value.sival_ptr = &mqd;
	if(mq_notify(mqd, &sev) == -1)
		errExit("mq_notify");
	sigemptyset(&emptyMask);
	
	for(;;)
	{
		//sigsuspend(&emptyMask);
		siginfo_t info;
		sigwaitinfo(&blockMask, &info);
		mqd_t *tmp = (mqd_t *)info.si_value.sival_ptr;
		printf("sig received:sig=%d,si_code=%d, SI_MESGQ = %d,mqd = %d\n", info.si_signo, info.si_code,SI_MESGQ, *tmp);
		if(mq_notify(mqd, &sev) == -1)
			errExit("mq_notify");
		while((numRead = mq_receive(mqd, buffer, attr.mq_msgsize, NULL)) >= 0)
			printf("Read %ld bytes\n", (long)numRead);
		if(errno != EAGAIN)
			errExit("mq_recieve");
	}
}
