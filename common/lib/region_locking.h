#ifndef _REGION_LOCKING_H_
#define _REGION_LOCKING_H_
int lockRegion(int fd , int type, int whence, int start, int len);
int lockRegionWait(int fd , int type, int whence, int start, int len);
pid_t regionIsLocked(int fd, int type, int whence, int start, int len);
#endif
