CC = @gcc -I include/
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
DEBUG = -g src/my_utils.c
RELEASE = $(CC) $(CFLAGS) -DNDEBUG -O3 test/main.c
GD = $(CC) $(CFLAGS) $(DEBUG)

STACK_SRC = src/stack.c test/stack_test.c
VECTOR_SRC = src/vector.c test/vector_test.c
SLIST_SRC = src/slist.c test/slist_test.c src/snode.c
FSA_SRC = src/fsa.c test/fsa_test.c
SORT_SRC = src/comparison_sort.c test/comparison_sort_test.c 
RECURSION_SRC = src/recursion.c test/recursion_test.c src/stack.c
VSA_SRC = src/vsa.c test/vsa_test.c

vsa: $(VSA_SRC)
	$(GD) $(VSA_SRC) -o vsa
vsa_release: src/vsa.c test/main.c
	$(RELEASE) src/vsa.c -o vsa_release
vsa_obj:
	$(CC) -c $(CFLAGS) $(DEBUG) $(VSA_SRC)

recursion: $(RECURSION_SRC)
	$(GD) $(RECURSION_SRC) -o recursion
recursion_release: src/recursion.c test/main.c src/stack.c
	$(RELEASE) src/recursion.c src/stack.c -o recursion_release
recursion_obj:
	$(CC) -c $(CFLAGS) $(DEBUG) $(RECURSION_SRC)
	
comparison_sort: $(SORT_SRC)
	$(GD) $(SORT_SRC) -o comparison_sort
comparison_sort_release: src/comparison_sort.c test/main.c
	$(RELEASE) src/comparison_sort.c -o comparison_sort_release
comparison_sort_obj:
	$(CC) -c $(CFLAGS) $(DEBUG) $(SORT_SRC)
	
fsa: $(FSA_SRC)
	$(GD) $(FSA_SRC) -o fsa
fsa_release: src/fsa.c test/main.c
	$(RELEASE) src/fsa.c -o fsa_release
fsa_obj:
	$(CC) -c $(CFLAGS) $(DEBUG) $(FSA_SRC)

slist: $(SLIST_SRC)
	$(GD) $(SLIST_SRC) -o slist
slist_release: src/slist.c src/snode.c test/main.c
	$(RELEASE) src/slist.c src/snode.c -o slist_release
slist_obj:
	$(CC) -c $(CFLAGS) $(DEBUG) $(SLIST_SRC)

vector: $(VECTOR_SRC)
	$(GD) $(VECTOR_SRC) -o vector
vector_release: src/vector.c test/main.c
	$(RELEASE) src/vector.c -o vector_release
vector_obj:
	$(CC) -c $(CFLAGS) $(DEBUG) $(VECTOR_SRC)

stack: $(STACK_SRC)
	$(GD) $(STACK_SRC) -o stack
stack_release: src/stack.c test/main.c
	$(RELEASE) src/stack.c -o stack_release
stack_obj:
	$(CC) -c $(CFLAGS) $(DEBUG) $(STACK_SRC)

.PHONY : clean
clean:
	@-rm -f *.out
	@-rm -f *.o

