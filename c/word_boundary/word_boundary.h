#ifndef __WORD_BOUNDARY_H__
#define __WORD_BOUNDARY_H__

#include<assert.h>
#include<stddef.h> /* size_t */
#include<stdlib.h> /* malloc */
#include<stdio.h> /* printf */

/*
put c in the first n bytes starting in s 

return:
pointer to start of s	
*/
void *Memset(void *s, int c, size_t n);


/*
copy n bytes from src to dest, the areas must not overlap.

return:
pointer to start of dest
*/
void *Memcpy(void *dest, const void *src, size_t n);
















#endif
