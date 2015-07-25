CC= clang++
CFLAGS= -g -Wall -std=c++1y
LDFLAGS=-g -Wall -std=c++1y
SOURCES=Time.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE= Time

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
