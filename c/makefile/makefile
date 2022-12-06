OBJS = foo.o main.o
CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra
DEBUG = -g 
RELEASE = -DNDEBUG

fooer : $(OBJS)
	cc $(CFLAGS) $(DEBUG) $(OBJS) -o fooer.out

all: main.o foo.o	
main.o : foo.h
foo.o : foo.h foo.c

.PHONY : clean debug release
clean:
	@rm fooer.out $(OBJS)
debug: fooer
release: $(OBJS)
	cc $(CFLAGS) $(RELEASE) $(OBJS) -o fooer.out
