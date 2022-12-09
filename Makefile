CXX = g++
CXXFLAGS = -O3 -std=c++11 -Wall -g
TARGETS = solution1

.PHONY: all run clean

all: $(TARGETS)

run:
	./$(TARGETS) < input.txt

clean:
	rm -f *.o $(TARGETS)