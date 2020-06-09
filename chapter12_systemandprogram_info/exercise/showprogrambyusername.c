#include <stdio.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>//pw_uid
#include <dirent.h>
int main(int argc , char **argv)
{
		if(argc != 2)
		{
			printf("should be %s username\n", argv[0]);
			return -1;
		}
		errno = 0;
		struct passwd *pw = getpwnam(argv[1]);
		if(!pw)
		{
				if(errno)
				{
							printf("%s\n", strerror(errno));
				}
				else
				{
						printf("this no match one\n");
				}
				return -1;
		}
		DIR *dir =  opendir("/proc");
		if(!dir)
		{
				printf("open dir fail\n");
				return -1;
		}
		struct dirent *p = NULL;
		while((p = readdir(dir)))
		{
				if(p->d_type == DT_DIR && strcmp(p->d_name, ".") && strcmp(p->d_name, ".."))
				{
						char *ptr = NULL;
						long long pid = strtol(p->d_name, &ptr, 0);
						if(ptr && *ptr != '\0')
							continue;
						char filename[32] = {0};
						snprintf(filename, sizeof(filename), "/proc/%lld/status", pid);
						FILE * fd = fopen(filename, "rb");
						if(fd == NULL)
						{
								printf("open file:%s fail\n", filename);
								continue;
						}
						char buf[256] = {0};
						char *line = NULL;
						char name[128] = {0};
						while((line = fgets(buf, sizeof(buf), fd)))
						{
								char *a = strstr(buf, "Name:");
								
								if(a)
								{
									strncpy(name, &buf[strlen("Name:")], sizeof(name));
									//b = ;
									continue;
								}
								a= strstr(buf, "Uid:");
								if(a)
								{
										char *c = &buf[strlen("Uid:")];
										char *d = NULL;
										long long  id = strtol(c, &d, 0);
										if(d!= NULL)
										{
												if(pw->pw_uid == id)
												{
														//或者在这地方读取/proc/pid/cmdline就可以知道命令的名称了，这里我就不做多处理了
														printf("pid = %lld,name:%s",pid, name);
														break;
												}
										}
								}
								memset(buf, 0, sizeof(buf));
						}
						fclose(fd);
				}
		}
		closedir(dir);
}
