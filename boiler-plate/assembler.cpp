#include "isa.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

int main(int argc, char* argv[]) {

    // Map readable instruction names to their binary opcodes defined in isa.h
    std::unordered_map<std::string, uint16_t> opcodes = {
        {"HALT", ISA::OP_NOOP},
        {"LDI",  ISA::OP_LDI},
        {"ADD",  ISA::OP_ADD}
    };

    // Map register names to their numeric index (R1=1, R2=2, R3=3)
    std::unordered_map<std::string, uint16_t> regs = {
        {"R1", 1}, {"R2", 2}, {"R3", 3}
    };

    // Require one argument: the .asm filename
    if (argc < 2) {
        std::cerr << "Usage: assembler <filename.asm>" << std::endl;
        return 1;
    }

    // Open the .asm source file passed in via command line (e.g. fibonacci.asm)
    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr << "FATAL ERROR: Could not open '" << argv[1] << "'!" << std::endl;
        return 1; // Kill the program
    }

    // Output file: always writes to machine_code.bin in binary mode
    std::ofstream outfile("machine_code.bin", std::ios::binary);
    std::string line;

    // Read the .asm file one line at a time
    while (std::getline(infile, line)) {

        if (line.empty() || line[0] == '/')
            continue;// Skip empty / comments

        // Tokenize the line by whitespace into individual parts
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> tokens;
        while (ss >> token) {
            // Stop collecting tokens if we hit an inline comment
            if (token == "//") break;
            tokens.push_back(token);
        }

        // Start with a blank 16-bit instruction
        uint16_t instr = 0x0000;
        uint16_t op = opcodes[tokens[0]]; 

        if (tokens[0] == "LDI") {
            // [Opcode:4][Dest:4][Immediate:8]
            uint16_t dest = regs[tokens[1]];
            uint16_t imm  = std::stoi(tokens[2]);
            instr = (op << 12) | (dest << 8) | (imm & 0xFF);

        } else if (tokens[0] == "ADD") {
            // [Opcode:4][Dest:4][Src1:4][Src2:4]
            uint16_t dest = regs[tokens[1]];
            uint16_t src1 = regs[tokens[2]];
            uint16_t src2 = regs[tokens[3]];
            instr = (op << 12) | (dest << 8) | (src1 << 4) | (src2);

        } else if (tokens[0] == "HALT") {
            // Halt: encodes as all zeros
            instr = 0x0000;
        }

        // Write the 16-bit instruction to the binary file
        outfile.write(reinterpret_cast<const char*>(&instr), sizeof(instr));
    }

    std::cout << "Assembler: Successfully compiled " << argv[1]
              << " to machine_code.bin" << std::endl;
    return 0;
}