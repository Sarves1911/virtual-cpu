#pragma once
#include "isa.h"
#include "alu.h"
#include "clock.h"
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
  }
  void cycle();

private:
  MemoryManager &m_MemoryManager;
  ALU &m_ALU;
  Clock &m_Clock;
  std::array<uint16_t, ISA::REG_COUNT> m_Registers;
  std::array<uint16_t, ISA::FLAG_COUNT> m_Flags;
  
  void fetchNextInst();
  void executeCurrentInst();
};
