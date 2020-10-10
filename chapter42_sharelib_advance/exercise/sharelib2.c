#include <stdio.h>
void mineprint1()
{
	printf("%s\n", __func__);
	extern  void  mineprint();
	mineprint();
}
