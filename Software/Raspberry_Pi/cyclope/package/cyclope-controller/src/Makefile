CC = g++
CCFLAGS = -W -Wall

BINARY = cyclope-controller
INCLUDES = -IIncludes
SOURCES = $(shell find Sources -iname "*.cpp")

all:
	$(CC) $(CCFLAGS) $(INCLUDES) $(SOURCES) -o $(BINARY)

clean:
	rm -f $(BINARY)
