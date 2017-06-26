CFLAGS = -O2 -Wall -Wextra -pedantic -std=c++11
CXX = g++


SRC = screen_tests.cpp
BINS = $(patsubst %.cpp, %.exe, $(SRC))
OBJ =
DEPS = screen.h window_mgr.h


all: $(BINS)


screen_tests.exe: screen_tests.cpp $(OBJ) $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)


clean:
	rm -f $(BINS) $(OBJ)


.PHONY: all, clean
