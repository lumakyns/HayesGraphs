CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20

SRC = src/main.cpp
EXEC = bin/main.exe

all: $(EXEC)

$(EXEC): $(SRC) | bin
	$(CXX) $(CXXFLAGS) -o $@ $^

bin:
	mkdir -p bin

clean:
	rm -f $(EXEC)
	rm -rf bin

.PHONY: all clean