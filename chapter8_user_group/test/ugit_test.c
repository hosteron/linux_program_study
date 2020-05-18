
#include <ctype.h>
#include <stdio.h>
#include "ugid_functions.h"
int main()
{
		printf("%s\n", userNameFromId(0));
		printf("%d\n", userIdFromName("xiangzhou"));
		printf("%s\n", groupNameFromdId(0));
		printf("%d\n", groupIdFromName("xiangzhou"));
}
