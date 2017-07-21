CFLAGS = -O2 -Wall -Wextra -pedantic -std=c++14 -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib
CXX = g++


SRC = query_tests.cpp query.cpp textquery.cpp
BINS = query_tests.exe
OBJ = 
DEPS = query.h query_alt.h textquery.h


all: $(BINS)


query_tests.exe: $(SRC) $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)


clean:
	rm -f $(BINS) $(OBJ)


.PHONY: all, clean
