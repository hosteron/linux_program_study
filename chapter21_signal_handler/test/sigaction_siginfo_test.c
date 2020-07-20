#define _POSIX_C_SOUCE 199309
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void printSigInfo(siginfo_t *info)
{
		if(!info) return;
		switch(info->si_code)
	{
			case SI_USER:
			printf("SI_USER        kill(2)\n");
			break;
			case SI_KERNEL:
          printf(" SI_KERNEL      Sent by the kernel.\n");
           break;
			case SI_QUEUE:
           printf("SI_QUEUE       sigqueue(3)\n");
			 break;
			case SI_TIMER:
            printf("SI_TIMER       POSIX timer expired\n");
			break;
			case SI_MESGQ:
           printf("SI_MESGQ       POSIX message queue state changed (since Linux 2.6.6); see mq_notify(3)\n");
			break;
			case SI_ASYNCIO:
           printf("SI_ASYNCIO     AIO completed\n");
			break;
			case SI_SIGIO:
            printf("SI_SIGIO       Queued SIGIO (only in kernels up to Linux 2.2; from Linux 2.4 onward SIGIO/SIGPOLL fills in si_code as described below).\n");
			break;
			case SI_TKILL:
            printf("SI_TKILL       tkill(2) or tgkill(2) (since Linux 2.4.19)\n");
           break;
           #if 1
           case ILL_ILLOPC:
           printf("ILL_ILLOPC     illegal opcode\n");
			break;
			#endif
			case ILL_ILLOPN:
           printf("ILL_ILLOPN     illegal operand\n");
			break;
			case ILL_ILLADR:
           printf("ILL_ILLADR     illegal addressing mode\n");
			break;
			case ILL_ILLTRP:
           printf("ILL_ILLTRP     illegal trap\n");
			break;
			case ILL_PRVOPC:
           printf("ILL_PRVOPC     privileged opcode\n");
			break;
			case ILL_PRVREG:
           printf("ILL_PRVREG     privileged register\n");
			break;
			case ILL_COPROC:
           printf("ILL_COPROC     coprocessor error\n");
			break;
			case ILL_BADSTK:
           printf("ILL_BADSTK     internal stack error\n");
			break;
			#if 0
			case FPE_INTDIV:
			//case 11:
           printf("FPE_INTDIV     integer divide by zero\n");
			break;
			
			case FPE_INTOVF:
           printf("FPE_INTOVF     integer overflow\n");
			break;
			case FPE_FLTDIV:
           printf("FPE_FLTDIV     floating-point divide by zero\n");
			break;
			case FPE_FLTOVF:
           printf("FPE_FLTOVF     floating-point overflow\n");
			break;
			case FPE_FLTUND:
           printf("FPE_FLTUND     floating-point underflow\n");
			break;
			case FPE_FLTRES:
           printf("FPE_FLTRES     floating-point inexact result\n");
			break;
			case FPE_FLTINV:
           printf("FPE_FLTINV     floating-point invalid operation\n");
			break;
			case FPE_FLTSUB:
           printf("FPE_FLTSUB     subscript out of range\n");
           break;
           case SEGV_MAPERR:
		printf("SEGV_MAPERR    address not mapped to object\n");
			break;
			case SEGV_ACCERR:
           printf("SEGV_ACCERR    invalid permissions for mapped object\n");
           break;
           case BUS_ADRALN:
          printf(" BUS_ADRALN     invalid address alignment\n");
           break;
			case BUS_ADRERR:
           printf("BUS_ADRERR     nonexistent physical address\n");
           break;
			case BUS_OBJERR:
           printf("BUS_OBJERR     object-specific hardware error\n");
           break;
			case BUS_MCEERR_AR:
           printf("BUS_MCEERR_AR (since Linux 2.6.32) \
                          Hardware memory error consumed on a machine check; action required.\n");
			break;
			case BUS_MCEERR_AO:
           printf("BUS_MCEERR_AO (since Linux 2.6.32)\
                          Hardware memory error detected in process but not consumed; action optional.\n");
            break;
            case TRAP_BRKPT:
            printf("TRAP_BRKPT     process breakpoint\n");
			break;
			case TRAP_TRACE:
           printf("TRAP_TRACE     process trace trap\n");
           break;
			case TRAP_BRANCH:
           printf("TRAP_BRANCH (since Linux 2.4)\
                          process taken branch trap\n");
            break;
			case TRAP_HWBKPT:
           printf("TRAP_HWBKPT (since Linux 2.4)\
                          hardware breakpoint/watchpoint\n");
            break;
           
           case CLD_EXITED:
		printf("CLD_EXITED     child has exited\n");
			break;
			case CLD_KILLED:
           printf("CLD_KILLED     child was killed\n");
			break;
			case CLD_DUMPED:
           printf("CLD_DUMPED     child terminated abnormally\n");
			break;
			case CLD_TRAPPED:
           printf("CLD_TRAPPED    traced child has trapped\n");
			break;
		case CLD_STOPPED:
           printf("CLD_STOPPED    child has stopped\n");
			break;
			case CLD_CONTINUED:
          printf(" CLD_CONTINUED  stopped child has continued (since Linux 2.6.9)\n");
           break;
           case POLL_IN:
			printf("POLL_IN        data input available\n");
			break;
			case POLL_OUT:
           printf("POLL_OUT       output buffers available\n");
			break;
			case POLL_MSG:
           printf("POLL_MSG       input message available\n");
			break;
			case POLL_ERR:
           printf("POLL_ERR       I/O error\n");
			break;
			case POLL_PRI:
           printf("POLL_PRI       high priority input available\n");
			break;
			case POLL_HUP:
           printf("POLL_HUP       device disconnected\n");
           break;
           #endif
           default :
           printf("siginfo unkown si_code\n");
           break;
	}
}
void handler(int sig ,siginfo_t *info, void *context)
{
	printf("sig = %d, info->si_signo=%d, si_code=%d, si_pid=%d, si_uid=%d\n", sig, info->si_signo, info->si_code, info->si_pid, info->si_uid);
	printSigInfo(info);
	psiginfo(info, "psiginfo std err:");
	if(sig == SIGSEGV)
		_exit(-1);
}
int main()
{
		printf("pid=%d\n", getpid());
		struct sigaction sa;
		sa.sa_sigaction = handler;
		sa.sa_flags = SA_SIGINFO;
		sigemptyset(&sa.sa_mask);
		sigaction(SIGTERM, &sa, NULL);
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGSEGV, &sa, NULL);
		char *p = 11;
		strcpy(p, "hello world\n"); //generate SIGSEGV
		pause();
}
