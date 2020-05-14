#include <stdio.h>
#include <unistd.h>
#include <setjmp.h>
jmp_buf env;
void func()
{
		printf("func\n");
		if(setjmp(env) == 0)
		{
				printf("initial return\n");
		}
		else
		{
				printf("longjmp here\n");
		}
}
int main()
{
		
		func();
		longjmp(env, 1);
}
