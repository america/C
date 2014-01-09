CC=gcc 

CFLAGS= -g -Wall -pthread

VPATH=src

all:thread-attr.o

thread-attr.o:thread-attr.c
	$(CC) $(CFLAGS) -o thread-attr.o $< 

clean:
	rm -f *.o
