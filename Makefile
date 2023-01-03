CXX = g++
CXXFLAGS = -O3 -std=c++11 -Wall -g
TARGETS = solution2
TESTS = $(wildcard tests/*)

.PHONY: all run test clean

all: $(TARGETS)

run: $(TARGETS)
	./$(TARGETS) < input.txt

test: $(TARGETS)
	for f in $(TESTS); do \
	./$(TARGETS) < $$f ; \
	done

clean:
	rm -f *.o $(TARGETS)