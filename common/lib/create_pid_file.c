#include <sys/stat.h>
#include <fcntl.h>
#include "region_locking.h"
#include "create_pid_file.h"
#include "tlpi_hdr.h"
#define BUF_SIZE 100

int createPidFile(const char *progName, const char *pidFile, int flags)
{
	int fd;
	char buf[BUF_SIZE];
	fd = open(pidFile, O_RDWR|O_CREAT,S_IRUSR|S_IWUSR);
	if(fd == -1)
		errExit("Could not open PID file %s", pidFile);
	if(flags & CPF_CLOEXEC)
	{
		flags = fcntl(fd, F_GETFD);
		if(flags == -1)
			errExit("Could not get flags for PID file %s", pidFile);
		flags |= FD_CLOEXEC;
		if(fcntl(fd, F_SETFD,flags) == -1)
			errExit("Could not set flags for PID file %s", pidFile);
	}

	if(lockRegion(fd, F_WRLCK, SEEK_SET,0, 0)== -1){
		if(errno == EAGAIN || errno == EACCES)
			fatal("PID file '%s' is locked; probably '%s' is already running", pidFile, progName);
		else
			errExit("Unable to lock PID FILE '%s'", pidFile);
	}

	if(ftruncate(fd, 0) == -1)
		errExit("Could not truncate PID file '%s'", pidFile);
	snprintf(buf, BUF_SIZE,"%ld\n", (long)getpid());
	if(write(fd, buf, strlen(buf))!= strlen(buf))
		fatal("Writing to PID file '%s'", pidFile);


	return fd;
}
