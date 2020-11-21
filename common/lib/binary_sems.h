#ifndef BINARY_SHEMS_H
#define BINARY_SHEMS_H
#include "tlpi_hdr.h"
extern  Boolean bsUseSemUndo;
extern Boolean bsRetryOnEintr;
int initSemAvailable(int semId, int semNum);
int initSemInuse(int semId, int semNum);
int reserveSem(int semId, int semNum);
int releaseSem(int semId, int semNum);
#endif
