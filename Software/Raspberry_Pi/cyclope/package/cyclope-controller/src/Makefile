CC = g++
CCFLAGS = -W -Wall

BINARY = cyclope-controller
INCLUDES = -IIncludes
LIBRARIES = -pthread
SOURCES = $(shell find Sources -iname "*.cpp")

all:
	$(CC) $(CCFLAGS) $(INCLUDES) $(SOURCES) $(LIBRARIES) -o $(BINARY)

clean:
	rm -f $(BINARY)
