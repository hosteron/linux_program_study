#include <sys/un.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
int main(int argc ,char **argv)
{
	struct sockaddr_un addr;
	addr.sun_family = AF_UNIX;
	remove("/tmp/sockc");
	strncpy(addr.sun_path, "/tmp/sockc", sizeof(addr.sun_path));
	int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if(fd == -1)
	{
		printf("create  socket fail\n");
		return -1;
	}
	bind(fd , (struct sockaddr *)&addr, sizeof(struct sockaddr_un));

	char buf[128] = {0};
	struct sockaddr_un saddr;
	saddr.sun_family = AF_UNIX;
	strncpy(saddr.sun_path, "/tmp/socka", sizeof(saddr.sun_path));
	int ret = sendto(fd, argv[1], strlen(argv[1]), 0, (struct sockaddr *)&saddr, sizeof(saddr));
	if(ret == -1)
	{
		printf("sendto error :%s\n", strerror(errno));
		return -1;
	}
	int addrlen = sizeof(saddr);
	recvfrom(fd , buf, sizeof(buf), 0, (struct sockaddr *)&saddr, &addrlen);
	printf("recieve from :%s:response:%s\n", saddr.sun_path, buf);
	#if 0
	while(1)
	{
		struct sockaddr_un c_addr;
		int addrlen = sizeof(c_addr);
		int num = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr *)&c_addr, &addrlen);
		if(num == -1)
		{
			printf("recvfrom fail\n");
			return -1;
		}

		printf("recvfrom:%s:%d,%s\n", c_addr.sun_path, num, buf);

		int i;
		for(i = 0; i <  num; i++)
		{
			buf[i] = toupper(buf[i]);
		}
		sendto(fd, buf, num,  0, (struct sockaddr *)&c_addr, addrlen);
	}
	#endif
}
