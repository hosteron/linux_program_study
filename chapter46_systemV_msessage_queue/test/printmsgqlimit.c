#define _GNU_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/ipc.h>
int msgid = 0;
void onexit()
{
	msgctl(msgid,IPC_RMID, NULL);
}
int main()
{
	//printf("MSGMNB=%d\n", MSGMNB);
	atexit(onexit);
	msgid = msgget(IPC_PRIVATE,S_IRUSR|S_IWUSR);
	struct msqid_ds buf;
	msgctl(msgid, IPC_STAT, &buf);
	printf("msg_qbytes:%d\n", buf.msg_qbytes);
}
