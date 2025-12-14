CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = cafe_program
OBJS = main.o cafe.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c cafe.h
	$(CC) $(CFLAGS) -c main.c

cafe.o: cafe.c cafe.h
	$(CC) $(CFLAGS) -c cafe.c

clean:
	del *.o $(TARGET).exe 2>nul || true

run: $(TARGET)
	.\$(TARGET).exe

.PHONY: all clean run
