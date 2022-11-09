#ifndef __STRINGME_H__
#define __STRINGME_H__
#include<stddef.h>

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




#endif /* __STRINGME_H__ */
