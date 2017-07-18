CFLAGS = -O2 -Wall -Wextra -pedantic -std=c++14 -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib
CXX = g++


SRC = query_tests.cpp query.cpp textquery.cpp
BINS = query_tests.exe
OBJ = 
DEPS = query.h textquery.h


all: $(BINS)


quote_tests.exe: quote_tests.cpp quote.cpp $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)

exs15.8.1.exe: exs15.8.1.cpp quote.cpp basket.cpp $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(BINS) $(OBJ)


.PHONY: all, clean
