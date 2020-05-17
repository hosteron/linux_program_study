#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <mcheck.h>
#include <string.h>
#include <malloc.h>
int main()
{
		//mtrace();
		char *a = (char *)malloc(3);
		printf("a = %p\n", a);
		char *b = (char *)calloc(1,36);
		printf("b = %p \n", b);
		int i ;
		for(i = 0; i < 5; i++)
			a[i] = 'a' + i;
		#if 0
		//free(a);
		free(b);
		printf("a = %p, %s\n", a, a);
		char *c = realloc(a, 246);
		printf("c = %p, %s\n", c ,c );
		free(c);
		char *d = memalign(4, 36);
		free(d);
		void  *memptr;
		posix_memalign(&memptr,1024*sizeof(void *), 1024);
		free(memptr);
		#endif
		//muntrace();
}
