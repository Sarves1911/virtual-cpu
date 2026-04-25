CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I include
BUILD_DIR = build

CPU_TARGET = $(BUILD_DIR)/virtual-cpu
ASM_TARGET = $(BUILD_DIR)/assembler

# CPU needs these files (but NOT assembler.cpp)
CPU_SRC = src/alu.cpp src/clock.cpp src/cpu.cpp src/main.cpp src/memory.cpp

# Assembler only needs its own file
ASM_SRC = src/assembler.cpp

all: prepare $(CPU_TARGET) $(ASM_TARGET)

prepare:
	@mkdir -p $(BUILD_DIR)

$(CPU_TARGET): $(CPU_SRC)
	$(CXX) $(CXXFLAGS) -o $(CPU_TARGET) $(CPU_SRC)

$(ASM_TARGET): $(ASM_SRC)
	$(CXX) $(CXXFLAGS) -o $(ASM_TARGET) $(ASM_SRC)

clean:
	rm -rf $(BUILD_DIR)
	rm -f machine_code.bin
