#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "fsa.h"
#include "my_utils.h"


int main()
{
	size_t fsa1_size = FsaSuggestedSize(5, 8);
	size_t fsa3_size = FsaSuggestedSize(5, 9);
	void *fsa1_space = malloc(fsa1_size);
	void *fsa3_space = malloc(fsa3_size);
	void *fsa1_alloc1 = NULL, *fsa1_alloc2 = NULL, *fsa1_alloc3 = NULL, *fsa1_alloc4 = NULL, *fsa1_alloc5 = NULL, *fsa1_alloc6 = (void*)0x1;
	void *fsa3_alloc1 = NULL, *fsa3_alloc2 = NULL, *fsa3_alloc3 = NULL, *fsa3_alloc4 = NULL, *fsa3_alloc5 = NULL, *fsa3_alloc6 = NULL, *fsa3_alloc7 = NULL, *fsa3_alloc8 = NULL, *fsa3_alloc9 = NULL, *fsa3_alloc10 = (void*)0x1;
	short word_size = sizeof(size_t);
	fsa_t *fsa1 = FsaInit(fsa1_space, 5, fsa1_size);
	fsa_t *fsa3 = FsaInit(((char*)fsa3_space + 2), 5, fsa3_size - 2);
	
	printf("START TESTING PRE-ALIGNED WORD SIZED BLOCKS:\n\n\n");
	printTest("check size > num blocks * (block size)", !(fsa1_size > 5 * 8));
	printTest("check fsa1 size, should be 5", !(FsaCountFree(fsa1) == 5));
	fsa1_alloc1 = FsaAlloc(fsa1);
	printTest("check fsa1 size, should be 4 after 1 alloc", !(FsaCountFree(fsa1) == 4));
	fsa1_alloc2 = FsaAlloc(fsa1);
	printTest("check fsa1 size, should be 3 after 2 alloc", !(FsaCountFree(fsa1) == 3));
	fsa1_alloc3 = FsaAlloc(fsa1);
	printTest("check fsa1 size, should be 2 after 3 alloc", !(FsaCountFree(fsa1) == 2));
	fsa1_alloc4 = FsaAlloc(fsa1);
	printTest("check fsa1 size, should be 1 after 4 alloc", !(FsaCountFree(fsa1) == 1));
	fsa1_alloc5 = FsaAlloc(fsa1);
	printTest("check fsa1 size, should be 0 after 5 alloc", !(FsaCountFree(fsa1) == 0));
	fsa1_alloc6 = FsaAlloc(fsa1); /* all blocks allocated */
	printTest("check try alloc when full *might not be needed*", !(fsa1_alloc6 == NULL));
	
	printf("\ncheck alignment of allocs:\n\n");
	printTest("alloc1 aligned?", ((size_t)fsa1_alloc1) % word_size);
	printTest("alloc2 aligned?", ((size_t)fsa1_alloc2) % word_size);
	printTest("alloc3 aligned?", ((size_t)fsa1_alloc3) % word_size);
	printTest("alloc4 aligned?", ((size_t)fsa1_alloc4) % word_size);
	printTest("alloc5 aligned?", ((size_t)fsa1_alloc5) % word_size); 
	
	printf("\ncheck free function, random order:\n\n");
	FsaFree(fsa1, fsa1_alloc3); 
	printTest("check fsa1 size, should be 1 after 1 free", !(FsaCountFree(fsa1) == 1));
	FsaFree(fsa1, fsa1_alloc4); 
	printTest("check fsa1 size, should be 2 after 2 free", !(FsaCountFree(fsa1) == 2));
	FsaFree(fsa1, fsa1_alloc1); 
	printTest("check fsa1 size, should be 3 after 3 free", !(FsaCountFree(fsa1) == 3));
	FsaFree(fsa1, fsa1_alloc2); 
	printTest("check fsa1 size, should be 4 after 4 free", !(FsaCountFree(fsa1) == 4));
	FsaFree(fsa1, fsa1_alloc5); 
	printTest("check fsa1 size, should be 5 after 5 free", !(FsaCountFree(fsa1) == 5));
	
	printf("\nrealloc again to see free went well\n\n");
	fsa1_alloc1 = FsaAlloc(fsa1);
	printTest("check fsa1 size, should be 4 after 1 alloc", !(FsaCountFree(fsa1) == 4));
	fsa1_alloc2 = FsaAlloc(fsa1);
	printTest("check fsa1 size, should be 3 after 2 alloc", !(FsaCountFree(fsa1) == 3));
	fsa1_alloc3 = FsaAlloc(fsa1);
	printTest("check fsa1 size, should be 2 after 3 alloc", !(FsaCountFree(fsa1) == 2));
	fsa1_alloc4 = FsaAlloc(fsa1);
	printTest("check fsa1 size, should be 1 after 4 alloc", !(FsaCountFree(fsa1) == 1));
	fsa1_alloc5 = FsaAlloc(fsa1);
	printTest("check fsa1 size, should be 0 after 5 alloc", !(FsaCountFree(fsa1) == 0));
	fsa1_alloc6 = FsaAlloc(fsa1); /* all blocks allocated */
	printTest("check try alloc when full *might not be needed*", !(fsa1_alloc6 == NULL));
	
	printf("\ncheck alignment of allocs again:\n\n");
	printTest("alloc1 aligned?", ((size_t)fsa1_alloc1) % word_size);
	printTest("alloc2 aligned?", ((size_t)fsa1_alloc2) % word_size);
	printTest("alloc3 aligned?", ((size_t)fsa1_alloc3) % word_size);
	printTest("alloc4 aligned?", ((size_t)fsa1_alloc4) % word_size);
	printTest("alloc5 aligned?", ((size_t)fsa1_alloc5) % word_size); 
	free(fsa1);
	
	
	
	
	
	printTest("check size > num blocks * (block size)", !(fsa3_size > 5 * 9));
	printf("\n\n\n\nSTART TESTING NON-ALIGNED NON-WORD SIZED BLOCKS:\n\n\n");
	printTest("check fsa3 size, should be 9", !(FsaCountFree(fsa3) == 9));
	fsa3_alloc1 = FsaAlloc(fsa3);
	printTest("check fsa3 size, should be 8 after 1 alloc", !(FsaCountFree(fsa3) == 8));
	fsa3_alloc2 = FsaAlloc(fsa3);
	printTest("check fsa3 size, should be 7 after 2 alloc", !(FsaCountFree(fsa3) == 7));
	fsa3_alloc3 = FsaAlloc(fsa3);
	printTest("check fsa3 size, should be 6 after 3 alloc", !(FsaCountFree(fsa3) == 6));
	fsa3_alloc4 = FsaAlloc(fsa3);
	printTest("check fsa3 size, should be 5 after 4 alloc", !(FsaCountFree(fsa3) == 5));
	fsa3_alloc5 = FsaAlloc(fsa3);
	printTest("check fsa3 size, should be 4 after 5 alloc", !(FsaCountFree(fsa3) == 4));
	fsa3_alloc6 = FsaAlloc(fsa3); 
	printTest("check fsa3 size, should be 3 after 6 alloc", !(FsaCountFree(fsa3) == 3));
	fsa3_alloc7 = FsaAlloc(fsa3); 
	printTest("check fsa3 size, should be 2 after 7 alloc", !(FsaCountFree(fsa3) == 2));
	fsa3_alloc8 = FsaAlloc(fsa3); 
	printTest("check fsa3 size, should be 1 after 8 alloc", !(FsaCountFree(fsa3) == 1));
	fsa3_alloc9 = FsaAlloc(fsa3); 
	printTest("check fsa3 size, should be 0 after 9 alloc", !(FsaCountFree(fsa3) == 0));
	fsa3_alloc10 = FsaAlloc(fsa3); /* all blocks allocated */
	printTest("check try alloc when full *might not be needed*", !(fsa3_alloc10 == NULL));
	
	
	
	printf("\ncheck alignment of allocs when first malloc was not aligned and block size isnt word:\n\n");
	printTest("alloc1 aligned?", ((size_t)fsa3_alloc1) % word_size);
	printTest("alloc2 aligned?", ((size_t)fsa3_alloc2) % word_size);
	printTest("alloc3 aligned?", ((size_t)fsa3_alloc3) % word_size);
	printTest("alloc4 aligned?", ((size_t)fsa3_alloc4) % word_size);
	printTest("alloc5 aligned?", ((size_t)fsa3_alloc5) % word_size);
	printTest("alloc6 aligned?", ((size_t)fsa3_alloc6) % word_size);
	printTest("alloc7 aligned?", ((size_t)fsa3_alloc7) % word_size);
	printTest("alloc8 aligned?", ((size_t)fsa3_alloc8) % word_size);
	printTest("alloc9 aligned?", ((size_t)fsa3_alloc9) % word_size);
	
	
	printf("\ncheck free function, random order:\n\n");
	FsaFree(fsa3, fsa3_alloc3); 
	printTest("check fsa1 size, should be 1 after 1 free", !(FsaCountFree(fsa3) == 1));
	FsaFree(fsa3, fsa3_alloc4); 
	printTest("check fsa1 size, should be 2 after 2 free", !(FsaCountFree(fsa3) == 2));
	FsaFree(fsa3, fsa3_alloc1); 
	printTest("check fsa1 size, should be 3 after 3 free", !(FsaCountFree(fsa3) == 3));
	FsaFree(fsa3, fsa3_alloc2); 
	printTest("check fsa1 size, should be 4 after 4 free", !(FsaCountFree(fsa3) == 4));
	FsaFree(fsa3, fsa3_alloc5); 
	printTest("check fsa1 size, should be 5 after 5 free", !(FsaCountFree(fsa3) == 5));
	FsaFree(fsa3, fsa3_alloc9);
	printTest("check fsa1 size, should be 6 after 6 free", !(FsaCountFree(fsa3) == 6));
	FsaFree(fsa3, fsa3_alloc8); 
	printTest("check fsa1 size, should be 7 after 7 free", !(FsaCountFree(fsa3) == 7));
	FsaFree(fsa3, fsa3_alloc6); 
	printTest("check fsa1 size, should be 8 after 8 free", !(FsaCountFree(fsa3) == 8));
	FsaFree(fsa3, fsa3_alloc7); 
	printTest("check fsa1 size, should be 9 after 9 free", !(FsaCountFree(fsa3) == 9));
	
	
	printf("\nrealloc again to see free reset well\n\n");
	printTest("check fsa3 size, should be 9", !(FsaCountFree(fsa3) == 9));
	fsa3_alloc1 = FsaAlloc(fsa3);
	printTest("check fsa3 size, should be 8 after 1 alloc", !(FsaCountFree(fsa3) == 8));
	fsa3_alloc2 = FsaAlloc(fsa3);
	printTest("check fsa3 size, should be 7 after 2 alloc", !(FsaCountFree(fsa3) == 7));
	fsa3_alloc3 = FsaAlloc(fsa3);
	printTest("check fsa3 size, should be 6 after 3 alloc", !(FsaCountFree(fsa3) == 6));
	fsa3_alloc4 = FsaAlloc(fsa3);
	printTest("check fsa3 size, should be 5 after 4 alloc", !(FsaCountFree(fsa3) == 5));
	fsa3_alloc5 = FsaAlloc(fsa3);
	printTest("check fsa3 size, should be 4 after 5 alloc", !(FsaCountFree(fsa3) == 4));
	fsa3_alloc6 = FsaAlloc(fsa3); 
	printTest("check fsa3 size, should be 3 after 6 alloc", !(FsaCountFree(fsa3) == 3));
	fsa3_alloc7 = FsaAlloc(fsa3); 
	printTest("check fsa3 size, should be 2 after 7 alloc", !(FsaCountFree(fsa3) == 2));
	fsa3_alloc8 = FsaAlloc(fsa3); 
	printTest("check fsa3 size, should be 1 after 8 alloc", !(FsaCountFree(fsa3) == 1));
	fsa3_alloc9 = FsaAlloc(fsa3); 
	printTest("check fsa3 size, should be 0 after 9 alloc", !(FsaCountFree(fsa3) == 0));
	fsa3_alloc10 = FsaAlloc(fsa3); /* all blocks allocated */
	printTest("check try alloc when full *might not be needed*", !(fsa3_alloc10 == NULL));
	
	
	printf("\ncheck alignment of allocs when first malloc was not aligned and block size isnt word:\n\n");
	printTest("alloc1 aligned?", ((size_t)fsa3_alloc1) % word_size);
	printTest("alloc2 aligned?", ((size_t)fsa3_alloc2) % word_size);
	printTest("alloc3 aligned?", ((size_t)fsa3_alloc3) % word_size);
	printTest("alloc4 aligned?", ((size_t)fsa3_alloc4) % word_size);
	printTest("alloc5 aligned?", ((size_t)fsa3_alloc5) % word_size);
	printTest("alloc6 aligned?", ((size_t)fsa3_alloc6) % word_size);
	printTest("alloc7 aligned?", ((size_t)fsa3_alloc7) % word_size);
	printTest("alloc8 aligned?", ((size_t)fsa3_alloc8) % word_size);
	printTest("alloc9 aligned?", ((size_t)fsa3_alloc9) % word_size);
	free(fsa3_space);
	return 0;
}
