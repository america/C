target=client.o

src=$(shell ls *.c)
obj=$(src:.c=.o)
dep=$(obj:.o=.d)

CC=gcc 
CFLAGS=-g -Wall -O2 -MMD -MP

$(target):$(obj)
	$(CC) $(CFLAGS) -o $(target) $(obj)

.PHONY:clean
clean:
	rm -f $(target) $(obj) $(dep)

-include $(dep)
