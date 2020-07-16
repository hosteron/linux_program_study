#ifndef SIGNAL_FUNCTIONS_H_
#define SIGNAL_FUNCTIONS_H_
#include <signal.h>
#include <stdio.h>
void printSigSet(FILE *of, const char *prefix, const sigset_t *sigset);
int printSigMask(FILE *of, const char *msg);
int printPendingSigs(FILE *of, const char *msg);
#endif
