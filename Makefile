CXX = g++
CXXFLAGS = -Wall -g
TARGETS = solution1

.PHONY: all run clean

all: $(TARGETS)

run:
		./$(TARGETS) < input.txt

clean: 
		rm -f *.o $(TARGETS)