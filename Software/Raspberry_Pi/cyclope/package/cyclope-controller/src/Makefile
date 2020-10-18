CXX ?= g++
CXXFLAGS += -W -Wall

BINARY = cyclope-controller
INCLUDES = -IIncludes
LIBRARIES = -pthread -lopencv_videoio -lopencv_imgcodecs -lopencv_imgproc -lopencv_core
SOURCES = $(shell find Sources -iname "*.cpp")

all:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SOURCES) $(LIBRARIES) -o $(BINARY)

clean:
	rm -f $(BINARY)
