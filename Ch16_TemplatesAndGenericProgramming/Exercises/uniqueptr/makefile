CFLAGS = -O2 -Wall -Wextra -pedantic -std=c++11 -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib
CXX = g++


SRC = uniqueptr_tests.cpp
BINS = uniqueptr_tests.exe
OBJ = 
DEPS = uniqueptr.h


all: $(BINS)


uniqueptr_tests.exe: uniqueptr_tests.cpp $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)


clean:
	rm -f $(BINS) $(OBJ)


.PHONY: all, clean
