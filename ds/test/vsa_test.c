#include <stdlib.h>

#include "vsa.h"
#include "my_utils.h"

int main()
{	
	vsa_t *vsa1 = VsaInit(malloc(128), 128);
	
	
	
	free(vsa1);
	return 0;
}
