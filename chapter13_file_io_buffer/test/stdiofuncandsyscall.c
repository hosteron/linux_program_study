#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
int main()
{
		printf("first printf sentence");
		write(STDOUT_FILENO, "second write sentence", strlen("second write sentence"));
}
