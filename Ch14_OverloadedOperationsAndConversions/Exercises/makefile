CFLAGS = -O2 -Wall -Wextra -pedantic -std=c++14 -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib
CXX = g++


SRC = $(wildcard *.cpp)
BINS = $(patsubst %.cpp, %.exe, $(SRC))
OBJ = $(patsubst %.cpp, %.o, $(BINS))
DEPS = 


all: $(BINS)


%.exe: %.cpp $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)


clean:
	rm -f $(BINS) $(OBJ)


.PHONY: all, clean
