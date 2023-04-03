#include <stdio.h>
#include <stdlib.h> /* system */

#include "vpn_utils.h"

int run(char *cmd)
{
	printf("Execute '%s'\n", cmd);
	if (system(cmd))
	{
		return 1;
	}
	
	return 0;
}
