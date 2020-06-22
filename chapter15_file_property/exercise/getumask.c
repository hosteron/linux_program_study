#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char **argv)
{
		mode_t cur = umask(0);
		mode_t tmp = umask(cur);
		printf("cur=%d, tmp=%d\n", cur, tmp);
}
