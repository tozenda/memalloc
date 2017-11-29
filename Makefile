CC=gcc
CFLAGS=-Wall -g

all: memshell

memshell: memshell.o alloc.o

alloc.o : alloc.c

memshell.o : memshell.c

clean:
	rm -f memshell.o alloc.o
