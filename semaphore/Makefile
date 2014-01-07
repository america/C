CC=gcc 

#CFLAGS= -v
CFLAGS= -DSYNC -v

VPATH=src

all:semaphore.o

semaphore.o:semaphore.c
	$(CC) $(CFLAGS) -o semaphore.o $< 

clean:
	rm -f *.o
