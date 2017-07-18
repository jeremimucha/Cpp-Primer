CFLAGS = -O2 -Wall -Wextra -pedantic -std=c++14 -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib
CXX = g++


SRC = quote_tests.cpp exs15.8.1.cpp quote.cpp basket.cpp
BINS = quote_tests.exe exs15.8.1.exe
OBJ = 
DEPS = quote.h basket.h


all: $(BINS)


quote_tests.exe: quote_tests.cpp quote.cpp $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)

exs15.8.1.exe: exs15.8.1.cpp quote.cpp basket.cpp $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(BINS) $(OBJ)


.PHONY: all, clean
