#ifndef __STRINGME_H__
#define __STRINGME_H__
#include<stddef.h>
#include<stdlib.h>
#include<assert.h>

size_t StrLen(const char* s);


/*
copy string that src points to, including null terminated byte, to the buffer dest points to.
the strings may not overlap! and user has to make sure dest is large enough! !!!BEWARE OF BUFFER OVERRUNS!!!

return value:
pointer to the destination string dest
*/
char *StrCpy(char *dest, const char *src);

/*
similar to strcpy, but at most n byes of src are copied.
-if there is no '\0' among the first n bytes of src, dest will not be null terminated.
-if length of src is less than n, dest will be padded with null terminators so a total of n bytes are written.
return value:
pointer to the destination string dest
*/
char *StrNcpy(char *dest, const char *src, size_t n);

/*
compare two strings
return value:
integer, zero if s1 and s2 are equal.
positive if s1 is bigger lexicographically
negative if s2 is smaller lexicographically
*/
int StrCmp(const char* s1, const char* s2);

/*
similar to strcmp, but the first n bytes are compared.
return value:
integer, zero if s1 and s2 are equal in the first n bytes.
positive if s1 is bigger lexicographically in the first n bytes.
negative if s1 is smaller lexicographically in the first n bytes. 
*/
int StrNcmp(const char *s1, const char *s2, size_t n);

/*
similar to strcmp, but isn't case sensitive.
return value:
integer, zero if s1 and s2 are equal.
positive if s1 is bigger lexicographically.
negative if s1 is smaller lexicographically. 
*/
int StrCasecmp(const char *s1, const char *s2);

/*
The strchr() function returns a pointer to the first occurrence of the character c in the string s.
return value:
a pointer to the matched character or NULL if the character  is  not  found.
The  terminating null byte is considered part of the string, so that if c is specified as '\0', these functions return a pointer to the terminator.
*/
char *StrChr(const char *s, int c);


/*
The  strdup() function returns a pointer to a new string which is a duplicate of the string s.  Memory for the new string is obtained with malloc, and can be freed with free.
return value:
On  success,  the strdup() function returns a pointer to the duplicated string.  It returns NULL if insufficient memory was available
*/
char *StrDup(const char *s);

/*
strcat() function appends the src string to the dest string, overwriting the terminating null byte ('\0') at the end of dest, and  then  adds  a  terminating  null  byte.
strings  may  not  overlap,  and the dest string must have enough space for the result.
return value:
The strcat() and strncat() functions return a pointer to the resulting string dest.
*/
char *StrCat(char *dest, const char *src);

/*
strncat() function appends the src string to the dest string, overwriting the terminating null byte ('\0') at the end of dest, and  then  adds  a  terminating  null  byte.
If  src  contains  n or more bytes, strncat() writes n+1 bytes to dest (n from src plus the terminating null byte).  Therefore, the size of dest must be at least strlen(dest)+n+1.
src does not need to be null-terminated if it contains n or more bytes.
return value:
The strcat() and strncat() functions return a pointer to the resulting string dest.
*/
char *StrNcat(char *dest, const char *src, size_t n);

/*
The  strstr()  function  finds  the  first occurrence of the substring needle in the string haystack.  The terminating null bytes ('\0') are not compared.
return value:
The  strstr()  function  finds  the  first occurrence of the substring needle in the string haystack.  The terminating null bytes ('\0') are not compared.
if needle is empty string the full haystack is returned
*/
char *StrStr(const char *haystack, const char *needle);

/*
The  strspn()  function  calculates the length (in bytes) of the initial segment of s which consists entirely of bytes in accept.
ELIF: 
finds the first occurrence of a character in s that is not contained in the set of characters that is specified by accept.
finds the first occurrence of a character in string1 that is not contained in the set of characters that is specified by accept
'\0' in accept isnt considered in the matching proccess
return value:
the number of bytes in the initial segment of s which consist only of bytes from accept.
*/
size_t StrSpn(const char *s, const char *accept);

#endif /* __STRINGME_H__ */
