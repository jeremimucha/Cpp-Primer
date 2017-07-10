CFLAGS = -O2 -Wall -Wextra -pedantic -std=c++11 -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib
CXX = g++


SRC = message_folder_tests.cpp message.cpp folder.cpp
BINS = message_folder_tests.exe
OBJ = 
DEPS = message.h folder.h


all: $(BINS)


message_folder_tests.exe: $(SRC) $(DEPS)
	$(CXX) -o $@ $^ $(CFLAGS)


clean:
	rm -f $(BINS) $(OBJ)


.PHONY: all, clean
