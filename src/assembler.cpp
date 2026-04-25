#include "../include/isa.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

int main(int argc, char *argv[]) {

  // Map readable instruction names to their binary opcodes
  std::unordered_map<std::string, uint16_t> opcodes = {
      {"HALT", ISA::OP_HALT},   {"LDI", ISA::OP_LDI}, {"ADD", ISA::OP_ADD},
      {"PRINT", ISA::OP_PRINT}, {"SUB", ISA::OP_SUB}, {"JMP", ISA::OP_JMP},
      {"JZ", ISA::OP_JZ},       {"MOV", ISA::OP_MOV}, {"LOAD", ISA::OP_LOAD}, 
      {"STORE", ISA::OP_STORE}
  };
  // Map register names to their numeric index
  std::unordered_map<std::string, uint16_t> regs = {
      {"R0", ISA::Registers::R0},   {"R1", ISA::Registers::R1},
      {"R2", ISA::Registers::R2},   {"R3", ISA::Registers::R3},
      {"R4", ISA::Registers::R4},   {"R5", ISA::Registers::R5},
      {"R6", ISA::Registers::R6},   {"R7", ISA::Registers::R7},
      {"R8", ISA::Registers::R8},   {"R9", ISA::Registers::R9},
      {"R10", ISA::Registers::R10}, {"R11", ISA::Registers::R11},
      {"R12", ISA::Registers::R12}, {"R13", ISA::Registers::R13},
      {"R14", ISA::Registers::R14}, {"R15", ISA::Registers::R15},
  };

  if (argc < 2) {
    std::cerr << "Usage: assembler <filename.asm>" << std::endl;
    return 1;
  }

  std::ifstream infile(argv[1]);
  if (!infile) {
    std::cerr << "FATAL ERROR: Could not open '" << argv[1] << "'!" << std::endl;
    return 1;
  }

  // Structures for Two-Pass Assembly
  std::unordered_map<std::string, uint16_t> labels;
  std::vector<std::vector<std::string>> parsed_instructions;
  std::string line;
  uint16_t current_address = 0;

  // =========================================================
  // PASS 1: Parse lines, remove comments, and map labels
  // =========================================================
  while (std::getline(infile, line)) {
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> tokens;

    // Safely tokenize and strip comments (even if they have no spaces)
    while (ss >> token) {
      if (token.length() >= 2 && token.substr(0, 2) == "//") break;
      tokens.push_back(token);
    }

    // Skip entirely empty lines or lines that were just comments
    if (tokens.empty()) continue; 

    // Check if the first token is a label (ends with a colon ':')
    if (tokens[0].back() == ':') {
      std::string label_name = tokens[0].substr(0, tokens[0].size() - 1);
      labels[label_name] = current_address;
      
      // Remove the label from the tokens list for this line
      tokens.erase(tokens.begin()); 
      if (tokens.empty()) continue; // Move on if the line was ONLY a label
    }

    // Store the clean, valid instruction for Pass 2
    parsed_instructions.push_back(tokens);
    current_address++; // Each instruction takes up 1 slot in memory
  }

  // =========================================================
  // PASS 2: Generate Machine Code
  // =========================================================
  std::ofstream outfile("machine_code.bin", std::ios::binary);

  for (size_t i = 0; i < parsed_instructions.size(); i++) {
    const auto &tokens = parsed_instructions[i];
    uint16_t instr = 0x0000;
    
    // Safety check for unknown opcodes
    if (opcodes.find(tokens[0]) == opcodes.end()) {
      std::cerr << "Error: Unknown instruction '" << tokens[0] << "'" << std::endl;
      continue;
    }
    
    uint16_t op = opcodes[tokens[0]];

    // Wrapping in a try-catch to definitively prevent the stoi crash
    try {
      if (tokens[0] == "LDI") {
        uint16_t dest = regs[tokens[1]];
        uint16_t imm = std::stoi(tokens[2]);
        instr = (op << 12) | (dest << 8) | (imm & 0xFF);
        
      } else if (tokens[0] == "ADD" || tokens[0] == "SUB") {
        uint16_t dest = regs[tokens[1]];
        uint16_t src1 = regs[tokens[2]];
        uint16_t src2 = regs[tokens[3]];
        instr = (op << 12) | (dest << 8) | (src1 << 4) | src2;
      } else if (tokens[0] == "MOV" || tokens[0] == "LOAD") {
        // MOV and LOAD share the same format: [Opcode:4][Dest:4][Src:4][0000]
        uint16_t dest = regs[tokens[1]];
        uint16_t src = regs[tokens[2]];
        instr = (op << 12) | (dest << 8) | (src << 4);
        
      } else if (tokens[0] == "STORE") {
        // STORE format: [Opcode:4][0000][Src:4][Target:4]
        uint16_t src = regs[tokens[1]];
        uint16_t target = regs[tokens[2]];
        instr = (op << 12) | (src << 4) | target;  
      } else if (tokens[0] == "PRINT") {
        uint16_t src = regs[tokens[1]];
        instr = (op << 12) | (src << 8);
        
      } else if (tokens[0] == "JZ" || tokens[0] == "JMP") {
        uint16_t addr;
        // Check if the target is a mapped text label first
        if (labels.find(tokens[1]) != labels.end()) {
          addr = labels[tokens[1]];
        } else {
          // If not in the label map, assume it's a numeric literal
          addr = std::stoi(tokens[1]);
        }
        instr = (op << 12) | (addr & 0xFF);
        
      } else if (tokens[0] == "HALT") {
        instr = (op << 12);
      }

      outfile.write(reinterpret_cast<const char *>(&instr), sizeof(instr));

    } catch (const std::exception &e) {
        std::cerr << "Fatal Assembler Error: Could not parse numeric value in instruction '" << tokens[0] << "'." << std::endl;
        return 1;
    }
  }

  std::cout << "Assembler: Successfully compiled " << argv[1] << " to machine_code.bin" << std::endl;
  return 0;
}