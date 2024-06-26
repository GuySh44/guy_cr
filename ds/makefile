CC = @gcc -I include/
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
DEBUG = -g src/my_utils.c
RELEASE = $(CC) $(CFLAGS) -DNDEBUG -O3
GD = $(CC) $(CFLAGS) $(DEBUG)

STACK_SRC = src/stack.c test/stack_test.c
VECTOR_SRC = src/vector.c test/vector_test.c
SLIST_SRC = src/slist.c test/slist_test.c src/snode.c
FSA_SRC = src/fsa.c test/fsa_test.c
SORT_SRC = src/comparison_sort.c test/comparison_sort_test.c 
RECURSION_SRC = src/recursion.c test/recursion_test.c src/stack.c
VSA_SRC = src/vsa.c test/vsa_test.c
BST_SRC = src/bst.c test/bst_test.c src/tnode.c
BINARY_SEARCH_SRC = src/binary_search.c test/binary_search_test.c
AVL_SRC = src/avl.c test/avl_test.c src/avl_node.c
HASH_SRC = src/hash_table.c test/hash_table_test.c src/snode.c src/slist.c
QUEUE_SRC = src/queue.c test/queue_test.c


queue: $(QUEUE_SRC)
	$(GD) $(QUEUE_SRC) -o queue
queue_release: src/queue.c test/main.c
	$(RELEASE) src/queue.c -o queue_release
queue_obj:
	$(CC) -c $(CFLAGS) $(DEBUG) $(QUEUE_SRC)

hash_table: $(HASH_SRC)
	$(GD) $(HASH_SRC) -o hash_table
hash_table_release: src/slist.c src/snode.c src/hash_table.c test/main.c
	$(RELEASE) src/slist.c src/snode.c src/hash_table.c -o slist_release
hash_table_obj:
	$(CC) -c $(CFLAGS) $(DEBUG) $(HASH_SRC)

avl: $(AVL_SRC)
	$(GD) $(AVL_SRC) -o avl
avl_release: src/avl.c src/avl_node.c test/main.c
	$(RELEASE) src/avl.c src/avl_node.c -o avl_release
avl_obj:
	$(CC) -c $(CFLAGS) $(DEBUG) $(AVL_SRC)

binary_search: $(BINARY_SEARCH_SRC)
	$(GD) $(BINARY_SEARCH_SRC) -o binary_search
binary_search_release: src/binary_search.c test/binary_search_test.c
	$(GD) -DNDEBUG src/binary_search.c test/binary_search_test.c -o binary_search_release
binary_search_obj:
	$(CC) -c $(CFLAGS) $(DEBUG) $(BINARY_SEARCH_SRC)

bst: $(BST_SRC)
	$(GD) $(BST_SRC) -o bst
bst_release: src/bst.c src/tnode.c test/main.c
	$(RELEASE) src/bst.c src/tnode.c -o bst_release
bst_obj:
	$(CC) -c $(CFLAGS) $(DEBUG) $(BST_SRC)

vsa: $(VSA_SRC)
	$(GD) $(VSA_SRC) -o vsa
vsa_release: src/vsa.c test/vsa_release.c
	$(GD) -DNDEBUG src/vsa.c test/vsa_release.c -o vsa_release
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

