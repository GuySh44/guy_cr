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
	AuthAddUser("guy","guy");
	AuthAddUser("guy","4497");
	AuthAddUser("", "");
	AuthAddUser("", "123");
	AuthAddUser("123", "");
	return 0;
}
