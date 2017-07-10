CFLAGS = -O2 -Wall -Wextra -pedantic -std=c++14 -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib
CXX = g++


SRC = $(wildcard *.cpp)
BINS = textquery_test.exe
OBJ = textquery.o
DEPS = textquery.h


all: $(BINS)

textquery.o: textquery.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CFLAGS)

textquery_test.exe: textquery_test.cpp $(OBJ) $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)


clean:
	rm -f $(BINS) $(OBJ)


.PHONY: all, clean
