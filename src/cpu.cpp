#include "../include/cpu.h"
#include <iomanip>
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
  uint16_t instr = m_Registers[ISA::IR];
  uint16_t opCodeVal = extractBits(instr, 12, 4);
  ISA::Opcode opcode = static_cast<ISA::Opcode>(opCodeVal);

  switch (opcode) {
  case ISA::OP_LOAD:
    handle_OP_LOAD(instr);
    break;
  case ISA::OP_STORE:
    handle_OP_STORE(instr);
    break;
  case ISA::OP_LDI:
    handle_OP_LDI(instr);
    break;
  case ISA::OP_ADD:
    handle_OP_ADD(instr);
    break;
  case ISA::OP_SUB:
    handle_OP_SUB(instr);
    break;
  case ISA::OP_MOV:
    handle_OP_MOV(instr);
    break;
  case ISA::OP_JMP:
    handle_OP_JMP(instr);
    break;
  case ISA::OP_JZ:
    handle_OP_JZ(instr);
    break;
  case ISA::OP_PRINT: {
    uint16_t srcReg = extractBits(instr, 8, 4);
    uint16_t val = m_Registers[srcReg];
    // Only print the character if it's in the printable range (32-126)
    if (val >= 32 && val <= 126) {
      std::cout << "stdout: " << val << " ('" << static_cast<char>(val)
                << "')\n";
    } else {
      std::cout << "stdout: " << val << " (ctrl char)\n";
    }
    break;
  }
  case ISA::OP_HALT:
    handle_OP_HALT();
    break;
  case ISA::OP_NOOP:
    break;
  default:
    std::cout << std::hex << std::setfill('0')
              << "HARDWARE FAULT: Unhandled Opcode 0x" << std::setw(4)
              << opCodeVal << std::endl;
    m_Registers[ISA::PC]--;
    break;
  }
}

bool CPU::checkHalt() { return m_Registers[ISA::IR] != (ISA::OP_HALT << 12); }

void CPU::handle_OP_LOAD(uint16_t instr) {
  uint16_t destReg = extractBits(instr, 8, 4);
  uint16_t sourceReg = extractBits(instr, 4, 4);
  uint16_t memAddress = m_Registers[sourceReg];
  m_Registers[destReg] = m_MemoryManager.read(memAddress);
}

void CPU::handle_OP_STORE(uint16_t instr) {
  uint16_t sourceReg = extractBits(instr, 4, 4);
  uint16_t targetReg = extractBits(instr, 0, 4);
  uint16_t memAddress = m_Registers[sourceReg];
  uint16_t dataToStore = m_Registers[targetReg];
  m_MemoryManager.write(memAddress, dataToStore);
}

void CPU::handle_OP_LDI(uint16_t instr) {
  uint16_t destReg = extractBits(instr, 8, 4);
  uint16_t immVal = extractBits(instr, 0, 8);
  m_Registers[destReg] = immVal;
}

void CPU::handle_OP_ADD(uint16_t instr) {
  uint16_t destReg = extractBits(instr, 8, 4);
  uint16_t src1Reg = extractBits(instr, 4, 4);
  uint16_t src2Reg = extractBits(instr, 0, 4);
  ALUResult res =
      m_ALU.execute(ISA::OP_ADD, m_Registers[src1Reg], m_Registers[src2Reg]);
  m_Registers[destReg] = res.value;
  m_Flags[ISA::ZERO_FLAG] = res.zero;
}

void CPU::handle_OP_SUB(uint16_t instr) {
  uint16_t destReg = extractBits(instr, 8, 4);
  uint16_t src1Reg = extractBits(instr, 4, 4);
  uint16_t src2Reg = extractBits(instr, 0, 4);
  ALUResult res =
      m_ALU.execute(ISA::OP_SUB, m_Registers[src1Reg], m_Registers[src2Reg]);
  m_Registers[destReg] = res.value;
  m_Flags[ISA::ZERO_FLAG] = res.zero;
}

void CPU::handle_OP_MOV(uint16_t instr) {
  uint16_t destReg = extractBits(instr, 8, 4);
  uint16_t srcReg = extractBits(instr, 4, 4);
  m_Registers[destReg] = m_Registers[srcReg];
}

void CPU::handle_OP_JMP(uint16_t instr) {
  uint16_t jumpAddress = extractBits(instr, 0, 8);
  m_Registers[ISA::PC] = jumpAddress;
}

void CPU::handle_OP_JZ(uint16_t instr) {
  uint16_t jumpAddress = extractBits(instr, 0, 8);
  if (m_Flags[ISA::ZERO_FLAG] == true) {
    m_Registers[ISA::PC] = jumpAddress;
  }
}

void CPU::handle_OP_HALT() {
  std::cout << "\nCPU EXECUTED HALT INSTRUCTION.\n" << std::endl;
  m_Registers[ISA::PC]--;
}

const std::string _print_line = "===============================";
void print_line() { std::cout << _print_line << std::endl; }

void print_section_line() {
  std::cout << _print_line << _print_line << std::endl;
}

void CPU::memoryDump() {
  std::cout << std::endl;
  print_section_line();
  std::cout << "Memory Dump" << std::endl;
  m_MemoryManager.memoryDump();
  print_section_line();
  std::cout << std::endl;
}

void CPU::printState() {
  std::cout << std::endl;
  print_section_line();
  this->printClockTime();
  print_section_line();
  this->printSpecialRegisters();
  print_section_line();
  this->printFlags();
  print_section_line();
  this->printGeneralRegisters();
  print_section_line();
  std::cout << std::endl;
}

void CPU::printClockTime() {
  std::cout << "Clock Step" << std::endl;
  std::cout << this->m_Clock.getTime() << std::endl;
}

void CPU::printSpecialRegisters() {
  std::cout << "Special Registers" << std::endl;
  std::cout << std::hex << std::setfill('0') << "PC: 0x" << std::setw(4)
            << m_Registers[ISA::PC] << " | IR: 0x" << std::setw(4)
            << m_Registers[ISA::IR] << std::dec << std::endl;
}

void CPU::printFlags() {
  std::cout << "Flags Status" << std::endl;
  std::cout << "Z-Flag: " << m_Flags[ISA::ZERO_FLAG] << std::endl;
}

void CPU::printGeneralRegisters() {
  std::cout << "General Registers" << std::endl;
  const uint REGISTERS_PER_LINE = 4;
  for (int i = ISA::R0; i <= ISA::R15; i++) {
    if (i > 0 && i % REGISTERS_PER_LINE == 0) {
      std::cout << std::endl;
    }
    std::cout << std::hex << std::setfill('0') << "R" << i << ": 0x"
              << std::setw(4) << m_Registers[i] << " ";
  }
  std::cout << std::dec << std::endl;
}
