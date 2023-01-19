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
	printf("%d\n",AuthAddUser("guy","4497"));
	printf("%d\n",AuthAddUser("", ""));
	printf("%d\n",AuthAddUser("", "123"));
	printf("%d\n",AuthAddUser("123", ""));
	printf("%d\n",AuthAddUser(" 345", ""));
	printf("%d\n",AuthAddUser("3:45", ""));
	printf("%d\n",AuthAddUser("345\n", ""));
	printf("%d\n",AuthAddUser("3:4\n5 ", ""));
	printf("%d\n",AuthAddUser("345", ""));
	return 0;
}
