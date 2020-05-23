#define _GNU_SOURCE
#include <pwd.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>
#include <unistd.h>
#include <sys/fsuid.h>
#include <limits.h>
#include <grp.h>
#define SG_SIZE (NGROUPS_MAX+1)
int isDoubleList(gid_t *list,gid_t gid, size_t size, size_t cnt)
{
		int i;
		for(i = 0; i< size && i < cnt; i++ )
		{
				if(gid == list[i])
				return 1;
		}
		return 0;
}
int myinitgroups(const char *user, gid_t group)
{
		if(!user) return -1;
		gid_t list[SG_SIZE] = {0};
		int cnt = 0;
		struct passwd *pw = getpwnam(user);
		if(!pw)
		{
			printf("%s is  not exsit\n", user);
			return -1;	
		}
		if(!isDoubleList(list, pw->pw_gid, SG_SIZE, cnt))
		{
				list[cnt++] = pw->pw_gid;
		}
		struct group *gr = getgrent();
		while(gr)
		{
				char **m = gr->gr_mem;
				//printf("%d\n",  gr->gr_gid);
				int flag =0;
				while(m && *m)
				{

						if(!strcmp(*m, user))
						{
								flag = 1;
								break;
						}
						m++;
				}
				if(flag)
				{
					if(!isDoubleList(list, gr->gr_gid, SG_SIZE, cnt))
					{
							list[cnt++] = gr->gr_gid;
					}
				}

			gr = getgrent();
		}
		endgrent();
		
		if(!isDoubleList(list, group, SG_SIZE, cnt))
		{
				list[cnt++] = group;
		}
		int j;
		for(j = 0; j < cnt ; j++)
		{
				printf("%d ", list[j]);
		}
		printf("\n");
		return 0;
}
int main(int argc, char **argv)
{
		int ret = myinitgroups(argv[1], atoi(argv[2]));
		printf("ret = %d\n", ret);
}
