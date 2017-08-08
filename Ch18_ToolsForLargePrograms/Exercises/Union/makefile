CFLAGS = -O2 -Wall -Wextra -pedantic -std=c++11
CXX = g++


SRC = token_tests.cpp token.cpp
BINS = token_tests.exe
OBJ =
DEPS = token.h


all: $(BINS)


token_tests.exe: $(SRC) $(OBJ) $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)


clean:
	rm -f $(BINS) $(OBJ)


.PHONY: all, clean
