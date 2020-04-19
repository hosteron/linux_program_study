#include <gnu/libc-version.h>
#include <stdio.h>
int main()
{
	printf("gnu-libc-version:%s\n", gnu_get_libc_version());
}
