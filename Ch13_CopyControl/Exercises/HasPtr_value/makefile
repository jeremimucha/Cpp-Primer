CFLAGS = -O2 -Wall -Wextra -pedantic -std=c++11 -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib
CXX = g++


SRC = hasptr_tests.cpp
BINS = hasptr_tests.exe
OBJ = 
DEPS = hasptr_val.h


all: $(BINS)


hasptr_tests.exe: hasptr_tests.cpp $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)


clean:
	rm -f $(BINS) $(OBJ)


.PHONY: all, clean
