#include <stdio.h>
#include <unistd.h>
int main()
{
		printf("_POSIX_ASYNCHRONOUS_IO=%ld, sysconf=%ld\n", _POSIX_ASYNCHRONOUS_IO, sysconf(_SC_ASYNCHRONOUS_IO));
		printf("_POSIX_CHOWN_RESTRICTED=%d, pathconf=%ld\n", _POSIX_CHOWN_RESTRICTED, pathconf("~",_PC_CHOWN_RESTRICTED));
		printf("_POSIX_JOB_CONTROL=%d, sysconf=%ld\n", _POSIX_JOB_CONTROL, sysconf(_SC_JOB_CONTROL));
		printf("_POSIX_MESSAGE_PASSING=%ld, sysconf=%ld\n", _POSIX_MESSAGE_PASSING, sysconf(_SC_MESSAGE_PASSING));
		printf("_POSIX_PRIORITY_SCHEDULING=%ld, sysconf=%ld\n", _POSIX_PRIORITY_SCHEDULING, sysconf(_SC_PRIORITY_SCHEDULING));
		printf("_POSIX_REALTIME_SIGNALS=%ld, sysconf=%ld\n", _POSIX_REALTIME_SIGNALS, sysconf(_SC_REALTIME_SIGNALS));
		printf("_POSIX_SAVED_IDS=%d\n", _POSIX_SAVED_IDS);
		printf("_POSIX_SEMAPHORES=%ld, sysconf=%ld\n", _POSIX_SEMAPHORES, sysconf(_SC_SEMAPHORES));
		printf("_POSIX_SHARED_MEMORY_OBJECTS=%ld, sysconf=%ld\n", _POSIX_SHARED_MEMORY_OBJECTS, sysconf(_SC_SHARED_MEMORY_OBJECTS));
		printf("_POSIX_THREADS=%ld, sysconf=%ld\n", _POSIX_THREADS, sysconf(_SC_THREADS));
		printf("_XOPEN_UNIX=%d, sysconf=%ld\n", _XOPEN_UNIX, sysconf(_SC_XOPEN_UNIX));
}
