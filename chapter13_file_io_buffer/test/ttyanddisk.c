#include <stdio.h>
#include <unistd.h>
#include <string.h>
/*
./a.out输出：
if i had more time
I would have written you a shorter letter.
* 因为输出到终端，采用的是行缓冲的方式，printf()遇到\n就刷新了，然后就将数据输出到系统缓冲中，紧接着write输出，所以如上显示，_IOLBF

./a.out > test
cat test输出：
I would have written you a shorter letter.
if i had more time
* 因为输出到磁盘，采用的是全缓冲的方式，printf()虽然有\n但是还是还是要等应用层缓冲区满了才会刷新到系统缓冲，或者程序在退出是fclose()了，会刷新，终止，write的输出
* 内容在前面
*/
int main()
{
	printf("if i had more time\n");
	char *p = "I would have written you a shorter letter.\n";
	write(STDOUT_FILENO,p, strlen(p));
}
