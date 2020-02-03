# makefile
CC=g++
#LIBS=unused

# Compiler Flags
CXXFLAGS=-std=c++11

# .o Compilation
O_FILES=main.o

# Point to includes of local directories
#INCLUDES=unused

all: $(O_FILES)
	$(CC) $(CXXFLAGS) -o pa1 $(O_FILES) #$(LIBS)

main.o: main.cpp
	$(CC) $(CXXFLAGS) -c main.cpp -o main.o #$(INCLUDES)

clean:
	-@if rm pa1 2>/dev/null || true; then echo "Main Removed"; else echo "No Main"; fi