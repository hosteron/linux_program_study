#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tlpi_hdr.h"
int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("argc != 2 error\n");
		return -1;
	}
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd == -1)
	{
		printf("socket fail\n");
		return -1;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(10001);
	inet_pton(AF_INET, "192.168.0.106", &addr.sin_addr);
	bind(fd, (struct sockaddr *)&addr, (socklen_t)sizeof(addr));

	struct sockaddr_in dst;
	dst.sin_family  = AF_INET;
	dst.sin_port = htons(10000);
	inet_pton(AF_INET, "192.168.0.106", &dst.sin_addr);

	sendto(fd, argv[1], strlen(argv[1]), 0, (const struct sockaddr *)&dst, (socklen_t)sizeof(dst));
	char buf[32] = {0};
	struct sockaddr_in src;
	socklen_t  len ;
	len = sizeof(src);
	int ret = recvfrom(fd, buf, sizeof(buf), 0,(struct sockaddr *)&src,  &len);
	printf("ret = %d, buf = %s\n", ret, buf);
	char ip[32] = {0};
	inet_ntop(AF_INET, &src.sin_addr, ip, sizeof(ip));

	printf("recieve from :%s, %d\n", ip, ntohs(src.sin_port));
}
