CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I include
TARGET = build/virtual-cpu
TEST_TARGET = build/virtual-cpu-tests
ASM_TARGET = build/assembler

# Filter out assembler.cpp from SRC just in case to prevent linker crashes
SRC      = $(filter-out src/assembler.cpp, $(wildcard src/*.cpp))
TEST_SRC = $(wildcard test/*.cpp)
ASM_SRC  = boiler-plate/assembler.cpp
CORE_LOGIC = $(filter-out src/main.cpp, $(SRC))

FORMATTER = clang-format
FORMAT_FLAGS = -i -style=file

all: build test format

build: $(SRC)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)
	$(CXX) $(CXXFLAGS) -o $(ASM_TARGET) $(ASM_SRC)

test: $(ALL_FILES)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(CORE_LOGIC) $(TEST_SRC)
	@./$(TEST_TARGET)

format:
	find . -iname "*.cpp" -o -iname "*.hpp" -o -iname "*.c" -o -iname "*.h" | xargs $(FORMATTER) $(FORMAT_FLAGS)

clean:
	rm -f $(TARGET)
	rm -f $(ASM_TARGET)
	rm -r $(TEST_TARGET)

.PHONY: build test clean all format
