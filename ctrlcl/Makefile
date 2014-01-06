TARGET = ctrlcl

CC = gcc 

CFLAGS = -c -v

VPATH = src
SRC = ctrlcl.c
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
