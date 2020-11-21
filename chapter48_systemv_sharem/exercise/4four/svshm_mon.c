#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include "tlpi_hdr.h"
#if 0
truct shmid_ds {
struct ipc_perm shm_perm;    /* Ownership and permissions */
size_t          shm_segsz;   /* Size of segment (bytes) */
time_t          shm_atime;   /* Last attach time */
time_t          shm_dtime;   /* Last detach time */
time_t          shm_ctime;   /* Last change time */
pid_t           shm_cpid;    /* PID of creator */
pid_t           shm_lpid;    /* PID of last shmat(2)/shmdt(2) */
shmatt_t        shm_nattch;  /* No. of current attaches */
...
};
#endif
int main(int argc ,char **argv)
{
	struct shmid_ds buf;
	if(argc !=2 )
		usageErr("%s shmid\n", argv[0]);
	
	int shmid = getInt(argv[1], 0, "shmid");

	if(shmctl(shmid, IPC_STAT, &buf) == -1)
		errExit("shmctl");
	printf("sizeof shm:%ld\n", (long)buf.shm_segsz);
	printf("last attach time:%s\n", ctime(&buf.shm_atime));
	printf("last detach time:%s\n", ctime(&buf.shm_dtime));
	printf("last change time:%s\n", ctime(&buf.shm_ctime));
	printf("pid of creator:%ld\n", (long)buf.shm_cpid);
	printf("pid of last shmat/shmdt:%ld\n", (long)buf.shm_lpid);
	printf("num of current attaches:%ld\n", (long)buf.shm_nattch);
}
