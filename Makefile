CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I include
TARGET = build/virtual-cpu
TEST_TARGET = build/virtual-cpu-tests

SRC      = $(wildcard src/*.cpp)
TEST_SRC = $(wildcard test/*.cpp)
CORE_LOGIC = $(filter-out src/main.cpp, $(SRC))

all: build test

build: $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

test: $(ALL_FILES)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(CORE_LOGIC) $(TEST_SRC)
	@./$(TEST_TARGET)

clean:
	rm -f $(TARGET)
	rm -r $(TEST_TARGET)

.PHONY: build test clean all
