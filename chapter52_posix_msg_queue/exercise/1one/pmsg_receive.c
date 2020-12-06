#include <mqueue.h>
#include <fcntl.h>
#include "tlpi_hdr.h"
#include <time.h>
static void usageError(const char *progName)
{
	fprintf(stderr, "Usage: %s [-n] -t <secs>name\n", progName);
	fprintf(stderr, "	-n	Use O_NOBLOCK flag\n");
	exit(EXIT_FAILURE);
}
int main(int argc, char **argv)
{
	int flags , opt;
	mqd_t mqd;
	unsigned int prio;
	void *buffer;
	struct mq_attr attr;
	ssize_t numRead;
	flags = O_RDONLY;
	int t;
	while((opt = getopt(argc, argv, "nt:")) != -1)
	{
		switch(opt)
		{
			case 'n': flags |= O_NONBLOCK;break;
			case 't': t = atoi(optarg); break;
			default:usageError(argv[0]);
		}
	}
	if(optind >= argc)
	{
		usageError(argv[0]);
	}

	mqd = mq_open(argv[optind], flags);
	if(mqd == (mqd_t ) -1)
		errExit("mq_open");
	if(mq_getattr(mqd, &attr) == -1)
		errExit("mq_getattr");
	buffer = malloc(attr.mq_msgsize);
	if(buffer == NULL)
		errExit("malloc");
	struct timespec sp;
	clock_gettime(CLOCK_REALTIME, &sp);
	sp.tv_sec += t;
	//numRead = mq_receive(mqd, buffer, attr.mq_msgsize, &prio);
	numRead = mq_timedreceive(mqd, buffer, attr.mq_msgsize, &prio, &sp);
	if(numRead == -1)
		errExit("mq_receive");
	printf("Read %ld bytes ; priority = %u\n", (long)numRead , prio);
	if(write(STDOUT_FILENO, buffer, numRead) == -1)
		errExit("write");
	write(STDOUT_FILENO, "\n", 1);
	exit(EXIT_SUCCESS);
}
