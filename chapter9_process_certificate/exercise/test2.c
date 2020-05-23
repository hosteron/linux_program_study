#include <stdio.h>
#include <unistd.h>
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
	uidgidprint();
	int ret = setreuid(-1, 1000);
	printf("ret = %d\n", ret);
	uidgidprint();
	uid_t uid;
	uid_t euid;
	uid_t suid;
	if(getresuid(&uid, &euid, &suid) == -1)
	{
			printf("getresuid fail\n");
			return -1;
	}
	ret =  setresuid(0, 0,0);
	printf("ret = %d\n", ret);
	uidgidprint();
}
