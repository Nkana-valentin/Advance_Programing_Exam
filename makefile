SRC = benchmark.cpp

CXX = g++
CXXFLAGS = -Wall -Wextra -Wpeadantic -03 -std=c++14

EXE = $(SRC: .cpp =.x)

all: $(EXE)

.PHONY: all
%.o: $.cpp
        $(CXX) -c $< -o $@ $(CXXFLAGS)

%.x: %.o
       $(CXX) $^ -o $@ $(CXXFLAGS)

clean:
     rm -f $(EXE) *- *.o

.PHONY: clean

benchmark.o : bst.hpp




