CFLAGS = -O2 -Wall -Wextra -pedantic -std=c++11 -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib
CXX = g++


SRC = strblob_test.cpp ex12.20.cpp
BINS = strblob_test.exe ex12.20.exe
OBJ = 
DEPS = strblob.h strblobptr.h


all: $(BINS)


strblob_test.exe: strblob_test.cpp $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)


ex12.20.exe: ex12.20.cpp $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)


clean:
	rm -f $(BINS) $(OBJ)


.PHONY: all, clean
