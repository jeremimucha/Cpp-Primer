CFLAGS = -O2 -Wall -Wextra -pedantic -std=c++11
CXX = g++


SRC = screen_tests.cpp screen.cpp
BINS = screen_tests.exe
OBJ =
DEPS = screen.h window_mgr.h


all: $(BINS)


screen_tests.exe: $(SRC) $(OBJ) $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)


clean:
	rm -f $(BINS) $(OBJ)


.PHONY: all, clean
