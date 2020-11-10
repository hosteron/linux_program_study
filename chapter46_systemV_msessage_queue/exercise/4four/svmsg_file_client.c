#include "svmsg_file.h"
static int clientId;
static void removeQueue(void)
{
	if(msgctl(clientId, IPC_RMID, NULL) == -1)
		errExit("msgctl");
}

int main(int argc, char **argv)
{
	struct requestMsg req;
	struct responseMsg resp;
	int serverId, numMsgs;
	ssize_t msgLen , totBytes;
	if(argc != 2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s pathname\n", argv[0]);
	if(strlen(argv[1]) > sizeof(req.pathname) - 1)
		cmdLineErr("pathname too long (max: %ld bytes)\n", (long) sizeof(req.pathname) -1);
	int fd = open(SERVER_KEY_FILE, O_RDONLY|O_CLOEXEC);
	if(fd == -1)
		errExit("open");
	
	//serverId = msgget(SERVER_KEY, S_IWUSR);
	//if(serverId == -1)
		//errExit("msgget - server message queue");
	read(fd, &serverId, sizeof(serverId));
	printf("serverId = %d\n", serverId);
	close(fd);

	clientId = msgget(IPC_PRIVATE, S_IRUSR | S_IWUSR | S_IWGRP);
	if(clientId == -1)
		errExit("msgget -client message queue");
	if(atexit(removeQueue) != 0)
		errExit("atexit");
	req.mtype = 1;
	req.clientId = clientId;
	strncpy(req.pathname, argv[1], sizeof(req.pathname));
	req.pathname[sizeof(req.pathname) - 1] = '\0';
	printf("serverid=%d\n", serverId);
	if(msgsnd(serverId, &req, REQ_MSG_SIZE, 0) == -1)
		errExit("msgsnd");
	printf("run in this way\n");
	msgLen = msgrcv(clientId, &resp, RESP_MSG_SIZE, 0, 0);
	if(msgLen == -1)
		errExit("msgrcv");
	if(resp.mtype == RESP_MT_FAILURE){
		printf("%s\n", resp.data);
		if(msgctl(clientId, IPC_RMID, NULL) == -1)
			errExit("msgctl");
		exit(EXIT_FAILURE);
	}

	totBytes = msgLen;
	for(numMsgs = 1; resp.mtype == RESP_MT_DATA; numMsgs++)
	{
		msgLen = msgrcv(clientId, &resp, RESP_MSG_SIZE, 0, 0);
		if(msgLen == -1)
			errExit("msgrcv");
		totBytes += msgLen;
	}
	printf("Received %ld bytes (%d messages)\n", (long)totBytes, numMsgs);
	exit(EXIT_SUCCESS);
}
