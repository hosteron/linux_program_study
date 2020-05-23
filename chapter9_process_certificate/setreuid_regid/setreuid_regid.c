#include <stdio.h>
#include <unistd.h>
#include "tlpi_hdr.h"
void uidgidprint()
{
		uid_t uid;
		uid_t euid;
		uid_t suid;
		gid_t gid;
		gid_t egid;
		gid_t sgid;
		if(getresuid(&uid, &euid, &suid) == -1)
			errExit("getresuid");
		if(getresgid(&gid, &egid, &sgid) == -1)
			errExit("getresgid");
		printf("UID:%d %d %d\n", uid, euid, suid);
		printf("GID:%d %d %d\n", gid, egid, sgid);
}
int main()
{
	printf("pid= %d\n", getpid());
	printf("uid:%d, euid:%d, gid:%d, egid:%d\n", getuid(), geteuid(), getgid(), getegid());
	uid_t uid =  getuid();
	uid_t euid = geteuid();
	gid_t gid = getgid();
	gid_t egid = getegid();
	if(setreuid(getuid(), -1) == -1)
		errExit("set uid to effective user id");
	printf("uid:%d, euid:%d, gid:%d, egid:%d\n", getuid(), geteuid(), getgid(), getegid());
	
	if(setreuid(uid, -1) == -1)
		errExit("set uid to initial user id");
	printf("uid:%d, euid:%d, gid:%d, egid:%d\n", getuid(), geteuid(), getgid(), getegid());
	
	//------------------
	
	if(setregid(getgid(), -1) == -1)
		errExit("setregid");
	//uidgidprint();
	if(setregid(gid , -1) == -1)
		errExit("setregid");
	printf("uid:%d, euid:%d, gid:%d, egid:%d\n", getuid(), geteuid(), getgid(), getegid());
	
	//-----------------
	printf("effective\n");
	if(setreuid(-1, geteuid()) == -1)
		errExit("setreuid effective");
	uidgidprint();
	
	if(setreuid(-1, euid) == -1)
		errExit("setreuid recover\n");
	uidgidprint();
	#if 0
	if(setreuid(getuid(), getuid()) == -1)
		errExit("setreuid finish");
	uidgidprint();
	#endif
	
	int fsid = setfsuid(-1);//不管失败成功，都返回之前的文件系统id
	printf("fsid =%d\n", fsid);
	
	#define GROUP_SIZE 9
	gid_t list[GROUP_SIZE] = {0};
	int ret = getgroups(GROUP_SIZE, list);
	if(ret == -1)
		errExit("getgroups");
	printf("groups num = %d\n", ret);
	int i;
	for(i = 0; i < ret; i++)
		printf("%d ", list[i]);
	printf("\n");
	
	gid_t list_re[2] = {0};
	ret = setgroups(2, list_re);
	if(ret == -1)
		errExit("setgroups");
	
	ret = getgroups(GROUP_SIZE, list);
	printf("after setgroups ret:%d\n", ret);
	for(i = 0; i < ret; i++)
		printf("%d ", list[i]);
	printf("\n");
	
}
