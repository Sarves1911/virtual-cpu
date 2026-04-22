#include "../include/cpu.h"
#include <cstdint>
#include <fstream>
#include <iostream>

uint16_t memory[4096] = {0};
uint16_t registers[16] = {0};
uint16_t PC = 0;
bool isHalted = false;

// Helper to slice bits
uint16_t extractBits(uint16_t instr, int pos, int len) {
  uint16_t mask = (1 << len) - 1;
  return (instr >> pos) & mask;
}

int main() {
  // 1. Load the machine code into memory
  std::ifstream infile("machine_code.bin", std::ios::binary);
  if (!infile) {
    std::cerr << "Error: Run the assembler first!" << std::endl;
    return 1;
  }

  int i = 0;
  while (infile.read(reinterpret_cast<char *>(&memory[i]), sizeof(uint16_t))) {
    i++;
  }
  std::cout << "Emulator: Loaded " << i << " instructions into memory.\n"
            << std::endl;

  // 2. The Master Clock Loop
  std::cout << "--- CPU EXECUTION START ---" << std::endl;
  while (!isHalted) {
    // FETCH
    uint16_t instr = memory[PC];
    PC++;

    // DECODE
    uint16_t opcode = extractBits(instr, 12, 4);
    uint16_t dest = extractBits(instr, 8, 4);

    // EXECUTE
    switch (opcode) {
    case OP_LDI: {
      uint16_t imm = extractBits(instr, 0, 8);
      registers[dest] = imm;
      break;
    }
    case OP_ADD: {
      uint16_t src1 = extractBits(instr, 4, 4);
      uint16_t src2 = extractBits(instr, 0, 4);
      registers[dest] = registers[src1] + registers[src2];
      break;
    }
    case OP_HALT: {
      isHalted = true;
      break;
    }
    default:
      isHalted = true;
      break;
    }
  }
  std::cout << "--- CPU EXECUTION HALTED ---\n" << std::endl;

  // 3. Dump Core (Prove it worked)
  std::cout << "[Core Dump]" << std::endl;
  std::cout << "R1: " << registers[1] << std::endl;
  std::cout << "R2: " << registers[2] << std::endl;
  std::cout << "R3: " << registers[3] << " 67 hehe" << std::endl;

  return 0;
}