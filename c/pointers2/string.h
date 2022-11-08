#ifndef __STRING_H__
#define __STRING_H__
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
-if there is no '\0' among the first n bytes of src, dest will no be null terminated.
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
negative if s2 is smaller lexicographically in the first n bytes. 
*/
int StrNcmp(const char *s1, const char *s2, size_t n);

#endif /* __STRING_H__ */
