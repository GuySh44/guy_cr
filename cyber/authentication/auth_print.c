#include <stdio.h>
#include <string.h>

#include "authenticator.h"

#define CREDS_SIZE 32

void SetUsers()
{
	AuthConfigAuthenticator("./test_dir/users_db", NULL);
	AuthAddUser("guy","guy");
	AuthAddUser("kali","kali");
	AuthAddUser("123","456");
}


int main()
{
	char username[CREDS_SIZE];
	char password[CREDS_SIZE];
	SetUsers();
	
	
	while(1)
	{
		printf("enter username / exit to exit \n");
		scanf("%s", username);
		
		if(0 == strcmp(username, "exit"))
		{
			break;
		}
		
		printf("Enter password:\n");
		scanf("%s", password);
		
		
		if(0 == AuthAuthenticator(username,password))
		{
			printf("You're in hackerkman\n");
			break;
		}
	}
	
	return 0;
}
