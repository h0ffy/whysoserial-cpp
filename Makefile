# Makefile for the Java payload generator in C++

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = ysoserial-cpp
SOURCE = ysoserial-cpp.cpp

# Main rule
all: $(TARGET)

# Compile the program
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

# Clean generated files
clean:
	rm -f $(TARGET) *.ser *.o

# Install (optional)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Basic tests
test: $(TARGET)
	@echo "Running basic tests..."
	./$(TARGET) object1 bash -c "whoami"
	@echo "Test completed. Check the object1_payload.obj file"

# Generate all example payload types
examples: $(TARGET)
	@echo "Generating example payloads..."
	./$(TARGET) object1 "whoami"
	./$(TARGET) object2 "id"
	./$(TARGET) templates "calc.exe"
	@echo "Examples generated in .ser files"

# Rule to display help
help:
	@echo "Makefile usage:"
	@echo "  make          - Compile the program"
	@echo "  make clean    - Clean generated files"
	@echo "  make test     - Run basic tests"
	@echo "  make examples - Generate all example payloads"
	@echo "  make install  - Install to /usr/local/bin"
	@echo "  make help     - Show this help"

# Debug build
debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

.PHONY: all clean test examples help install debug
