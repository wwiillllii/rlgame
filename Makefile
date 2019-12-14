CC := gcc
CFLAGS := -std=c++11 -Wall -Wextra
LDFLAGS := -lstdc++ -ldl

SOURCE_DIR := src/
INCLUDE_DIR := include/
OBJECT_DIR := obj/
API_DIR := api/

CFLAGS := $(CFLAGS) -I$(INCLUDE_DIR) -I$(API_DIR)

SOURCES := $(shell find $(SOURCE_DIR) -name *.cpp)
OBJECTS := $(subst $(SOURCE_DIR), $(OBJECT_DIR), $(SOURCES))
OBJECTS := $(OBJECTS:.cpp=.o)

all: main

clean:
	rm -f main
	rm -f $(OBJECTS)

main: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

modules/%.so: modules/src/%.cpp
	$(CC) $(CFLAGS) $^ -fPIC -shared -o $@

$(OBJECT_DIR)%.o: $(SOURCE_DIR)%.cpp
	@mkdir -p $(OBJECT_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@
