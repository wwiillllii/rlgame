CC := gcc
CFLAGS := -Wall -Wextra
LDFLAGS := -ldl

SOURCE_DIR := src/
INCLUDE_DIR := include/
OBJECT_DIR := obj/

CFLAGS := $(CFLAGS) -I$(INCLUDE_DIR)

SOURCES := $(shell find $(SOURCE_DIR) -name *.c)
OBJECTS := $(subst $(SOURCE_DIR), $(OBJECT_DIR), $(SOURCES))
OBJECTS := $(OBJECTS:.c=.o)

all: main

clean:
	rm main
	rm -f $(OBJECTS)

main: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJECT_DIR)%.o: $(SOURCE_DIR)%.c
	mkdir -p $(OBJECT_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@
