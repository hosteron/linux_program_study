#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
char *ename[200] = {0};
int main()
{
ename[EPERM]="EPERM";
ename[ENOENT]="ENOENT";
ename[ESRCH]="ESRCH";
ename[EINTR]="EINTR";
ename[EIO]="EIO";
ename[ENXIO]="ENXIO";
ename[E2BIG]="E2BIG";
ename[ENOEXEC]="ENOEXEC";
ename[EBADF]="EBADF";
ename[ECHILD]="ECHILD";
ename[EAGAIN]="EAGAIN";
ename[ENOMEM]="ENOMEM";
ename[EACCES]="EACCES";
ename[EFAULT]="EFAULT";
ename[ENOTBLK]="ENOTBLK";
ename[EBUSY]="EBUSY";
ename[EEXIST]="EEXIST";
ename[EXDEV]="EXDEV";
ename[ENODEV]="ENODEV";
ename[ENOTDIR]="ENOTDIR";
ename[EISDIR]="EISDIR";
ename[EINVAL]="EINVAL";
ename[ENFILE]="ENFILE";
ename[EMFILE]="EMFILE";
ename[ENOTTY]="ENOTTY";
ename[ETXTBSY]="ETXTBSY";
ename[EFBIG]="EFBIG";
ename[ENOSPC]="ENOSPC";
ename[ESPIPE]="ESPIPE";
ename[EROFS]="EROFS";
ename[EMLINK]="EMLINK";
ename[EPIPE]="EPIPE";
ename[EDOM]="EDOM";
ename[ERANGE]="ERANGE";
ename[EDEADLK]="EDEADLK";
ename[ENAMETOOLONG]="ENAMETOOLONG";
ename[ENOLCK]="ENOLCK";
ename[ENOSYS]="ENOSYS";
ename[ENOTEMPTY]="ENOTEMPTY";
ename[ELOOP]="ELOOP";
ename[EWOULDBLOCK]="EWOULDBLOCK";
//ename[EAG]="EAG";
ename[ENOMSG]="ENOMSG";
ename[EIDRM]="EIDRM";
ename[ECHRNG]="ECHRNG";
ename[EL2NSYNC]="EL2NSYNC";
ename[EL3HLT]="EL3HLT";
ename[EL3RST]="EL3RST";
ename[ELNRNG]="ELNRNG";
ename[EUNATCH]="EUNATCH";
ename[ENOCSI]="ENOCSI";
ename[EL2HLT]="EL2HLT";
ename[EBADE]="EBADE";
ename[EBADR]="EBADR";
ename[EXFULL]="EXFULL";
ename[ENOANO]="ENOANO";
ename[EBADRQC]="EBADRQC";
ename[EBADSLT]="EBADSLT";
ename[EDEADLOCK]="EDEADLOCK";
//ename[EDEAD]="EDEAD";
ename[EBFONT]="EBFONT";
ename[ENOSTR]="ENOSTR";
ename[ENODATA]="ENODATA";
ename[ETIME]="ETIME";
ename[ENOSR]="ENOSR";
ename[ENONET]="ENONET";
ename[ENOPKG]="ENOPKG";
ename[EREMOTE]="EREMOTE";
ename[ENOLINK]="ENOLINK";
ename[EADV]="EADV";
ename[ESRMNT]="ESRMNT";
ename[ECOMM]="ECOMM";
ename[EPROTO]="EPROTO";
ename[EMULTIHOP]="EMULTIHOP";
ename[EDOTDOT]="EDOTDOT";
ename[EBADMSG]="EBADMSG";
ename[EOVERFLOW]="EOVERFLOW";
ename[ENOTUNIQ]="ENOTUNIQ";
ename[EBADFD]="EBADFD";
ename[EREMCHG]="EREMCHG";
ename[ELIBACC]="ELIBACC";
ename[ELIBBAD]="ELIBBAD";
ename[ELIBSCN]="ELIBSCN";
ename[ELIBMAX]="ELIBMAX";
ename[ELIBEXEC]="ELIBEXEC";
ename[EILSEQ]="EILSEQ";
ename[ERESTART]="ERESTART";
ename[ESTRPIPE]="ESTRPIPE";
ename[EUSERS]="EUSERS";
ename[ENOTSOCK]="ENOTSOCK";
ename[EDESTADDRREQ]="EDESTADDRREQ";
ename[EMSGSIZE]="EMSGSIZE";
ename[EPROTOTYPE]="EPROTOTYPE";
ename[ENOPROTOOPT]="ENOPROTOOPT";
ename[EPROTONOSUPPORT]="EPROTONOSUPPORT";
ename[ESOCKTNOSUPPORT]="ESOCKTNOSUPPORT";
ename[EOPNOTSUPP]="EOPNOTSUPP";
ename[EPFNOSUPPORT]="EPFNOSUPPORT";
ename[EAFNOSUPPORT]="EAFNOSUPPORT";
ename[EADDRINUSE]="EADDRINUSE";
ename[EADDRNOTAVAIL]="EADDRNOTAVAIL";
ename[ENETDOWN]="ENETDOWN";
ename[ENETUNREACH]="ENETUNREACH";
ename[ENETRESET]="ENETRESET";
ename[ECONNABORTED]="ECONNABORTED";
ename[ECONNRESET]="ECONNRESET";
ename[ENOBUFS]="ENOBUFS";
ename[EISCONN]="EISCONN";
ename[ENOTCONN]="ENOTCONN";
ename[ESHUTDOWN]="ESHUTDOWN";
ename[ETOOMANYREFS]="ETOOMANYREFS";
ename[ETIMEDOUT]="ETIMEDOUT";
ename[ECONNREFUSED]="ECONNREFUSED";
ename[EHOSTDOWN]="EHOSTDOWN";
ename[EHOSTUNREACH]="EHOSTUNREACH";
ename[EALREADY]="EALREADY";
ename[EINPROGRESS]="EINPROGRESS";
ename[ESTALE]="ESTALE";
ename[EUCLEAN]="EUCLEAN";
ename[ENOTNAM]="ENOTNAM";
ename[ENAVAIL]="ENAVAIL";
ename[EISNAM]="EISNAM";
ename[EREMOTEIO]="EREMOTEIO";
ename[EDQUOT]="EDQUOT";
ename[ENOMEDIUM]="ENOMEDIUM";
ename[EMEDIUMTYPE]="EMEDIUMTYPE";
ename[ECANCELED]="ECANCELED";
ename[ENOKEY]="ENOKEY";
ename[EKEYEXPIRED]="EKEYEXPIRED";
ename[EKEYREVOKED]="EKEYREVOKED";
ename[EKEYREJECTED]="EKEYREJECTED";
ename[EOWNERDEAD]="EOWNERDEAD";
ename[ENOTRECOVERABLE]="ENOTRECOVERABLE";
ename[ERFKILL]="ERFKILL";
ename[EHWPOISON]="EHWPOISON";
int i ;
int cnt=0;
int max=0;
int num = sizeof(ename)/sizeof(ename[i]);
printf("num=%d\n", num);
for(i =0 ; i < sizeof(ename)/sizeof(ename[i]); i++)
{
		if(ename[i])
		{
				cnt++;
				printf("[%s]:%d\n",ename[i], i);
				if(max < i)
				{
						max = i;
				}
		}
}
printf("cnt=%d, max=%d\n",cnt, max);
int fd = open("ename.c.inc", O_CREAT|O_EXCL|O_WRONLY,0775);
if(fd<=0)
{
		printf("open ename.c.inc failed\n");
		return -1;
}
write(fd, "static char *ename[] = {", strlen("static char *ename[] = {"));
int index = 0;
int max_ename = 0;
for(i = 0; i <= max; i++)
{
		if(index++ % 7 == 0)
			write(fd, "\n", 1);
		if(ename[i])
		{
				max_ename ++;
				write(fd, "\"",1);
				write(fd, ename[i], strlen(ename[i]));
				write(fd, "\"", 1);
				write(fd,",", 1);
		}
		else
		{
				write(fd, "\"",1);
				write(fd, "\"", 1);
				write(fd,",", 1);
		}
}
write(fd, "};", 2);
write(fd, "\n", 1);
char buf[32] = {0};
snprintf(buf, sizeof(buf), "#define MAX_ENAME %d", max_ename);
write(fd , buf, strlen(buf));
write(fd, "\n", 1);
close(fd);
}
