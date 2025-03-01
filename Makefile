CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -Wno-sign-compare
INCLUDE_PATH = -Iinclude
SRC = src/main.cpp src/graphHelpers.cpp
EXEC = bin/main.exe

# Detect OS
ifeq ($(OS),Windows_NT)
    EXEC := bin/main.exe
    RM = del /Q
    MKDIR = if not exist bin mkdir bin
else
    RM = rm -f
    MKDIR = mkdir -p bin
endif

all: $(EXEC)

$(EXEC): $(SRC) | bin
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) -o $@ $^

bin:
	$(MKDIR)

clean:
	$(RM) -r bin
	$(MKDIR)

.PHONY: all clean
