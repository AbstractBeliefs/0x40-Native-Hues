CC = gcc
CFLAGS = -std=c11 -c -Wall
LDFLAGS = -lSDL2 -lSDL2_image
SOURCES = main.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = 0x40Hues

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f 0x40Hues *.o

run: all
	./0x40Hues
