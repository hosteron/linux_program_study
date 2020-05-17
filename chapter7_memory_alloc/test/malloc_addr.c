#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
extern char end;
int main()
{
		
		char *p1 = malloc(32);
		void *p = sbrk(0);
		printf("%p -> malloc\n", p1);
		printf("%p -> sbrk\n", p);
		printf("%p -> end\n", &end);
}
