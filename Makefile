CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = cafe_manager
OBJS = main.o cafe.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c cafe.h
	$(CC) $(CFLAGS) -c main.c

cafe.o: cafe.c cafe.h
	$(CC) $(CFLAGS) -c cafe.c

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)