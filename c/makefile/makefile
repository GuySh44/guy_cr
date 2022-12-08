OBJS = foo.o main.o
CC = @gcc -I -L include/
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
DEBUG = -g 
RELEASE = -DNDEBUG -O3
GD = $(CC) $(CFLAGS) $(DEBUG) $(OBJS)

fooer : $(OBJS)
	$(GD) -o fooer.out

all : main.o foo.o
main.o : foo.h
foo.o : foo.h foo.c

stack_test.o : stack.h
stack.o : stack.h
stack : stack_test.o stack.o
	$(GD) -o stack 

.PHONY : clean debug release
clean:
	@-rm fooer.out $(OBJS)
debug: fooer
release: $(OBJS)
	$(CC) $(CFLAGS) $(RELEASE) $(OBJS) -o fooer.out
