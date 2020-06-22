#define _BSD_SOURCE
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
int main(int argc ,char **argv)
{
		struct stat s1;
		int ret = stat(argv[1], &s1);
		printf("ret=%d\n", ret);
		struct stat *sp = &s1;
		printf("st_dev-major=%d\nst_dev-minor=%d\nst_ino=%d\nst_mode=%d\nst_nlink=%d\nst_size=%d\nst_blocks=%d\nst_blksize=%d\n",major(sp->st_dev), minor(sp->st_dev),sp->st_ino,sp->st_mode,sp->st_nlink,sp->st_size,sp->st_blocks,sp->st_blksize);
		ret = lstat(argv[1], &s1);
		printf("\nret=%d\n", ret);
		printf("st_dev=%d\nst_ino=%d\nst_mode=%d\nst_nlink=%d\nst_size=%d\n",sp->st_dev,sp->st_ino,sp->st_mode,sp->st_nlink,sp->st_size);
		int fd= open(argv[1], O_RDONLY);
		ret = fstat(fd, &s1);
		printf("\nret=%d\n",ret);
		printf("st_dev=%d\nst_ino=%d\nst_mode=%d\nst_nlink=%d\nst_size=%d\n",sp->st_dev,sp->st_ino,sp->st_mode,sp->st_nlink,sp->st_size);
		
}
