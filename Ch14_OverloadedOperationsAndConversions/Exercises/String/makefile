CFLAGS = -O2 -Wall -Wextra -pedantic -std=c++11 -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib
CXX = g++


SRC = String_tests.cpp String.cpp
BINS = String_tests.exe
OBJ = 
DEPS = String.h


all: $(BINS)


String_tests.exe: $(SRC) $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)


clean:
	rm -f $(BINS) $(OBJ)


.PHONY: all, clean
