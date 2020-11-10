#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/msg.h>
#include "tlpi_hdr.h"
#define MAX_MTEXT 1024
struct mbuf{
	long mtype;
	char mtext[MAX_MTEXT];
};
static void  usageError(const char *progName, const char *msg)
{
	if(msg != NULL)
		fprintf(stderr, "%s", msg);
	fprintf(stderr, "Usage: %s [option] msqid [max-bytes]\n", progName);
	fprintf(stderr, "	-e Use MSG_NOERROR flag\n");
	fprintf(stderr, "	-t type Select message of given type\n");
	fprintf(stderr, "	-n	Use IPC_NOWAIT flag\n");
#ifdef MSG_EXCEPT
	fprintf(stderr, "	-x	Use MSG_EXCEPT flag\n");
#endif
	exit(EXIT_FAILURE);
}
int main(int argc, char *argv[])
{
	int msqid, flags, type;
	ssize_t msgLen;
	size_t maxBytes;
	struct mbuf msg;
	int opt;
	flags = 0;
	type = 0;
	while((opt = getopt(argc, argv, "ent:x")) != -1)
	{
		switch(opt)
		{
			case 'e': flags |= MSG_NOERROR;break;
			case 'n': flags |= IPC_NOWAIT;break;
			case 't': type = atoi(optarg); break;
		#ifdef MSG_EXCEPT
			case 'x': flags |= MSG_EXCEPT;break;
		#endif
			default:
			usageError(argv[0], NULL);
		}
	}
	if(argc < optind + 1 || argc > optind + 2)
		usageError(argv[0], "Wrong number of arguments\n");
	msqid = getInt(argv[optind], 0, "msgqid");
	maxBytes = (argc > optind+1) ? getInt(argv[optind+1], 0, "max-bytes"):MAX_MTEXT;
	msgLen = msgrcv(msqid, &msg, maxBytes, type, flags);
	if(msgLen == -1)
		errExit("msgrcv");
	printf("Received: type = %ld, length=%ld", msg.mtype, (long)msgLen);
	if(msgLen > 0)
		printf("; body=%s", msg.mtext);
	printf("\n");
	exit(EXIT_SUCCESS);
}
