CC = gcc
CFLAGS = -c -Wall
LDFLAGS = -l SDL2
SOURCES = main.c
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = 0x40Hues

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f 0x40Hues *.o

run: all
	./0x40Hues
