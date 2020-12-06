#include <mqueue.h>
#include <signal.h>
#include "tlpi_hdr.h"
struct mq_seqnum{
	int pid;
	int length;
};
char buf[64];
void func()
{
	//char buf[32];
	printf("buf=%s\n", buf);
	mq_unlink(buf);
}
int main(int argc ,char **argv)
{
	if(argc != 2)
	{
		printf("%s <len>\n", argv[0]);
		return -1;
	}
	pid_t pid = getpid();
	//char tmpbuf[64] = {0};
	//sprintf(tmpbuf,"/client%ld", (long)pid);
	//printf("sizeof(buf)=%d\n", sizeof(buf));
	int n = sprintf(buf, "/client_%ld", (long)pid);
	//int n = 0;
	printf("filename =%s, %ld, n = %d, %s\n", buf, (long)getpid(), n, strerror(errno));
	mqd_t mqd = mq_open(buf, O_RDWR|O_CREAT, 0664, NULL);
	//mqd_t  mqd = mq_open(buf, O_RDONLY|O_CREAT|O_EXCL,0664);
	//mqd_t  mqd = mq_open("/client_test", O_RDONLY|O_CREAT,0664);
	if(mqd == (mqd_t)-1)
		errExit("mq_open");
	atexit(func);
	//return -1;
	mqd_t mqd_s = mq_open("/mq_server", O_WRONLY);
	if(mqd_s == (mqd_t)-1)
		errExit("mq_open 2");
	struct mq_seqnum  req;
	req.pid = pid;
	req.length = atoi(argv[1]);
	int snd = mq_send(mqd_s, &req, sizeof(req), 0);
	printf("snd = %d\n", snd);
	
	struct mq_attr attr;
	mq_getattr(mqd, &attr);
	int seq;
	printf("msgsize=%d,sizeof(seq)=%d\n", attr.mq_msgsize, sizeof(seq));
	void *buffer = (void *)malloc(attr.mq_msgsize);
	
	int numRead = mq_receive(mqd, buffer, attr.mq_msgsize, NULL);
	seq = *((int*)buffer);
	printf("numRead= %d, seq= %d ,%s\n", numRead, seq, strerror(errno));

}
