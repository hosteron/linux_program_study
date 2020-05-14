#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern char **environ;
int mysetenv(const char *name, const char *value, int overwrite)
{
	if(!name || !value || !strlen(name))
		return -1;
	if(overwrite)
	{
	int len = strlen(name) + strlen(value)+1+1;
	char *p = malloc(len);
	if(p == NULL)
		return -1;
	snprintf(p, len, "%s=%s", name, value);
	if(putenv(p))
	{
				free(p);
				return -1;
	}
	}
	else
	{
			char *getname = getenv(name);
			if(getname)
				return 0;
			int len = strlen(name) + strlen(value)+1+1;
	char *p = malloc(len);
	if(p == NULL)
		return -1;
	snprintf(p, len, "%s=%s", name, value);
	if(putenv(p))
	{
				free(p);
				return -1;
	}
	}
	return 0;
}
int myunsetenv(const char *name)
{
		if(!name || !strlen(name)) return -1;
		char **p = environ;
		for(; p!= NULL && *p != NULL; p++)
		{
				if(!strncmp(name, *p, strlen(name)))
					memset(*p, 0, strlen(*p));
		}
		return 0;
}
int main()
{
	//clearenv();
	char **p = environ;
	int ret = putenv("zhouxiang=123");
	printf("ret = %d, p=%p\n", ret, p);
	char **pr = NULL;
	for(p = environ; p!= NULL && *p != NULL; p++)
	{
		printf("%p, %s\n",*p, *p);
		
		if(pr)
		{
				printf("%x\n", *p - *pr );
		}
		pr = p;
	}
	printf("11111111111111111111111111111111\n");
		mysetenv("hello", "world", 1);
	mysetenv("hello", "world123", 0);
	mysetenv("zhouxiang", "abc", 1);
	for(p = environ; p!= NULL && *p != NULL; p++)
		printf("%s\n", *p);
	myunsetenv("hello");
	for(p = environ; p!= NULL && *p != NULL; p++)
	{
		
		printf("%p, %s\n",*p, *p);
		
	}
	printf("gethello=%s\n",getenv("hello"));
}
