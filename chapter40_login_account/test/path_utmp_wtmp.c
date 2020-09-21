#include <stdio.h>
#include <paths.h>
int main()
{
	printf("%s,%s\n", _PATH_UTMP, _PATH_WTMP);
}
