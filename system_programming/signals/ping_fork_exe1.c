#define _POSIX_SOURCE
#include <stdio.h> /* printf */
#include <signal.h> /* SIGUSR signal */
#include <unistd.h> /* kill fork pause write */
#include <sys/types.h> /* pid_t */


void SigHandlerParent()
{
	signal(SIGUSR2, SigHandlerParent);	/* signal will reset so we set again */ 
	sleep(1);
	write(1, "Pong\n", 6);
}


void SigHandlerChild()
{
	signal(SIGUSR1, SigHandlerChild);	/* signal will reset so we set again */
	write(1, "Ping\n", 6);
	kill(getppid(), SIGUSR2);
}


int main()
{

	pid_t child_pid = {0};
	signal(SIGUSR2, SigHandlerParent);	/* intial handler set */ 
	signal(SIGUSR1, SigHandlerChild); 
	
	if((child_pid = fork()) < 0)
	{
		printf("Fork Failed\n");
		return 1;
	}
	
	
/* Child Process */
	else if(0 == child_pid)
	{
		while(1)
		{
			pause();	/* wait for signal */
		}
	}


/* Parent Process */
	else
	{
		while(1)
		{
			sleep(1);
			kill(child_pid,SIGUSR1);
			pause();	/* wait for signal */
		}
	}
	return 0;
}

