#include <unistd.h>
#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

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
