#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "fsa.h"
#include "my_utils.h"


int main()
{
	size_t fsa_size = FsaSuggestedSize(2, 8);
	void *fsa_space = malloc(fsa_size);
	fsa_t *fsa = FsaInit(fsa_space, 2, 8);
	free(fsa);
	return 0;
}
