#include "../include/cpu.h"

#include <iostream>

void CPU::cycle() {
    fetchNextInst();
    executeCurrentInst();
}

void CPU::fetchNextInst() {
    uint16_t pc = m_Registers[ISA::PC];

    uint16_t instruction = m_MemoryManager.read(pc);

    m_Registers[ISA::IR] = instruction;
    m_Registers[ISA::PC] = pc + 1;
}

// TODO: implement
void CPU::executeCurrentInst(){
    
}