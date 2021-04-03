SRC = benchmark.cpp

CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -O3 -std=c++14

EXE = $(SRC:.cpp=.x)

all: $(EXE)

.PHONY: all

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

%.x: %.o
	$(CXX) $^ -o $@ $(CXXFLAGS)
	
clean:
	rm -f $(EXE) *~ *.o

.PHONY: clean

benchmark.o : bst.hpp
