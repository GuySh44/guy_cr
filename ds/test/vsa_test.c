#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "vsa.h"
#include "my_utils.h"

int main()
{	
	vsa_t *vsa1 = VsaInit(malloc(192), 192);
	void *vsa2_space = malloc(200);
	vsa_t *vsa2 = VsaInit(((char*)vsa2_space + 3), 197);
	
	size_t largest_chunk1 = VsaLargestChunk(vsa1);
	
	void *first_aloc, *second_aloc, *third_aloc;
	
	printf("vsa1 largest chunk:\t%lu\n", largest_chunk1);
	
	first_aloc = VsaAlloc(vsa1, largest_chunk1);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("MINIMAL FUNCTIONALITY TEST\n\n");
	
	printTest("alloc of 1 block full size available, LargestChunk returns 0? ", !(VsaLargestChunk(vsa1) == 0));
	
	printTest("try to alloc again, should return NULL", !(VsaAlloc(vsa1, 1) == NULL));
	
	printf("copying exact size string into alloc1\n");
	strcpy(first_aloc, "abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789777");
	
	printTest("did first aloc get the string", strcmp(first_aloc, "abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789777"));
	
	VsaFree(first_aloc);
	
	printTest("check if free on alloc1 worked fine, LargestChunk returns original LargestChunk?", !(largest_chunk1 == VsaLargestChunk(vsa1)));
	
		
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("TEST CASE I COULDNT SHUT UP ABOUT\n\n");
	first_aloc = VsaAlloc(vsa1, 24);
	
	printTest("Is LargestChunk right while linear allocing... after alloc1 ", !(VsaLargestChunk(vsa1) == 72));
	
	second_aloc = VsaAlloc(vsa1, 16);
	
	printTest("Is LargestChunk right while linear allocing... after alloc2 ", !(VsaLargestChunk(vsa1) == 32));
	
	third_aloc = VsaAlloc(vsa1, 32);
		
	printTest("Is LargestChunk right while linear allocing... after alloc3 ", !(VsaLargestChunk(vsa1) == 0));
	
	VsaFree(second_aloc);
	
	printTest("Is LargestChunk right after freeing middle... free alloc2 ", !(VsaLargestChunk(vsa1) == 16));

	second_aloc = VsaAlloc(vsa1, 8);
	
	
	printTest("Creating Fragmantation of word between alloc2 and alloc3", !(VsaLargestChunk(vsa1) == 0));
	
	strcpy(second_aloc, "abcdefg");
	
	printTest("Did usage of second aloc go as expected?", strcmp(second_aloc, "abcdefg"));
	
	VsaFree(third_aloc);
	
	printTest("Is LargestChunk right after defraging fragmantation... free alloc3 ", !(VsaLargestChunk(vsa1) == 40));
	
	third_aloc = VsaAlloc(vsa1,40);
	
	printTest("Check we can use defraged memory", !(VsaLargestChunk(vsa1) == 0));
	
	strcpy(third_aloc, "abcdefghijklmnopqrstuvwxyz0123456789abc");
	
	printTest("Did usage of third aloc go as expected?", strcmp(third_aloc, "abcdefghijklmnopqrstuvwxyz0123456789abc"));
	
	printTest("Did second aloc change becuase of bad treatment?", strcmp(second_aloc, "abcdefg"));
	
	VsaFree(third_aloc);
	
	VsaFree(second_aloc);
	
	VsaFree(first_aloc);
	
	printTest("Can we survive defrag of couple of frees? and keep our original size", !(largest_chunk1 == VsaLargestChunk(vsa1)));
	
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("MULTIPLE ALLOCS WITH DIFFERENT FREE ORDER, DEFRAGING, END OF POOL FRAGMENTATION\n\n");
	
	first_aloc = VsaAlloc(vsa1, 24);
	second_aloc = VsaAlloc(vsa1, 16);
	third_aloc = VsaAlloc(vsa1, 24);
		
	printTest("Creating Fragmantation of word between alloc3 and end", !(VsaLargestChunk(vsa1) == 0));
	
	VsaFree(third_aloc);
	
	printTest("Check if we defrag right next to end", !(VsaLargestChunk(vsa1) == 32));
	
	
	third_aloc = VsaAlloc(vsa1, 32);
	
	printTest("Did we allocate maximal size", !(VsaLargestChunk(vsa1) == 0));
	
	VsaFree(first_aloc);
	VsaFree(third_aloc);
	
	printTest("Does LargestChunk compare right between free blocks", !(VsaLargestChunk(vsa1) == 32));
	
	first_aloc = VsaAlloc(vsa1, 24);
		
	printTest("Does LargestChunk stay right after smaller free alloced", !(VsaLargestChunk(vsa1) == 32));
	
	VsaFree(second_aloc);
	
	printTest("LargestChunk after defrag alloc2 and alloc3 space", !(VsaLargestChunk(vsa1) == 72));
	
	second_aloc = VsaAlloc(vsa1, 16);
	
	third_aloc = VsaAlloc(vsa1, 32);
	
	VsaFree(first_aloc); 
	
	VsaFree(second_aloc);
	
	printTest("LargestChunk after defrag alloc1 and alloc2 space", !(VsaLargestChunk(vsa1) == 64));
	
	VsaFree(third_aloc);
	
	free(vsa1);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("ALIGNMENT AND ALLOC SIZE GIVEN DIFFERENT THEN WORD\n\n");
	
	first_aloc = VsaAlloc(vsa2, 22);
	second_aloc = VsaAlloc(vsa2, 14);
	third_aloc = VsaAlloc(vsa2, 21);
		
	printTest("Creating Fragmantation of word between alloc3 and end", !(VsaLargestChunk(vsa2) == 0));
	
	VsaFree(third_aloc);
	
	printTest("Check if we defrag right next to end", !(VsaLargestChunk(vsa2) == 32));
	
	
	third_aloc = VsaAlloc(vsa2, 30);
	
	printTest("Did we allocate maximal size", !(VsaLargestChunk(vsa2) == 0));
	
	VsaFree(first_aloc);
	VsaFree(third_aloc);
	
	printTest("Does LargestChunk compare right between free blocks", !(VsaLargestChunk(vsa2) == 32));
	
	first_aloc = VsaAlloc(vsa2, 19);
		
	printTest("Does LargestChunk stay right after smaller free alloced", !(VsaLargestChunk(vsa2) == 32));
	
	VsaFree(second_aloc);
	
	printTest("LargestChunk after defrag alloc2 and alloc3 space", !(VsaLargestChunk(vsa2) == 72));
	
	second_aloc = VsaAlloc(vsa2, 13);
	
	third_aloc = VsaAlloc(vsa2, 29);
	
	VsaFree(first_aloc); 
	
	VsaFree(second_aloc);
	
	printTest("LargestChunk after defrag alloc1 and alloc2 space", !(VsaLargestChunk(vsa2) == 64));
	
	VsaFree(third_aloc);
	
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	
	free(vsa2_space);
	
	return 0;
}
