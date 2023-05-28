#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int wrapper(const char* input, size_t size)
{
    char *buffer = calloc(64, sizeof(*buffer));

    if (!buffer) {
        printf("Allocation failed\n");
        return -1;
    }

    strcpy(buffer,input);

    printf("%s\n", buffer);

    return 0;
}

int LLVMFuzzerTestOneInput(const char *Data, size_t Size) 
{
    if (Size < 1)
    {
        return 0;
    }
    return wrapper(Data, Size);
}
