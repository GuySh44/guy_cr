#define _POSIX_SOURCE
#include <stdio.h> /* printf */
#include <unistd.h> /* kill */
#include <sys/signalfd.h> /* signalfd */
#include <sys/types.h> /* pid_t */
#include <signal.h> 


int main() 
{
	sigset_t mask = {0};
	int sfd = 0;
	printf("%d\n", getpid());
	
	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);
	
	
    if (sigprocmask(SIG_BLOCK, &mask, NULL) < 0) 
    {
        printf("Failed to signalmask\n");
        return -1;
    }
    
    
	sfd = signalfd(-1, &mask, 0);
	if (sfd == -1)
	{
		printf("signalfd");
	}
	
	while(1) 
	{
		struct signalfd_siginfo fdsi;
		if(read(sfd, &fdsi, sizeof(fdsi)) != sizeof(fdsi))
		{
			return 1;
		}
               
       if(SIGUSR1 == fdsi.ssi_signo) 
       {
      	   sleep(1);
           printf("Ping\n");
           kill(fdsi.ssi_pid, SIGUSR2);
       }
   }

	return 0;
}
