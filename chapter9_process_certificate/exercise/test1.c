#include <stdio.h>
#include <unistd.h>
#include <sys/fsuid.h>
void uidgidprint()
{
		uid_t uid;
		uid_t euid;
		uid_t suid;
		int ret = setfsuid(-1);
		if(getresuid(&uid, &euid, &suid) == -1)
			printf("getresuid error\n");
		printf("UID:%d %d %d %d \n", uid, euid, suid, ret);
}
int main()
{
	printf("%d\n", getpid());
	uidgidprint();
	setresuid(-1, 1001, 117);
	uidgidprint();
}
