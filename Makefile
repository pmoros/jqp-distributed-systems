CC = gcc
CFLAGS = -Wall -Wextra
TARGET = jgs
SOURCE = src/main.c  # Change this to your source file's name

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)
