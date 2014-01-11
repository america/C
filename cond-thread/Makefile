target=fire.o

obj=cond-thread.o

CC=gcc 
CFLAGS=-g -Wall -O2 -pthread

$(target):$(obj)
	$(CC) $(CFLAGS) -o $(target) $(obj)

.PHONY:clean
clean:
	rm -f $(target) $(obj)
