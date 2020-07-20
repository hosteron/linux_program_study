#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
//#include "utils.h"
#define USE_SIG_LONG_JMP
static sigjmp_buf senv;
void handler(int sig)
{
    printf("In the handler.\n");
#ifdef USE_SIG_LONG_JMP
    siglongjmp(senv, 1);
    printf("Never see this.\n");
#endif
}
void m_abort(void)
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGABRT);
    sigprocmask(SIG_UNBLOCK, &set, NULL);
    printf("m_abort: raise first SIGABRT.\n");
    raise(SIGABRT);
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESETHAND;
    sa.sa_handler = SIG_DFL;
    sigaction(SIGABRT, &sa, NULL);
    printf("m_abort: raise second SIGABRT.\n");
    raise(SIGABRT);
}
int main(void)
{
    printf("Now call the abort.\n");
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    sigaction(SIGABRT, &sa, NULL);
#ifdef USE_SIG_LONG_JMP
    if (sigsetjmp(senv, 1) == 0)
        m_abort();
    else
        printf("abort failed.\n");
#else
        m_abort();
        printf("abort failed.\n");
#endif
    return 0;
}
