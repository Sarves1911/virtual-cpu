#include "../include/isa.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

// Helper to completely strip comments off the end of a line
std::string cleanLine(std::string line) {
  size_t commentPos = line.find("//");
  if (commentPos != std::string::npos) {
    line = line.substr(0, commentPos);
  }
  return line;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: assembler <filename.asm>" << std::endl;
    return 1;
  }

  std::unordered_map<std::string, uint16_t> opcodes = {
      {"NOOP", ISA::OP_NOOP},   {"LDI", ISA::OP_LDI},    {"MOV", ISA::OP_MOV},
      {"ADD", ISA::OP_ADD},     {"SUB", ISA::OP_SUB},    {"LOAD", ISA::OP_LOAD},
      {"STORE", ISA::OP_STORE}, {"JMP", ISA::OP_JMP},    {"JZ", ISA::OP_JZ},
      {"HALT", ISA::OP_HALT},   {"PRINT", ISA::OP_PRINT}};

  std::unordered_map<std::string, uint16_t> regs;
  for (int i = 0; i < 16; i++)
    regs["R" + std::to_string(i)] = i;

  std::unordered_map<std::string, uint16_t> labels;
  std::vector<std::vector<std::string>> parsedLines;

  std::ifstream infile(argv[1]);
  if (!infile) {
    std::cerr << "FATAL ERROR: Could not open '" << argv[1] << "'!\n";
    return 1;
  }

  std::string line;
  uint16_t addressCounter = 0;

  // --- PASS 1: Find Labels & Clean Data ---
  while (std::getline(infile, line)) {
    line = cleanLine(line); // Safely remove comments
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> tokens;

    while (ss >> token)
      tokens.push_back(token);
    if (tokens.empty())
      continue; // Skip blank lines

    // If the token ends with a colon, save its memory address
    if (tokens[0].back() == ':') {
      std::string labelName = tokens[0].substr(0, tokens[0].size() - 1);
      labels[labelName] = addressCounter;
      tokens.erase(tokens.begin()); // Remove label so the instruction remains
    }
    // If there's still an instruction on this line, save it for Pass 2
    if (!tokens.empty()) {
      parsedLines.push_back(tokens);
      addressCounter++;
    }
  }

  // --- PASS 2: Generate Machine Code ---
  std::ofstream outfile("machine_code.bin", std::ios::binary);
  uint16_t instructionsWritten = 0;

  for (const auto &tokens : parsedLines) {
    uint16_t instr = 0x0000;
    uint16_t op = opcodes[tokens[0]];

    if (tokens[0] == "LDI") {
      uint16_t dest = regs[tokens[1]];
      uint16_t imm = std::stoi(tokens[2]);
      instr = (op << 12) | (dest << 8) | (imm & 0xFF);
    } else if (tokens[0] == "ADD" || tokens[0] == "SUB") {
      uint16_t dest = regs[tokens[1]];
      uint16_t src1 = regs[tokens[2]];
      uint16_t src2 = regs[tokens[3]];
      instr = (op << 12) | (dest << 8) | (src1 << 4) | src2;
    } else if (tokens[0] == "MOV") {
      uint16_t dest = regs[tokens[1]];
      uint16_t src = regs[tokens[2]];
      instr = (op << 12) | (dest << 8) | (src << 4);
    } else if (tokens[0] == "PRINT") {
      uint16_t src = regs[tokens[1]];
      instr = (op << 12) | (src << 8);
    } else if (tokens[0] == "JMP" || tokens[0] == "JZ") {
      uint16_t addr;
      // Check if the jump target is a Label (like "LOOP_START") or a hardcoded
      // number
      if (labels.count(tokens[1])) {
        addr = labels[tokens[1]];
      } else {
        addr = std::stoi(tokens[1]);
      }
      instr = (op << 12) | (addr & 0xFF);
    } else if (tokens[0] == "HALT" || tokens[0] == "NOOP") {
      instr = (op << 12);
    }

    outfile.write(reinterpret_cast<const char *>(&instr), sizeof(instr));
    instructionsWritten++;
  }

  std::cout << "Assembler: Successfully compiled " << argv[1] << " ("
            << instructionsWritten << " instructions) to machine_code.bin\n";
  return 0;
}
