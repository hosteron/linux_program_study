#include <sys/un.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
int main()
{
	struct sockaddr_un addr;
	addr.sun_family = AF_UNIX;
	remove("/tmp/socka");
	strncpy(addr.sun_path, "/tmp/socka", sizeof(addr.sun_path));
	int fd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if(fd == -1)
	{
		printf("create  socket fail\n");
		return -1;
	}
	bind(fd , (struct sockaddr *)&addr, sizeof(struct sockaddr_un));
	
	struct sockaddr_un addr_con;
	addr_con.sun_family = AF_UNIX;
	strncpy(addr_con.sun_path, "/tmp/sockb", sizeof(addr_con.sun_path));
	int ret = connect(fd, (struct sockaddr *)&addr_con, sizeof(addr_con));
	printf("ret = %d\n", ret);
	char buf[128] = {0};
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
}
