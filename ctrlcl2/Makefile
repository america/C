TARGET = ctrlcl2

CC = gcc 

CFLAGS = -c -v

VPATH = src
SRC = ctrlcl2.c
OBJ = $(SRC:.c=.o)

all:$(TARGET)

$(TARGET):$(OBJ)
	$(CC) -o $@ $(OBJ)

.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) $<
clean:
	rm -f $(TARGET) $(TARGET).exe
	rm -f *.o *.obj
