#include <assert.h>
#include <stdio.h> /* fopen fclose fgets fseek */
#include <string.h> /* strchr strlen strndup strcat */
#include <crypt.h> /* crypt */
#include <stdlib.h> /* malloc free */
#include <stddef.h> /* size_t */
#include <errno.h> /* errno */

#include "authenticator.h"

#define CRED_SIZE_WO_NT 31
#define INVALID_CHAR_SIZE 3
#define BUFFER_SIZE 128
#define SALT_STR_SIZE 7
#define ALG_SIZE 3

/* Reviewer: Ravid */

/* default place holder function for password strength */
static int AuthDefaultPasswordStrength(const char *password)
{
	return 0;
	(void)password;
}

/* global variable holding pointer to pwd_strength function */
static pwd_strength pwd_config = AuthDefaultPasswordStrength;

/* global variable holding string to database location */
static char *database_location = "./users_db";


/* check attributes of credentials based on requirements specified */
static int AuthCheckCred(const char *cred)
{
	char invalid_char[INVALID_CHAR_SIZE] = {'\n', ' ', ':'};
	size_t i = 0;
	
	for(; i < INVALID_CHAR_SIZE; ++i)
	{
		if(NULL != strchr(cred, invalid_char[i]))
		{
			return 3;
		}
	}
	
	if(strlen(cred) > CRED_SIZE_WO_NT)
	{
		return 4;
	}
	
	return 0;
}

/* 
search for an existing user, and return its data line from the database through buffer that is provided to it

return value:
	0 - username free
	1 - username already taken
	2 - system error
*/
static int AuthUserTaken(FILE *db_file, char *buffer, const char *username)
{	
	extern char* strndup(const char*, size_t n);
	char *curr_username = NULL;
	size_t i = 0;
	
	if(-1 == fseek(db_file, 0, SEEK_SET))
	{
		return 2;
	}
	
	while(NULL != fgets(buffer, BUFFER_SIZE, db_file))
	{
		i = 0;
		while(':' != buffer[i])
		{
			++i;
		}
		curr_username = strndup(buffer, i);
		if(!strcmp(curr_username, username))
		{
			free(curr_username);
			return 1;
		}
		free(curr_username);
	}
	
	return 0;
}


/*
create random salt containing hex chars and put it in salt_buf
return value:
	0 - success
	2 - system error
 */
static int AuthRandomSalt(char *salt_buf)
{
	FILE *urandom_fd = NULL;
	char reg_salt[SALT_STR_SIZE / 2] = {0};		/* SALT_STR_SIZE / 2 because each byte read from urandom will be translated into 2 nibble hex values */
	size_t i = 0;

    urandom_fd = fopen("/dev/urandom", "r");	/* reading from this file provides random bits */
    
    if(NULL == urandom_fd)
	{	
		return 2;
	}
	
    fread(reg_salt, SALT_STR_SIZE / 2, 1, urandom_fd);
    
	if(0 != fclose(urandom_fd))
	{
		return 2;
	}
	
	/* translate to hex so crypt() can handle the salt. reg_salt is too salty */
	for (; i < SALT_STR_SIZE / 2; ++i) 
	{
        if(sprintf(salt_buf + (i * 2), "%02x", (unsigned char)reg_salt[i]) < 0)
        {
        	return 2;
        }
    }
    salt_buf[SALT_STR_SIZE - 1] = '\0';
	
	return 0;
}

int AuthAddUser(const char *username, const char *password)
{
	FILE *db_file = NULL;
	int status = 0;
	size_t username_len = 0;
	char* buffer = NULL;
	char salt[SALT_STR_SIZE] = {0};
	char *hash = NULL;
	char salt_alg[SALT_STR_SIZE + ALG_SIZE] = {'$', '1', '$', '\0'};
	
	assert(username);
	assert(password);
	
	username_len = strlen(username);
	
	status = AuthCheckCred(username);
	if(status)
	{
		return status;
	}
	
	status = AuthCheckCred(password);
	if(status)
	{
		return status;
	}
	
	status = pwd_config(password);
	
	if(status)
	{
		return status;
	}
	
	buffer = (char*)malloc(BUFFER_SIZE);
	if(NULL == buffer)
	{
		return 2;
	}
	
	
	db_file = fopen(database_location, "ab+");
	if(NULL == db_file)
	{	
		free(buffer);
		return 2;
	}
	
	status = AuthUserTaken(db_file, buffer, username);
	if(0 != status)
	{
		if(0 != fclose(db_file))
		{
			free(buffer);
			return 2;
		}
		free(buffer);
		return status;
	}
	
	if(0 != fclose(db_file))
	{
		free(buffer);
		return 2;
	}
	
	
	status = AuthRandomSalt(salt);
	if(status)
	{
		free(buffer);		
		return status;
	}

    hash = crypt(password, strcat(salt_alg, salt));
	
	if('*' == *hash)
	{
		free(buffer);	
		return 2;
	}
	
	db_file = fopen(database_location, "ab+");
	if(NULL == db_file)
	{	
		free(buffer);
		return 2;
	}
	
	memcpy(buffer, username, username_len + 1);
	strcat(buffer, ":");
	strcat(buffer, hash);
	strcat(buffer, "\n");
	
	if(fputs(buffer, db_file) < 0)
	{
		if(0 != fclose(db_file))
		{
			free(buffer);
		}
		return 2;
	}
	
	if(0 != fclose(db_file))
	{
		free(buffer);
		return 2;
	}
	
	free(buffer);
	return 0;
}

