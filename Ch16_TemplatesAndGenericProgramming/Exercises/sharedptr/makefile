CFLAGS = -O2 -Wall -Wextra -pedantic -std=c++11 -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib
CXX = g++


SRC = sharedptr_tests.cpp
BINS = sharedptr_tests.exe
OBJ = 
DEPS = sharedptr.h


all: $(BINS)


sharedptr_tests.exe: sharedptr_tests.cpp $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)


clean:
	rm -f $(BINS) $(OBJ)


.PHONY: all, clean
