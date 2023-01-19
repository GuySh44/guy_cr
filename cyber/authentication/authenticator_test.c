#include <stdio.h>
#include <string.h>

#include "authenticator.h"

int NoGuyAllowed(const char *password)
{
	if(!strcmp("guy",password))
	{
		return 5;
	}
	return 0;
}


int main()
{
	AuthConfigAuthenticator("./test_dir/users_db", NoGuyAllowed);
	printf("%d\n",AuthAddUser("guy","guy"));
	printf("%d\n",AuthAddUser("guy","passcode"));
	printf("%d\n",AuthAddUser("", ""));
	printf("%d\n",AuthAddUser("", "123"));
	printf("%d\n",AuthAddUser("123", ""));
	printf("%d\n",AuthAddUser(" 345", ""));
	printf("%d\n",AuthAddUser("3:45", ""));
	printf("%d\n",AuthAddUser("345\n", ""));
	printf("%d\n",AuthAddUser("3:4\n5 ", ""));
	printf("%d\n",AuthAddUser("345", ""));
	
	printf("%d\n",AuthAuthenticator("guy","passcode"));
	printf("%d\n",AuthAuthenticator("guy","passcode2"));
	
	printf("%d\n",AuthDeleteUser("guy"));
	printf("%d\n",AuthDeleteUser("123"));
	printf("%d\n",AuthAuthenticator("guy","passcode"));
	return 0;
}
