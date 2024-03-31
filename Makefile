# Makefile

CXX = g++ # Compiler
CXXFLAGS = -O3 -std=c++11 # Flags

# Target executable name
TARGET = main

SRCS = main.cpp file_parser.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<  -o $@

clean:
	$(RM) $(OBJS) $(TARGET)
