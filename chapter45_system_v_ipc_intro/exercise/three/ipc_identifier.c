 #define _BSD_SOURCE
#include <sys/types.h>
       #include <sys/ipc.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
int main()
{
	key_t key = ftok("./ipc_identifier.c", 1);
	int id = msgget(key, IPC_CREAT|IPC_EXCL|S_IRUSR|S_IWUSR);
	int index = id % 32768;
	printf("index = %d\n", index);
	key = ftok("./ipc_identifier.c", 2);
	int id2 = msgget(key, IPC_CREAT|IPC_EXCL|S_IRUSR|S_IWUSR);
	index = id2 % 32768;
        printf("index = %d\n", index);
}
