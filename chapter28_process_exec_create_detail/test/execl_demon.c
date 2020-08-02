#include <stdio.h>
#include <stdint.h>
int main(int argc, char **argv)
{
		int i;
		printf("args: ");
		for(i = 0; i < argc ; i++)
		{
			printf("%s ", argv[i]);
		}
		printf("\n");
		uint64_t t;
		while(1)
		{
			int ret =  read(3, &t, sizeof(t));
			printf("execl ret = %d, %lu\n", ret, t);
		}
}
