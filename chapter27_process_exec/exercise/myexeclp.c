#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
extern char  **environ;
int myexeclp(const char *filen, const char *arg, ...)
{
	va_list ap;
	va_start(ap,arg);
	int cnt = 0;
	const char *argu = NULL;
	while(1)
	{
		argu = va_arg(ap, const char *);
		if(!argu)
		{
				break;
		}
		cnt++;	
	}

	va_end(ap);
	char **args = (char **)calloc(1, sizeof(const char *)*cnt+2);
	if(!args)
	{
	
	return -1;	
	}

	va_start(ap, arg);
    args[0] = (char *)arg;
	int i;
	for(i = 0; i < cnt ; i++)
	{
			argu = va_arg(ap, const char *);

			args[i+1]= (char *)argu;
	}

	va_end(ap);
	cnt = 0;
	char **ep = NULL;
	for(ep = environ; *ep != NULL; ep++)
	{
		cnt++;
	}

	char **env = (char **)calloc(1, sizeof(char *)*cnt+1);
	if(!env)
	{
			free(args);
			args = NULL;
			return -1;
	}

	i = 0;
	 for(ep = environ; *ep != NULL; ep++)
	{
	
		  env[i++] =  *ep;
	}

	char *p = getenv("PATH");
	if(!p)
	{
			execve(filen, args,env);
			_exit(127);
	}

	char *str = (char *)calloc(1, strlen(p)+1);
	char *pstr = str;
	strcpy(str, p);
	char *pd = strchr(str,':');
	char buf[256] = {0};
	while(pd)
	{
			*pd = '\0';
			memset(buf, 0, sizeof(buf));
			snprintf(buf,sizeof(buf), "%s/%s", str, filen);
			//printf("%s\n", buf);
			if(access(buf, F_OK) == 0)
			{
				execve(buf, args, env);
			}
			str = pd+1;
			pd = strchr(str, ':');
	}
	if(str && str!='\0')
	{
		memset(buf, 0, sizeof(buf));
		snprintf(buf,sizeof(buf), "%s/%s", str, filen);	
		if(access(buf, F_OK) != 0);
		{
				execve(filen, args, env);
				free(args);
				free(env);
				free(pstr);
				printf("%d\n", __LINE__);
				return -1;
			}
		   execve(buf, args, env);
	}
	printf("%d\n", __LINE__);
	return -1;
}
int main()
{
	myexeclp("exec_t.sh", "exec_t.sh", (const char *)NULL);	
	 //execlp("exec_t.sh", "exec_t.sh", (const char *)NULL);
	//char *argv[] = {"exec_t.sh", NULL};
    //char *enp[] = {"hello=world", NULL};
	//execve("exec_t.sh", argv, enp) ;
	printf("%s\n", strerror(errno));
}
