CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I include
TARGET = build/virtual-cpu
SRC = src/main.cpp
TEST_SRC = test/test_main.cpp
TEST_TARGET = build/virtual-cpu-tests

all: build test

build: $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

test: $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_SRC) && ./$(TEST_TARGET)

clean:
	rm -f $(TARGET)
	rm -r $(TEST_TARGET)

.PHONY: build test clean all
