#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
    int i = 8;
    int j = 16;
    int k = 32;
    int *p = &j;

    FILE *fp;

    if(0 == (fp = fopen("stoopid", "r")))
    {
        printf("well, that didn\'t work!\n");
        return -1;
    }
	printf("i address:\t%p\n",&i);
	printf("j address:\t%p\n",&j);
	printf("k address:\t%p\n",&k);
	printf("p:\t%p\n",p);
    fscanf(fp, "%p\n", &p);

    if(fclose(fp))
    {
        printf("oh well.");
        return -1;
    }

    printf("p points to: %d\n", *p);

    return 0;
}
