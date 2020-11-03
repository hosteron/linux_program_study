#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
int main(int argc ,char **argv)
{
	if(argc < 3)
		{
				printf("you should  %s <command> <r|w> [text for write]\n", argv[0]);
				return -1;
		}
		if(*argv[2] == 'w' && argc != 4)
		{
				printf("you should  %s <command> <r|w> [text for write]\n", argv[0]);
				return -1;	
		}

	char buf[128] = {0};
	FILE *pf = popen(argv[1], argv[2]);
	if(*argv[2] == 'r')
	{
		while(1)
		{
				//int ret  = fread(buf, sizeof(buf), 1, pf);
				//if(ret <= 0)
					//break;
				//int ret = read(fileno(pf), buf, sizeof(buf));
				//if(ret <= 0)
					//break;
				char *ret = fgets(buf, sizeof(buf), pf);
				if(!ret)
				break;
				printf("%s", buf);
				memset(buf, 0, sizeof(buf));
		}
	}
	else
	{
		int len = strlen(argv[3]);
				fwrite(argv[3], len, 1, pf);
				fflush(pf);
	}
	pclose(pf);
}
