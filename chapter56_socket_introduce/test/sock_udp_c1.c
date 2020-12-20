#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tlpi_hdr.h"
int main(int argc, char **argv)
{
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd == -1)
	{
		printf("socket fail\n");
		return -1;
	}


	struct sockaddr_in dst;
	dst.sin_family  = AF_INET;
	dst.sin_port = htons(10001);
	inet_pton(AF_INET, "192.168.0.106", &dst.sin_addr);

	sendto(fd, argv[1], strlen(argv[1]), 0, (const struct sockaddr *)&dst, (socklen_t)sizeof(dst));

}
