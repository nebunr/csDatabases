# makefile
CC=g++

# Compiler Flags
CXXFLAGS=-std=c++11

# .o Compilation
FILES=main.cpp parser.cpp

all: $(O_FILES)
	$(CC) $(CXXFLAGS) $(FILES) -o pa 

clean:
	-@if rm pa 2>/dev/null || true; then echo "Main Removed"; else echo "No Main"; fi