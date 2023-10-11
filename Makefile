CC = gcc
CFLAGS = -Wall -Wextra
TARGET = bin/jgs  # Output to the 'bin' folder
SOURCE = main.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)
