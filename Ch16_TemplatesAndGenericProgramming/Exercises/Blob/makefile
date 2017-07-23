CFLAGS = -O2 -Wall -Wextra -pedantic -std=c++11 -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib
CXX = g++


SRC = blob_test.cpp
BINS = blob_test.exe
OBJ = 
DEPS = blob.h blobptr.h


all: $(BINS)


blob_test.exe: blob_test.cpp $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)


clean:
	rm -f $(BINS) $(OBJ)


.PHONY: all, clean
