CXX ?= g++

BINARY = cyclope-controller
INCLUDES = -IIncludes
LIBRARIES = -pthread -lopencv_videoio -lopencv_imgcodecs -lopencv_imgproc -lopencv_core
SOURCES = $(wildcard Sources/*.cpp)

all:
	$(CXX) $(CXXFLAGS) -W -Wall $(INCLUDES) $(SOURCES) $(LIBRARIES) -o $(BINARY)

clean:
	rm -f $(BINARY)
