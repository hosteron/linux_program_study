#define _GNU_SOURCE	
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
int main(int argc, char **argv)
{
	printf("PID:%ld\n", (long)getpid());
	void *handle = dlopen(argv[1], RTLD_NOW);
	char *p = dlerror();
	if(p)
	{
		printf("%s, dlopen fail\n", p);
		return -1;
	}
	typedef void (*func)(void);
	func fp = (void (*)(void))dlsym(handle, argv[2]);
	p = dlerror();
	if(p )
	{
		printf("%s, dlsym fail\n", p);
		dlclose(handle);
		return -1;
	}
	Dl_info info;
	printf("fp:%p\n", fp);
	printf("----------info-----------------\n");
	dladdr(fp,&info);
	printf("fname:%s\n", info.dli_fname);
	printf("fbase:%p\n", info.dli_fbase);
	printf("sname:%s\n", info.dli_sname);
	printf("saddr:%p\n", info.dli_saddr);
	printf("---------end------------------\n");
	mineprint1();
	fp();
	sleep(10);
	printf("about to  dlclose\n");
	dlclose(handle);
	sleep(10);
	printf("program exit\n");
}
