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
	printf("should get 5 %d\n",AuthAddUser("guy","guy"));
	printf("should get 0 %d\n",AuthAddUser("guy","passcode"));
	printf("should get 0 %d\n",AuthAddUser("", ""));
	printf("should get 1 %d\n",AuthAddUser("", "123"));
	printf("should get 0 %d\n",AuthAddUser("123", ""));
	printf("should get 3 %d\n",AuthAddUser(" 345", ""));
	printf("should get 3 %d\n",AuthAddUser("3:45", ""));
	printf("should get 3 %d\n",AuthAddUser("345\n", ""));
	printf("should get 3 %d\n",AuthAddUser("3:4\n5 ", ""));
	printf("should get 0 %d\n",AuthAddUser("345", ""));
	printf("should get 4 %d\n",AuthAddUser("111111111111111111111111111111111111", ""));
	printf("should get 4 %d\n",AuthAddUser("", "111111111111111111111111111111111111"));
	
	printf("should get 0 %d\n",AuthAuthenticator("guy","passcode"));
	printf("should get 3 %d\n",AuthAuthenticator("guy","passcode2"));
	
	printf("should get 0 %d\n",AuthDeleteUser("guy"));
	printf("should get 0 %d\n",AuthDeleteUser("123"));
	printf("should get 1 %d\n",AuthDeleteUser("123"));
	
	printf("should get 1 %d\n",AuthAuthenticator("guy","passcode"));
	return 0;
}
