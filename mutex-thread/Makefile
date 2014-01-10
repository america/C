target=fire.o

obj=mutex-thread.o

CC=gcc 
CFLAGS=-DSYNC -g -Wall -pthread
#CFLAGS=-g -Wall -pthread

$(target):$(obj)
	$(CC) $(CFLAGS) -o $(target) $(obj)

mutex-thread.o:

.PHONY:clean
clean:
	rm -f $(target) $(obj)
