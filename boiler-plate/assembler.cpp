#include "isa.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
  std::unordered_map<std::string, uint16_t> opcodes = {
      {"HALT", ISA::OP_NOOP}, {"LDI", ISA::OP_LDI}, {"ADD", ISA::OP_ADD}};
  std::unordered_map<std::string, uint16_t> regs = {
      {"R1", 1}, {"R2", 2}, {"R3", 3}};

  std::ifstream infile("program.asm");
  if (!infile) {
    std::cerr << "FATAL ERROR: Could not find or open 'program.asm' in this "
                 "directory!"
              << std::endl;
    return 1; // Kill the program
  }
  std::ofstream outfile("machine_code.bin", std::ios::binary);
  std::string line;

  while (std::getline(infile, line)) {
    if (line.empty() || line[0] == '/')
      continue; // Skip empty/comments

    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> tokens;
    while (ss >> token)
      tokens.push_back(token);

    uint16_t instr = 0x0000;
    uint16_t op = opcodes[tokens[0]];

    if (tokens[0] == "LDI") {
      // [Opcode:4][Dest:4][Immediate:8]
      uint16_t dest = regs[tokens[1]];
      uint16_t imm = std::stoi(tokens[2]);
      instr = (op << 12) | (dest << 8) | (imm & 0xFF);
    } else if (tokens[0] == "ADD") {
      // [Opcode:4][Dest:4][Src1:4][Src2:4]
      uint16_t dest = regs[tokens[1]];
      uint16_t src1 = regs[tokens[2]];
      uint16_t src2 = regs[tokens[3]];
      instr = (op << 12) | (dest << 8) | (src1 << 4) | (src2);
    } else if (tokens[0] == "HALT") {
      instr = 0x0000;
    }

    // Write the 16-bit instruction to binary file
    outfile.write(reinterpret_cast<const char *>(&instr), sizeof(instr));
  }

  std::cout
      << "Assembler: Successfully compiled program.asm to machine_code.bin"
      << std::endl;
  return 0;
}
