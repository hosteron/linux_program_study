#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tlpi_hdr.h"
int main()
{
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd < 0)
	{
		errExit("socket");
	}
	printf("PID:%ld\n", (long)getpid());
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(10000);
	inet_pton(AF_INET, "192.168.0.106", &addr.sin_addr);
	bind(fd, (struct sockaddr *)&addr, (socklen_t)sizeof(addr));
	
	while(1)
	{
		struct sockaddr_in addr_c;
		char buf[128] = {0};
		int addr_len = sizeof(addr_c);
		int ret = recvfrom(fd , buf, sizeof(buf), 0, (struct sockaddr *)&addr_c, &addr_len);
		printf("recieve %d bytes, %s\n", ret, buf);
		char ip[32] = {0};
		inet_ntop(AF_INET, &addr_c.sin_addr, ip, sizeof(ip));
		printf("client:%s, port = %d\n", ip, ntohs(addr_c.sin_port));
		memset(buf, 0, sizeof(buf));
		snprintf(buf, sizeof(buf), "%ld recieved", (long)getpid());
		sendto(fd, buf, strlen(buf),0, (const struct sockaddr *)&addr_c, (socklen_t)sizeof(addr_c));
	}
}
