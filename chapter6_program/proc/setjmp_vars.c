#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
static jmp_buf env;
static void doJump(int nvar, int rvar, int vvar)
{
	printf("inside doJump():nvar=%d rvar=%d vvar=%d\n", nvar, rvar,vvar);
	longjmp(env, 1);
}
int main(int argc, char *argv[])
{
	int nvar = 1;
	register int rvar = 2;
	volatile int vvar =3 ;
	printf("init:nvar=%d rvar=%d vvar=%d\n", nvar, rvar,vvar);
	nvar = 111;
	rvar = 222;
	vvar = 333;
	printf("insert:nvar=%d rvar=%d vvar=%d\n", nvar, rvar,vvar);
	if(setjmp(env) == 0){
		nvar = 777;
		rvar = 888;
		vvar = 999;
		doJump(nvar, rvar, vvar);
	}else{
		printf("after longjmp():nvar=%d rvar=%d vvar=%d\n", nvar, rvar,vvar);
	}

	return 0;
}
