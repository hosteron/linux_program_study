#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <pwd.h>
int main()
{
	printf("uid:%d\n", getuid());
	pid_t uid = getuid();
	struct passwd *pw = getpwuid(uid);
	if(pw)
	printf("name=%s\n", pw->pw_name);
	int fd = open("test.txt", O_RDONLY);
	if(fd < 0)
	{
		printf("open fail:%s\n",strerror(errno));
		return -1;
	}

	printf("open success\n");
	close(fd);

}
