#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main( void )
{
    pid_t pid = 0;
    pid_t ppid = 0;
    int iRet = 0;

    pid = fork( );
    if( pid == -1 )
    {
        printf( "fork ERROR\n" );
        exit( -1 );
    }
    if( pid == 0 )
    {
		#if 0
        int ret = waitpid( getppid( ), NULL, 0 );
        printf( "group ID : %d, %d, %d, ret = %d\n", getgid( ), pid, getppid( ) , ret);
        #endif
        execlp("sleep", "sleep", "30", NULL);
    }
    else
    {
		sleep(5);
        ppid = getpid( );
        iRet = setpgid( pid, ppid );
        if( iRet == -1 )
        {
            printf( "setpgid ERROR\n" );
            exit( -1 );
        }
    }

    return 0;
}
