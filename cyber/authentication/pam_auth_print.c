#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <stdio.h>


static struct pam_conv conv = {misc_conv,	NULL};

int main()
{
	pam_handle_t *pamh=NULL;
	int retval;
	const char *user="nobody";
	
	
	
	
	return 0;
}
