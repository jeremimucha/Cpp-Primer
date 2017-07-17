CFLAGS = -O2 -Wall -Wextra -pedantic -std=c++14 -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib
CXX = g++


SRC = quote_tests.cpp quote.cpp ex15.26.cpp
BINS = quote_tests.exe ex15.26.exe
OBJ = 
DEPS = quote.h


all: $(BINS)


quote_tests.exe: quote_tests.cpp quote.cpp $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)

ex15.26.exe: ex15.26.cpp quote.cpp $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(BINS) $(OBJ)


.PHONY: all, clean