int AuthDeleteUser(const char *username)
{
	FILE *db_file = NULL;
	FILE *tmp_db_file = NULL;
	char *tmp_path = NULL;
	char buffer[BUFFER_SIZE] = {0};
	char line_to_del[BUFFER_SIZE] = {0};
	int status = 0;
	
	assert(username);
	
	/* check if user exists */
	if(NULL == buffer)
	{
		return 2;
	}
	
	db_file = fopen(database_location, "ab+");
	if(NULL == db_file)
	{	
		return 2;
	}
	
	status = AuthUserTaken(db_file, line_to_del, username);	
	if(1 != status)
	{
		if(0 != fclose(db_file))
		{
			return 2;
		}
		if(0 == status)
		{
			return 1;
		}
		return status;
	}
	
	if(0 != fclose(db_file))
	{
		return 2;
	}
	
	/*rename db as tmp*/
	tmp_path = (char*)malloc(strlen(database_location) + 5);
	strcpy(tmp_path, database_location); 
	strcat(tmp_path, "_tmp");
	
	if(-1 == rename(database_location, tmp_path))
	{
		return 2;
	}
	
	tmp_db_file = fopen(tmp_path, "ab+");
	if(NULL == db_file)
	{	
		free(tmp_path);
		return 2;
	}
	/*copy tmp to new file*/
	
	db_file = fopen(database_location, "ab+");
	if(NULL == db_file)
	{	
		fclose(tmp_db_file);
		free(tmp_path);
		return 2;
	}
	
	while(NULL != fgets(buffer, BUFFER_SIZE, tmp_db_file))
	{
		if(!strcmp(buffer, line_to_del))		/* pass over line to delete */
		{
			continue;
		}
		
		if(fputs(buffer, db_file) < 0)
		{
			if(0 != fclose(db_file))
			{
				fclose(tmp_db_file);
				free(tmp_path);
			}
			return 2;
		}
	}
	
	if(0 != fclose(db_file))
	{
		fclose(tmp_db_file);
		free(tmp_path);
		return 2;
	}
		
	/*clean tmp*/
	if (feof(tmp_db_file))
	{
		remove(tmp_path);
	}
	else
	{
		rename(tmp_path, database_location);
		free(tmp_path);
		return 2;
	}
	
	if(0 != fclose(tmp_db_file))
	{
		free(tmp_path);
		return 2;
	}
	
	free(tmp_path);
	return 0;
}

int AuthAuthenticator(const char *username, const char *password)
{
	char *old_hash = NULL;
	char *new_hash = NULL;
	char *buffer = NULL;
	size_t old_hash_len = 0;
	FILE *db_file = NULL;
	int status = 0;
	
	
	assert(username);
	assert(password);
	
	db_file = fopen(database_location, "ab+");
	if(NULL == db_file)
	{	
		free(buffer);
		return 2;
	}
	
	buffer = (char*)malloc(BUFFER_SIZE);
	if(NULL == buffer)
	{
		if(0 != fclose(db_file))
		{
			return 2;
		}
		return 2;
	}
	
	status = AuthUserTaken(db_file, buffer, username);		/* check if user even exists, if it does fill buffer with the corresponding line */
	if(1 != status)
	{
		if(0 != fclose(db_file))
		{
			free(buffer);
			return 2;
		}
		if(0 == status)
		{
			free(buffer);
			return 1;
		}
		free(buffer);
		return status;
	}
	
	if(0 != fclose(db_file))
	{
		free(buffer);
		return 2;
	}
	
	old_hash = strchr(buffer, ':') + 1;			/* parse only the hash out of entire line  */
	old_hash_len = strlen(old_hash);
	old_hash[old_hash_len - 1] = '\0';			/* get rid of \n at end of line */
	new_hash = crypt(password, old_hash);		/* check given password credential against old hash */
	
	if(strcmp(new_hash, old_hash))
	{
		free(buffer);
		return 3; 
	}
	
	free(buffer);
	return 0;
}

/* set global config variables to given values */
int AuthConfigAuthenticator(const char *file_path, pwd_strength pwd_config_func)
{
	if(NULL != file_path)
	{
		database_location = (char*)file_path;
	}
	
	if(NULL != pwd_config_func)
	{
		pwd_config = pwd_config_func;
	}
	
	return 0;
}

