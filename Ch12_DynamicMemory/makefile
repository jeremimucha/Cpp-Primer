CFLAGS = -O2 -Wall -Wextra -pedantic -std=c++11 -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib
CXX = g++


SRC = strblob_test.cpp
BINS = strblob_test.exe
OBJ = 
DEPS = strblob.h


all: $(BINS)


strblob_test.exe: strblob_test.cpp $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)


clean:
	rm -f $(BINS) $(OBJ)


.PHONY: all, clean
