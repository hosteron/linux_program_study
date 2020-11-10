#include "svmsg_file.h"
#include <syslog.h>
int serverId;
static void grimReaper(int sig)
{
	int savedErrno;
	savedErrno = errno;
	while(waitpid(-1, NULL, WNOHANG) > 0)
		continue;
	errno = savedErrno;
}
void onExit()
{	
	printf("%s:%d\n", __func__, __LINE__);
	msgctl(serverId, IPC_RMID, NULL);
	closelog();
}
static void serverRequest(const struct requestMsg *req)
{
	int fd ;
	ssize_t numRead;
	struct responseMsg resp;
	int ret = 0;
	fd = open(req->pathname, O_RDONLY);
	if(fd == -1)
	{
		syslog(LOG_ERR, "%s", strerror(errno));
		resp.mtype = RESP_MT_FAILURE;
		snprintf(resp.data, sizeof(resp.data), "%s", "Couldnt open");
		ret = msgsnd(req->clientId, &resp, strlen(resp.data)+1, 0);
		if(ret == -1)
		{
			syslog(LOG_ERR, "msgsnd %s", strerror(errno));
		}
		exit(EXIT_FAILURE);
	}

	resp.mtype = RESP_MT_DATA;
	while((numRead = read(fd, resp.data, RESP_MSG_SIZE )) > 0)
		if(msgsnd(req->clientId, &resp, numRead, 0) == -1)
			break;
	if(numRead == -1)
	{
		syslog(LOG_ERR, "%s", strerror(errno));
	}
	resp.mtype = RESP_MT_END;
	msgsnd(req->clientId, &resp, 0, 0);
}

void handler(int sig)
{
	psignal(sig,"recieve signal:");
	fflush(stdout);
	//clear source
	msgctl(serverId, IPC_RMID, NULL);
	unlink(SERVER_KEY_FILE);
	closelog();
	//end of clear source
	signal(sig, SIG_DFL);
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, sig);
	sigset_t preSet;
	sigprocmask(SIG_UNBLOCK, &set, &preSet);
	raise(sig);
}
int main(int argc, char **argv)
{
#if 0
	switch(fork())
	{
		case -1:errExit("fork");
		case 0:break;
		default:_exit(EXIT_SUCCESS);
	}
	if(setsid() == -1)
	{
		errExit("setsid");
	}
	switch(fork())
	{
		case -1:errExit("fork2");
		case 0:break;
		default:_exit(EXIT_SUCCESS);
	}
	close(STDIN_FILENO);
	int fd_std = open("/dev/null", O_RDWR);
	if(fd_std != STDIN_FILENO);
		errExit("fd_std");
	if(dup2(STDIN_FILENO, STDOUT_FILENO) != STDOUT_FILENO);
		errExit("dup2 in-out");
	if(dup2(STDIN_FILENO, STDERR_FILENO)!= STDERR_FILENO);
		errExit("dup2 in-err");
#endif
	struct requestMsg req;
	pid_t pid;
	ssize_t  msgLen;
	struct sigaction sa;
	//serverId = msgget(SERVER_KEY, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR | S_IWGRP);
	serverId = msgget(IPC_PRIVATE, S_IRUSR|S_IWUSR|S_IWGRP);
	if(serverId == -1)
		errExit("msgget");
	int fd = open(SERVER_KEY_FILE, O_CREAT|O_CLOEXEC|O_TRUNC|O_RDWR, 0664);
	if(fd  == -1 )
	{
		errExit("open");
	}
	openlog(argv[0], LOG_PID, LOG_LOCAL6|LOG_DEBUG);
	printf("serverId = %d\n", serverId);
	int len = write(fd, &serverId, sizeof(serverId));
	printf("write size = %d\n", len);
	fsync(fd);
	close(fd);
	atexit(onExit);
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handler;
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGINT,&sa, NULL);

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = grimReaper;
	if(sigaction(SIGCHLD, &sa, NULL) == -1)
		errExit("sigaction");
	for(;;)
	{
		msgLen = msgrcv(serverId, &req, REQ_MSG_SIZE, 0, 0);
		if(msgLen == -1)
		{
			if(errno == EINTR)
				continue;
			errMsg("msgrcv");
			break;
				
		}
		pid = fork();
		if(pid == -1)
		{
			errMsg("fork");
			break;
		}
		if(pid == 0)
		{
			serverRequest(&req);
			_exit(EXIT_SUCCESS);
		}
	}
	//if(msgctl(serverId, IPC_RMID, NULL) == -1)
		//errExit("msgctl");
	exit(EXIT_SUCCESS);
	
}
