#pragma once
#include "alu.h"
#include "clock.h"
#include "isa.h"
#include "memory.h"
#include <array>
#include <cstdint>
#include <vector>

class CPU {
public:
  CPU(MemoryManager &mem, ALU &alu, Clock &clock)
      : m_MemoryManager(mem), m_ALU(alu), m_Clock(clock) {
    Reset();
  }
  void Reset() {
    m_Registers.fill(0);
    m_Flags.fill(0);
    m_Registers[ISA::PC] = 0;
    m_Registers[ISA::IR] = 0;
    m_MemoryManager.reset();
  }
  void cycle();
  void printState();
  std::array<uint16_t, ISA::REG_COUNT> &registers() { return m_Registers; }
  std::array<uint16_t, ISA::FLAG_COUNT> &flags() { return m_Flags; }

private:
  MemoryManager &m_MemoryManager;
  ALU &m_ALU;
  Clock &m_Clock;
  std::array<uint16_t, ISA::REG_COUNT> m_Registers;
  std::array<uint16_t, ISA::FLAG_COUNT> m_Flags;

  void fetchNextInst();
  void executeCurrentInst();
  void handle_OP_LOAD(uint16_t instr);
  void handle_OP_STORE(uint16_t instr);
  void handle_OP_LDI(uint16_t instr);
  void handle_OP_ADD(uint16_t instr);
  void handle_OP_SUB(uint16_t instr);
  void handle_OP_MOV(uint16_t instr);
  void handle_OP_JMP(uint16_t instr);
  void handle_OP_JZ(uint16_t instr);
  void handle_OP_HALT();
};
