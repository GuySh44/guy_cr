#include <fcntl.h> /*open*/
#include <unistd.h> /*write*/
#include <time.h> /*strftime time localtime time_t*/
#include <string.h> /*memset*/

#define DATESIZE 32
#define LOGTIMEOUT " No action for 7 secs\n"
#define LOGTCPCLOSE " Tcp connection closed\n"

/*
Reviewer: raz
*/



int LogTimeout(void)
{
	int retval = 0;
	int logfd = 0;
	char buff[DATESIZE];
    struct tm *sTm = NULL;
    
    time_t now = time(0);
    
    if(((time_t) -1) == now)
    {
    	return -1;
    }
    
    sTm = localtime(&now);
    if(NULL == sTm)
    {
    	return -1;
    }

	memset(buff, '\0', DATESIZE);
    strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);
    

	logfd = open("./log.txt", O_WRONLY | O_CREAT | O_APPEND | O_NONBLOCK, 0666); 
	
	if(-1 == logfd)
	{
		return logfd;
	}
	
    retval = write(logfd, buff, strlen(buff));
	
	if(-1 == retval)
	{
		close(logfd);
		return retval;
	}
	
	retval = write(logfd, LOGTIMEOUT, strlen(LOGTIMEOUT));
	
	if(-1 == retval)
	{
		close(logfd);
		return retval;
	}
	
	if(-1 == close(logfd))
	{
		return -1;
	}
	
	return retval;
}

int LogTcpClosed(void)
{
	int retval = 0;
	int logfd = 0;
	char buff[DATESIZE];
    struct tm *sTm = NULL;
    
    time_t now = time(0);
    
    if(((time_t) -1) == now)
    {
    	return -1;
    }
    
    sTm = localtime(&now);
    if(NULL == sTm)
    {
    	return -1;
    }

	memset(buff, '\0', DATESIZE);
    strftime (buff, sizeof(buff), "%Y-%m-%d %H:%M:%S ", sTm);
    

	logfd = open("./log.txt", O_WRONLY | O_CREAT | O_APPEND | O_NONBLOCK, 0666); 
	
	if(-1 == logfd)
	{
		return logfd;
	}
	
    retval = write(logfd, buff, strlen(buff));
	
	if(-1 == retval)
	{
		close(logfd);
		return retval;
	}
	
	retval = write(logfd, LOGTCPCLOSE, strlen(LOGTCPCLOSE));
	
	if(-1 == retval)
	{
		close(logfd);
		return retval;
	}
	
	if(-1 == close(logfd))
	{
		return -1;
	}
	
	return retval;
}

