#include <security/pam_appl.h>
#include <security/pam_misc.h>
#include <stdio.h>


static struct pam_conv conv = {misc_conv,	NULL};

int main()
{
	pam_handle_t *pamh=NULL;
	int retval;
	char user[32] = {0};
	
	while(1)
	{
		printf("enter username / exit to exit \n");
		scanf("%s", user);
		
		if(0 == strcmp(user, "exit"))
		{
			break;
		}
		
		retval = pam_start("pam_cyber_print", user, &conv, &pamh);
		
		if (retval == PAM_SUCCESS)
		{
			retval = pam_authenticate(pamh, 0); /* is user really user? */
		}
		
		if (retval == PAM_SUCCESS)
		{
			retval = pam_acct_mgmt(pamh, 0); /* permitted access? */
		}
		
		/* This is where we have been authorized or not. */
		if (retval == PAM_SUCCESS) 
		{
			printf("Authenticated\n");
		}
		else 
		{
			printf("Not Authenticated\n");
		}
		
		if (pam_end(pamh,retval) != PAM_SUCCESS) 
		{ 											/* close Linux-PAM */
			pamh = NULL;
			printf("check_user: failed to release authenticator\n");
			return 1;
		}
	}
	
	return (retval == PAM_SUCCESS ? 0:1); /* indicate success */
}
