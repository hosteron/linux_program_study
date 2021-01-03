#include <netdb.h>
#include<sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc ,char **argv)
{
	printf("port ; %d\n", atoi(argv[1]));
	//struct servent *ent = getservbyport(atoi(argv[1]), NULL);
	struct servent *ent = getservbyport(80, "tcp");
	if(ent)
	printf("server:%s\n", ent->s_name);
	
}
