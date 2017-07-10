CFLAGS = -O2 -Wall -Wextra -pedantic -std=c++11 -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib
CXX = g++


SRC = employee_tests.cpp employee.cpp
BINS = employee_tests.exe
OBJ = 
DEPS = employee.h


all: $(BINS)


employee_tests.exe: employee_tests.cpp employee.cpp $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)


clean:
	rm -f $(BINS) $(OBJ)


.PHONY: all, clean
