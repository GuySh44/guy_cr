#define _POSIX_SOURCE
#include <signal.h> /* SIGUSR signal */
#include <unistd.h> /* kill pause write getppid getpid */
#include <sys/types.h> /* pid_t */
#include <stdio.h> /* printf */

void sig_handler_child()
{
	signal(SIGUSR2, sig_handler_child);
	write(1, "Ping\n", 6);
	kill(getppid(), SIGUSR1);
}

int main()
{
	
	signal(SIGUSR2, sig_handler_child); 
	
	while(1)
	{
		pause();
	}
		
	return 0;
}
