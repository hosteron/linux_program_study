#define _XOPEN_SOURCE 500
#include <ftw.h>
#include <sys/inotify.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
static int inotifyFd = -1;
int nftw_func(const char *pathname, const struct stat *statbuf, int typeflag, struct FTW *ftwbuf)
{
		//printf("%s \n", pathname);
		if(typeflag == FTW_D && inotifyFd > 0)
		{
				int fd = inotify_add_watch(inotifyFd,pathname, IN_CREATE|IN_DELETE|IN_MOVED_FROM|IN_MOVED_TO|IN_DONT_FOLLOW|IN_ONLYDIR);
				if(fd < 0)
				{
						printf("add %s watch fail\n", pathname);
						return -1;
				}
		}
		return 0;
}
#define BUF_LEN (10*(sizeof(struct inotify_event)+NAME_MAX+1))
int main(int argc , char **argv)
{
		char  *p = NULL;
		char buf[BUF_LEN] = {0};
		struct inotify_event *event = NULL;
		if(argc < 2 || !strcmp(argv[1], "--help"))
		{
			printf("%s dirname\n", argv[0]);
			return -1;
		}
		struct stat st;
		if(stat(argv[1], &st))
		{
				printf("%s is not exsit\n", argv[1]);
				return -1;
		}
		if(!S_ISDIR(st.st_mode))
		{
				printf("%s is not directory\n", argv[1]);
				return -1;
		}
		inotifyFd = inotify_init();
		if(inotifyFd < 0 )
		{
			printf("inotify_init fail\n");
			return -1;
		}
		int ret = nftw(argv[1], nftw_func, 10, FTW_PHYS);
		printf("nftw ret = %d\n",ret);
		
		while(1)
		{
				ret = read(inotifyFd, buf, sizeof(buf));
				if(ret <=0)
				{
						printf("read fail\n");
						return -1;
				}
				printf("read %d bytes frome inotify fd\n", ret);
				for(p = buf;p < buf+ret;)
				{
					event = (struct inotify_event *)p;
					if((event->mask & IN_CREATE) && (event->mask &IN_ISDIR))
					{
							#if 0
							if(event->len > 0)
							{
								int fd = inotify_add_watch(inotifyFd, event->name, IN_CREATE|IN_DELETE|IN_MOVED_FROM|IN_MOVED_TO|IN_DONT_FOLLOW|IN_ONLYDIR);
								if(fd < 0)
								{
										printf("add %s  watch fail\n", event->name);
										return -1;
								}
							}
							#endif
							int ret1 = nftw(argv[1], nftw_func, 10, FTW_PHYS);
							printf("nftw ret = %d\n",ret1);
					}
					else if((event->mask & IN_MOVED_TO) && (event->mask &IN_ISDIR))
					{
						#if 0
						if(event->len > 0)
							{
								int fd = inotify_add_watch(inotifyFd, event->name, IN_CREATE|IN_DELETE|IN_MOVED_FROM|IN_MOVED_TO|IN_DONT_FOLLOW|IN_ONLYDIR);
								if(fd < 0)
								{
										printf("add %s  watch fail\n", event->name);
										return -1;
								}
							}
						#endif
						int ret1 = nftw(argv[1], nftw_func, 10, FTW_PHYS);
						printf("nftw ret = %d\n",ret1);
					}
					if(event->mask & IN_CREATE) printf("IN_CREATE ");
					if(event->mask & IN_DELETE) printf("IN_DELETE ");
					if(event->mask & IN_MOVED_FROM) printf("IN_MOVED_FROM ");
					if(event->mask & IN_MOVED_TO) printf("IN_MOVED_TO ");
					if(event->mask & IN_ISDIR ) printf("IN_ISDIR ");
					if(event->mask & IN_IGNORED) printf("IN_IGNORED ");
					if(event->mask & IN_UNMOUNT) printf("IN_UNMOUNT ");
					printf("\n");
					if(event->len )
						printf("		name = %s\n", event->name);
					p += sizeof(struct inotify_event)+event->len;
				}
		}
}
