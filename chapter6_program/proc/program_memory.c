#include <stdio.h>
#include <gnu/libc-version.h>
#include <stdlib.h>
#include <unistd.h>
extern char etext;
extern char edata;
extern char end;
int main(int argc ,char **argv, char **envp)
{
	printf("argv=%p\n", argv);
	printf("envp=%p\n", envp);
	printf("etext=%p\n", &etext);
	printf("edata=%p\n", &edata);
	printf("end=%p\n", &end);
	printf("libc=%s\n", gnu_get_libc_version());
	printf("%d:%d\n", __GLIBC__,__GLIBC_MINOR__);
	printf("pid=%d\n", getpid());
	printf("pagesize=%ld\n", sysconf(_SC_PAGESIZE));
	//sleep(30);
}
