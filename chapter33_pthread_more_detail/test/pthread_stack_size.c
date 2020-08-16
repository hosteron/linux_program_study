#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <limits.h>
int main()
{
		printf("thread stack size =%d\n", sysconf(_SC_THREAD_STACK_MIN));
}
