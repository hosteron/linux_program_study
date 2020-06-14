#include <stdio.h>
#include <sys/statvfs.h>
int main(int argc, char **argv)
{
		struct statvfs tmp;
		int ret = statvfs(argv[1], &tmp);
		if(ret){
			printf("statvfs %s fail\n", argv[1]);
			return -1;
			}
			struct statvfs *buf = &tmp;
	 printf("%d\n" ,buf->f_bsize);
	  printf("%d\n" ,buf->f_frsize);
	   printf("%d\n" ,buf->f_blocks);
	    printf("%d\n" ,buf->f_bfree);
	     printf("%d\n" ,buf->f_bavail);
	      printf("%d\n" ,buf->f_files);
	       printf("%d\n" ,buf->f_ffree);
	        printf("%d\n" ,buf->f_bsize);
	         printf("%d\n" ,buf->f_favail);
	          printf("%d\n" ,buf->f_fsid);
	           printf("%d\n" ,buf->f_flag);
	           printf("%d\n" ,buf->f_namemax);
}


