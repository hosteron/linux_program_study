#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
int main(int argc, char **argv)
{
	#if 0
		if(argc != 2)
		{
				printf("you should %s <inputstring>\n",argv[0]);
				return -1;
		}
	#endif
		int fd1[2] = {0};
		int fd2[2] = {0};
		if(pipe(fd1) == -1)
		{
				printf("pipe fail, %s\n", strerror(errno));
				return -1;
		}
		if(pipe(fd2) == -1)
		{
				close(fd1[1]);
				close(fd1[2]);
				printf("pipe fail, %s\n", strerror(errno));
				return -1;
		}
		int num = 0;
		char buf[512] = {0};
		int ret = 0;
		switch(fork())
		{
				case -1:
				printf("fork fail, %s\n", strerror(errno));
				exit(-1);
				break;
				case 0://child
					close(fd1[1]);
					close(fd2[0]);
					while((num = read(fd1[0], buf, sizeof(buf)))> 0)
					{
						int i;
						//printf("num=%d\n", num);
						for(i = 0; i< num; i++)
						{
								//printf("%c\n", buf[i]);
								if(buf[i] <='z' && buf[i] >= 'a')
								{
									//printf("%c\n", buf[i]);
									buf[i]+='A'-'a';
								}
						}
						ret = 0;
						int total = 0;
						while(1)
						{
								ret = write(fd2[1], &buf[total], num- total);
								if(ret== -1 && errno != EINTR)
								{
										printf("write error, %s\n", strerror(errno));
										_exit(-1);
								}
								else
								{
										total += ret;
										if(total == num)
										{
												memset(buf, 0, num);
												break;
												
										}
								}
						}
					}
					printf("child read fail\n");
					close(fd1[0]);
					close(fd2[1]);
					exit(-1);
				break;
				default://parent
				{
					close(fd1[0]);
					close(fd2[1]);
					while(1)
					{
						ret = scanf("%s", buf);
						if(ret == -1)
						{
								printf("scanf fail, %s\n", strerror(errno));
								exit(-1);
						}
						//printf("ret = %d\n", ret);
						ret = strlen(buf);
						int total = 0;
						while(1)
						{
								num = write(fd1[1], &buf[total], ret-total);
								if(num == -1 && errno != EINTR)
								{
										printf("parent write fail %s\n", strerror(errno));
										exit(-1);
								}
								else
								{
										total += num;
										if(total == ret)
										{
												memset(buf, 0, ret);
												break;
										}
								}
								
						}
						total = 0;
						while((num = read(fd2[0], buf, sizeof(buf)))>0)
						{
								//printf("parent read =%d\n", num);
								total += num;
								printf("%s", buf);
								if(total == ret)
								{
										printf("\n");
										break;
								}
						}
					}
				}
				break;
		}
}
