CFLAGS = -O2 -Wall -Wextra -pedantic -std=c++11 -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib
CXX = g++


SRC = vec_tests.cpp
BINS = vec_tests.exe
OBJ = 
DEPS = vec.h


all: $(BINS)


vec_tests.exe: vec_tests.cpp $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)


clean:
	rm -f $(BINS) $(OBJ)


.PHONY: all, clean
