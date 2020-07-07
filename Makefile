#Makefile to compile the xyz2vtk tool

CXX = g++
CXXFLAGS = -O2 -g -fopenmp -std=c++11

MAIN = lmp2op

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

$(MAIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(OBJ) $(MAIN)
