#include<stddef.h>
#include<stdio.h>
void swap_sizet(size_t* var1_p, size_t* var2_p)
{
	size_t tmp = *var1_p;
	*var1_p = *var2_p;
	*var2_p = tmp;
}

void swap_sizet_pointer(size_t** var1_p, size_t** var2_p)
{
	swap_sizet((size_t*)var1_p, (size_t*)var2_p);
}

int main()
{
	size_t a = 3, b = 5;
	size_t* c = &a, *d = &b;
	printf("old a:%lu, b:%lu\n", a, b);
	printf("old c:%p, d:%p\n", (void*)c, (void*)d);
	swap_sizet(&a,&b);
	printf("new a:%lu, b:%lu\n", a, b);
	printf("new c:%p, d:%p\n", (void*)c, (void*)d);
	swap_sizet_pointer(&c,&d);
	printf("very new a:%lu, b:%lu\n", a, b);
	printf("very new c:%p, d:%p\n", (void*)c, (void*)d);
	return 1;
}
