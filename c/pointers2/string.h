#ifndef __STRING_H__
#define __STRING_H__
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

#endif /* __STRING_H__ */
