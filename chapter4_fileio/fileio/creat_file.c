#include <fcntl.h>
#include "tlpi_hdr.h"
#define _GNU_SOURCE
int main(int argc, char *argv[])
{
		int fd = 0;
		//fd  = open(argv[1], O_RDWR|O_CREAT, 0755); // 验证打开一个已存在的文件
		//fd  = open(argv[1], O_RDWR|O_CREAT|O_EXCL, 0755);
		//fd  = open(argv[1], O_RDONLY|O_DIRECTORY);
		//fd = open(argv[1], O_RDONLY|O_CREAT|O_EXCL, 0755); //验证O_CREAT|O_EXCL打开符号链接时的表现
		//fd = open(argv[1], O_RDONLY|O_CREAT, 0755);
		// fd = open(argv[1], O_RDONLY | O_NOATIME); 
		//fd = open(argv[1], O_RDONLY | O_NOFOLLOW);  //验证不O_NOFOLLOW不能打开符号链接
		fd = open(argv[1], O_WRONLY, 0755); // 验证ETXTBSY
		if(fd == -1)
			errExit("open");
		close(fd);
}
