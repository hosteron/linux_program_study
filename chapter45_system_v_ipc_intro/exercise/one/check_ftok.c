 #define _BSD_SOURCE
#include <sys/types.h>
       #include <sys/ipc.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc ,char **argv)
{
	if(argc != 2)
	{
		printf("%s <filename>\n", argv[0]);
		return -1;
	}
	printf("input filename:%s\n", argv[1]);
	key_t key =  ftok(argv[1], 1);
	printf("key = %x\n", key);
	struct stat st;
	stat(argv[1], &st);
	printf("%x-%x-%x\n", 1, minor(st.st_dev),st.st_ino&0xFFFF);
}
