#define _POSIX_SOURCE
#include <signal.h> /* SIGUSR signal */
#include <unistd.h> /* kill pause write getppid getpid */
#include <sys/types.h> /* pid_t */


/* Reviewer: sigprocmask-it */

void SigHandlerChild()
{
	signal(SIGUSR2, SigHandlerChild);
	write(1, "Ping\n", 6);
	kill(getppid(), SIGUSR1);
}

int main()
{
	
	signal(SIGUSR2, SigHandlerChild); 
	
	while(1)
	{
		pause();
	}
		
	return 0;
}
