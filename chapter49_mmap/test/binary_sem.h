#ifndef BINARY_SEM_H
#define BINARY_SEM_H

#define SEM_KEY 0x1234
union semun {
               int              val;    /* Value for SETVAL */
               struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
               unsigned short  *array;  /* Array for GETALL, SETALL */
               struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
           };


int initSemInUse(int semId, int which);

int initSemAvailable(int semId, int which);

int reserveSem(int semId, int which);

int releaseSem(int semId, int which);

#define WRITER 1
#define READER 0

#endif
