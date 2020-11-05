 #define _BSD_SOURCE
#include <sys/types.h>
       #include <sys/ipc.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
key_t myftok(const char *filename, int filter)
{
	if(!filename || filter == 0)
	{
		printf("invalid param\n");
		return -1;
	}
	key_t key = 0;
	struct stat st;
	if(stat(filename, &st) < 0)
	{
		return -1;
	}
	key += st.st_ino & 0xFFFF;
	key += (minor(st.st_dev) & 0xFF) << 16;
	key += (filter & 0xFF) << 24;
	return key;
}

int main(int argc ,char **argv)
{
	key_t key1 = ftok(argv[1], 1);
	key_t key2 = myftok(argv[1], 1);
	printf("%x, %x\n", key1, key2);
}
