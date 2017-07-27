CFLAGS = -O2 -Wall -Wextra -pedantic -std=c++14 -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib
CXX = g++


SRC = sales_data_tests.cpp Sales_data.cpp
BINS = sales_data_tests.exe
OBJ = 
DEPS = Sales_data.h


all: $(BINS)


sales_data_tests.exe: $(SRC) $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)


clean:
	rm -f $(BINS) $(OBJ)


.PHONY: all, clean
