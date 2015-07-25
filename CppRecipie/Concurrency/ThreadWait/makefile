CC= clang++
CFLAGS= -c -Wall -std=c++1y
LDFLAGS= -g -Wall -std=c++1y -pthread
SOURCES=threads.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE= threads

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean: FORCE
	rm $(OBJECTS)
	
