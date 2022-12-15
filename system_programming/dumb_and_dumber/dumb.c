#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
    int i = 7;
    int j = 12;
    int k = 15;
    int *p = &k;

    FILE *fp;

    if(0 == (fp = fopen("stoopid", "w")))
    {
        printf("well, that didn\'t work!\n");
        return -1;
    }

	printf("i address:\t%p\n",&i);
	printf("j address:\t%p\n",&j);
	printf("k address:\t%p\n",&k);
	printf("p:\t%p\n",p);
    fprintf(fp, "%p\n", p);

    if(fclose(fp))
    {
        printf("oh well.");
        return -1;
    }

    sleep(300);

    return 0;
}
