# Makefile for gatorLibrary

CXX = g++ # Compiler
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic # Compiler flags
SRC = gatorLibrary.cpp # Source file
TARGET = gatorLibrary # Executable name

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean
