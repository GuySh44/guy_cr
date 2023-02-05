#define _POSIX_SOURCE
#include <stdio.h> /* printf */
#include <signal.h> /* SIGUSR signal */
#include <unistd.h> /* kill fork pause write */
#include <sys/types.h> /* pid_t */


void SigHandlerParent()
{
	signal(SIGUSR1, SigHandlerParent); 
	sleep(1);
	write(1, "Pong\n", 6);
}


void SigHandlerChild()
{
	signal(SIGUSR2, SigHandlerChild);
	write(1, "Ping\n", 6);
	kill(getppid(), SIGUSR1);
}


int main()
{

	pid_t child_pid = {0};
	signal(SIGUSR1, SigHandlerParent); 
	signal(SIGUSR2, SigHandlerChild); 
	
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
			pause();
		}
	}


/* Parent Process */
	else
	{
		while(1)
		{
			sleep(1);
			kill(child_pid,SIGUSR2);
			pause();
		}
	}
	return 0;
}

