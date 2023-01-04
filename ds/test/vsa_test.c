#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "vsa.h"
#include "my_utils.h"

int main()
{	
	vsa_t *vsa1 = VsaInit(malloc(192), 192);
	
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
	printf("FAMOUS TEST CASE I COULDNT SHUT UP ABOUT\n\n");
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
	
	free(vsa1);
	return 0;
}
