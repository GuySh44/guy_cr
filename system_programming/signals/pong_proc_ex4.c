#define _POSIX_SOURCE
#include <stdio.h> /* printf */
#include <unistd.h> /* kill */
#include <sys/types.h> /* pid_t */
#include <signal.h> /* signal */

/* Reviewer: sigprocmask-it */

pid_t ping_pid;

void SigPong()
{
	signal(SIGUSR2, sigpong);
	write(1, "Pong\n", 6);
	kill(ping_pid, SIGUSR1);
}


int main(int argc, char *argv[]) 
{
	ping_pid = atoi(argv[1]);
	
	signal(SIGUSR2, SigPong);
	
	
	while(1)
	{
		sleep(1);
		kill(ping_pid, SIGUSR1);
		pause();
	}

	return 0;
	
	(void)argc;
}