CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I include
TARGET = build/virtual-cpu
TEST_TARGET = build/virtual-cpu-tests
ASM_TARGET = build/assembler

# Smartly find the assembler whether they named the folder boiler-plate or assembly-files
ASM_SRC = $(wildcard boiler-plate/assembler.cpp src/assembler.cpp assembly-files/assembler.cpp)

# Safely grab CPU files without grabbing the assembler
ALL_SRC  = $(wildcard src/*.cpp)
SRC      = $(filter-out src/assembler.cpp, $(ALL_SRC))

TEST_SRC = $(wildcard test/*.cpp)
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

# Changed -r to -rf so 'make clean' doesn't crash when files are missing
clean:
	rm -f $(TARGET)
	rm -f $(ASM_TARGET)
	rm -rf $(TEST_TARGET)
	rm -f machine_code.bin

run-fibo: build
	@./$(ASM_TARGET) ./assembly-files/fibonacci.asm && ./$(TARGET)

run-helloworld: build
	@./$(ASM_TARGET) ./assembly-files/helloWorld.asm && ./$(TARGET)

# running run-timer with verbose mode
run-timer: build
	@./$(ASM_TARGET) ./assembly-files/timer.asm && ./$(TARGET) -v

.PHONY: build test clean all format
