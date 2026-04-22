#include "../include/cpu.h"
#include <iostream>

// Helper function to cleanly slice bits out of the 16-bit instruction
static uint16_t extractBits(uint16_t instr, int pos, int len) {
    uint16_t mask = (1 << len) - 1;
    return (instr >> pos) & mask;
}

void CPU::cycle() {
    m_Clock.tick();
    fetchNextInst();
    executeCurrentInst();
}

void CPU::fetchNextInst() {
    uint16_t pc = m_Registers[ISA::PC];

    uint16_t instruction = m_MemoryManager.read(pc);

    m_Registers[ISA::IR] = instruction;
    m_Registers[ISA::PC] = pc + 1;
}

void CPU::executeCurrentInst() {
    // 1. Grab the instruction we just fetched
    uint16_t instr = m_Registers[ISA::IR];

    // 2. Decode the Opcode (The top 4 bits: index 12, length 4)
    uint16_t opCodeVal = extractBits(instr, 12, 4);
    ISA::Opcode opcode = static_cast<ISA::Opcode>(opCodeVal);

    // 3. Execute based on the ISA definitions
    switch (opcode) {
        
        // --- MEMORY OPERATIONS ---
        case ISA::OP_LOAD: {
            // Format: [0101] [4 bit dest reg] [4 bit source reg] [0000]
            uint16_t destReg = extractBits(instr, 8, 4);
            uint16_t sourceReg = extractBits(instr, 4, 4); // Holds the memory address
            
            uint16_t memAddress = m_Registers[sourceReg];
            m_Registers[destReg] = m_MemoryManager.read(memAddress);
            break;
        }
        case ISA::OP_STORE: {
            // Format: [0110] [0000] [4 bit source reg (addr)] [4 bit target reg (data)]
            uint16_t sourceReg = extractBits(instr, 4, 4); // Holds the memory address
            uint16_t targetReg = extractBits(instr, 0, 4); // Holds the data to write
            
            uint16_t memAddress = m_Registers[sourceReg];
            uint16_t dataToStore = m_Registers[targetReg];
            
            m_MemoryManager.write(memAddress, dataToStore);
            break;
        }

        // --- REGISTER LOADING ---
        case ISA::OP_LDI: {
            // Format: [0001] [4 bit dest reg] [8 bit immediate]
            uint16_t destReg = extractBits(instr, 8, 4);
            uint16_t immVal  = extractBits(instr, 0, 8);
            m_Registers[destReg] = immVal;
            break;
        }

        // --- ALU OPERATIONS ---
        case ISA::OP_ADD:
        case ISA::OP_SUB: {
            // Format: [Opcode] [4 bit dest] [4 bit src1] [4 bit src2]
            uint16_t destReg = extractBits(instr, 8, 4);
            uint16_t src1Reg = extractBits(instr, 4, 4);
            uint16_t src2Reg = extractBits(instr, 0, 4);

            // Let the ALU object do the heavy lifting
            ALUResult res = m_ALU.execute(opCodeVal, m_Registers[src1Reg], m_Registers[src2Reg]);
            
            m_Registers[destReg] = res.value;
            m_Flags[ISA::ZERO_FLAG] = res.zero;
            // Add negative flag tracking here once it is added to the enum in isa.h
            break;
        }
        // --- DATA MOVEMENT ---
        case ISA::OP_MOV: {
            // Format: [0010] [4 bit dest] [4 bit src] [0000]
            uint16_t destReg = extractBits(instr, 8, 4);
            uint16_t srcReg  = extractBits(instr, 4, 4);
            m_Registers[destReg] = m_Registers[srcReg];
            break;
        }

        // --- CONTROL FLOW (BRANCHING) ---
        case ISA::OP_JMP: {
            // Format: [0111] [0000] [8 bit immediate address]
            uint16_t jumpAddress = extractBits(instr, 0, 8);
            m_Registers[ISA::PC] = jumpAddress;
            break;
        }
        case ISA::OP_JZ: {
            // Format: [1000] [1 flag bit] [000] [8 bit immediate address]
            uint16_t jumpAddress = extractBits(instr, 0, 8);
            
            // Only jump if the Zero Flag was set by a previous ALU operation!
            if (m_Flags[ISA::ZERO_FLAG] == true) {
                m_Registers[ISA::PC] = jumpAddress;
            }
            break;
        }
        // --- SYSTEM CONTROL ---
        case ISA::OP_HALT: {
            // Format: [1001] [0000 0000 0000]
            std::cout << "CPU EXECUTED HALT INSTRUCTION." << std::endl;
            // Trap the CPU in an infinite loop at the current PC to simulate stopping
            m_Registers[ISA::PC]--; 
            break;
        }
        case ISA::OP_NOOP: {
            // Do nothing, just let the PC advance
            break;
        }
        default: {
            std::cout << "HARDWARE FAULT: Unhandled Opcode 0x" << std::hex << opCodeVal << std::endl;
            // Trap the CPU to prevent it from executing garbage memory
            m_Registers[ISA::PC]--; 
            break;
        }
    }
}
void CPU::printState() {
    std::cout << "PC: 0x" << std::hex << m_Registers[ISA::PC] << std::dec
              << " | R1 (Counter): " << m_Registers[1] 
              << " | R2 (Dec): " << m_Registers[2] 
              << " | Z-Flag: " << m_Flags[ISA::ZERO_FLAG] << std::endl;
}