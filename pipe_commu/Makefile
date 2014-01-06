CC = gcc 

CFLAGS = 

VPATH = src
SRC = pipe_commu.c child.c

.SUFFIXES: .c .o

all:pipe_commu.o child.o

pipe_commu.o:pipe_commu.c
	$(CC) $(CFLAGS) -o pipe_commu.o $< 

child.o:child.c
	$(CC) $(CFLAGS) -o child.o $< 
clean:
	rm -f *.o
