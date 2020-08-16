#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
static pthread_once_t  dirname_once = PTHREAD_ONCE_INIT;
static pthread_key_t dirname_key ;
void dirname_destroy(void *buf)
{
		if(buf)
		{
				printf("free dirname buf=%p\n", buf);
				free(buf);
		}
}
void dirname_once_init()
{
		pthread_key_create(&dirname_key, dirname_destroy);
		
}
char *mydirname(const char *name)
{
		if(!name)
			return NULL;
		pthread_once(&dirname_once, dirname_once_init);
		char *buf = pthread_getspecific(dirname_key);
		if(!buf)
		{
				buf = (char *)malloc(128);
				printf("dirname malloc = %p\n", buf);
				pthread_setspecific(dirname_key,buf);
		}
		strncpy(buf , name, 128);
		char *p = strrchr(buf, '/');
		if(!p)
		{
				memset(buf, 0, 128);
				strncpy(buf, "./", 128);
		}
		else
		{
				*p = '\0';
		}
		return buf;
}
static pthread_once_t  basename_once = PTHREAD_ONCE_INIT;
static pthread_key_t basename_key;
void basename_destroy(void *buf)
{
		if(buf)
		{
				printf("free basename buf=%p\n", buf);
				free(buf);
		}	
}
void basename_init()
{
		pthread_key_create(&basename_key, basename_destroy);
}
char *mybasename(const char *name)
{
		if(!name)
			return NULL;
		pthread_once(&basename_once, basename_init);
		char *buf = pthread_getspecific(basename_key);
		if(!buf)
		{
				buf = (char *)malloc(128);
				printf("basename malloc = %p\n", buf);
				pthread_setspecific(basename_key, buf);
		}
		char tmp[128] = {0};
		strncpy(tmp, name, sizeof(tmp));
		char *p = strrchr(tmp, '/');
		if(p)
		{
			if(!strcmp("/", tmp))
			{
				 strncpy(buf, tmp, 128);
				 return buf;
			}
			if(!strlen(p+1))
			{
					*p = '\0';
					p = strrchr(tmp, '/');
					if(p)
					{
						 strncpy(buf, p+1, 128);
						 return buf;
					}
					else
					{
						  strncpy(buf, tmp, 128);
						  return buf;
					}
			}
			 strncpy(buf, p+1, 128);
		}
		else
		{
			strncpy(buf, tmp, 128);
		}
		return buf;
}
void *func(void *arg)
{
		printf("basename of /xiang/zhou = %s\n", mybasename("/xiang/zhou")) ;
		//printf("dirname of /xiang/zhou = %s\n", mydirname("/xiang/zhou")) ;
		int i;
		for(i = 0 ; i < 3; i++)
			sleep(1);
		
}
void *func1(void *arg)
{
		int i;
		printf("basename of /sun/xixi =%s\n", mybasename("/sun/xixi"));
		//printf("dirname of  /sun/xixi = %s\n", mydirname("/sun/xixi")) ;
		for(i = 0 ; i < 3; i++)
			sleep(1);
}
int main()
{
		pthread_t t1;
		pthread_t t2;
		pthread_create(&t1, NULL, func, NULL);
		pthread_create(&t2, NULL, func1, NULL);
		pthread_cancel(t1);
		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
		
	
}
