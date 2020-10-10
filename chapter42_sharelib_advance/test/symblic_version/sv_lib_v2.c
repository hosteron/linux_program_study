#include <stdio.h>
__asm__(".symver xyz_old,xyz@VER_1");
__asm__(".symver xyz_new,xyz@@VER_2"); // 两个@@是为了指示当程序与这个共享库进行静态链接时应该使用的默认定义
void xyz_old()
{
	printf("v1 xyz\n");
}
void xyz_new()
{
	printf("v2 xyz\n");
}
void pqr()
{
	printf("v2 pqr\n");
}
