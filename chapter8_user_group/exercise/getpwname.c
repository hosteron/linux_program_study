#include <stdio.h>
#include <pwd.h>
struct passwd *mygetpwnam(const char *name)
{
		if(!name) return NULL;
		setpwent();
		struct passwd *pwd;
		while((pwd = getpwent()) != NULL)
		{
				if(!strcmp(pwd->pw_name , name))
				{
						break;
				}
		}
		endpwent();
		return pwd;
		
}
int main(int argc , char **argv)
{
		printf("%ld %ld\n", (long)(getpwnam("xiangzhou")->pw_uid), (long)(getpwnam("root")->pw_uid));
		struct passwd *pwd = mygetpwnam(argv[1]);
		if(pwd)
		printf("mygetpwnam(\"%s\") uid = %d\n", argv[1], pwd->pw_uid);
		else
		printf("mygetpwnam return null\n");
}
