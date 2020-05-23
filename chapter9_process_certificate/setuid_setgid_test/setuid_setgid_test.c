#include <stdio.h>
#include <unistd.h>
#include "tlpi_hdr.h"
int main()
{
		printf("uid:%d, gid:%d, euid:%d,egid:%d\n", getuid(), getgid(), geteuid(), getegid());
		#if 0
		if(setuid(getuid()) == -1)
			errExit("setuid");
		if(setgid(getgid()) == -1)
			errExit("setgid");
		#endif
		uid_t euid = geteuid();
		if(seteuid(getuid()) == -1)
			errExit("seteuid");
		uid_t egid = getegid();
		if(setegid(getgid()) == -1)
			errExit("setegit");
		printf("uid:%d, gid:%d, euid:%d,egid:%d\n", getuid(), getgid(), geteuid(), getegid());
		if(seteuid(euid) == -1)
			errExit("seteuid");
		if(setegid(egid) == -1)
			errExit("setegid");
		printf("uid:%d, gid:%d, euid:%d,egid:%d\n", getuid(), getgid(), geteuid(), getegid());
}
