#include <pwd.h>
#include <grp.h>
#include <stdio.h>
int main()
{
		struct passwd *pwd;
		while((pwd = getpwent()) != NULL)
			printf("%-8s %5ld\n", pwd->pw_name , pwd->pw_uid);
		setpwent();
		endpwent();
		struct group * grp;
		while((grp = getgrent()) != NULL)
			printf("%-8s %5ld\n", grp->gr_name, grp->gr_gid);
		setgrent();
		endgrent();
}
