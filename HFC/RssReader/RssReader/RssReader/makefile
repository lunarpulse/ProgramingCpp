CC= clang++
CFLAGS= -c -Wall -std=c++1y
LDFLAGS= -g -Wall -std=c++1y
SOURCES=RrsReader.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE= RrsReader1

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean: FORCE
	rm $(OBJECTS)
	
