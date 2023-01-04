#include <stdlib.h>
#include <stdio.h>

#include "vsa.h"

int main()
{	
	vsa_t *vsa1 = VsaInit(malloc(184), 184);
	
	printf("vsa1 largest chunk:\t%lu\n", VsaLargestChunk(vsa1));
	
	free(vsa1);
	return 0;
}

/*
display mem_ahead
display *curr_aloc_ahead
display *curr_free_ahead
display *next_aloc_ahead
display *next_free_ahead
*/
