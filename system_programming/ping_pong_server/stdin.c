#include <unistd.h> /*read write*/
#include <stddef.h> /*size_t*/
#include <assert.h> /**/
#include <string.h> /*strcmp*/

/*
Reviewer: raz
*/



int StdinRecieve(void *buf, size_t buf_size)
{
	assert(buf);
	
	return read(STDIN_FILENO, buf, buf_size);
}

int StdResponse(char *msg)
{
	if(0 == strcmp(msg, "quit"))
	{
		return 1;
	}
	
	if(0 == strcmp(msg, "ping"))
	{
		return 2;
	}
	
	return 0;
}
