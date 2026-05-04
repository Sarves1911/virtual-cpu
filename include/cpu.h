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
    m_Registers[ISA::SP] = ISA::MAX_MEM_ADDR; // reset stack pointer to max address
    m_MemoryManager.reset();
  }
  void cycle();
  void printState();
  void printClockTime();
  void printFlags();
  void printSpecialRegisters();
  void printGeneralRegisters();
  void memoryDump();

  bool checkHalt();
  std::array<uint16_t, ISA::REG_COUNT> &registers() { return m_Registers; }
  std::array<uint16_t, ISA::FLAG_COUNT> &flags() { return m_Flags; }

  void push(uint16_t value);
  uint16_t pop();

  void setShowStack(bool s) {m_ShowStack = s; }

private:
  MemoryManager &m_MemoryManager;
  ALU &m_ALU;
  Clock &m_Clock;
  std::array<uint16_t, ISA::REG_COUNT> m_Registers;
  std::array<uint16_t, ISA::FLAG_COUNT> m_Flags;
  bool m_ShowStack = false;
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
  void handle_OP_PUSH(uint16_t instr);
  void handle_OP_POP(uint16_t instr);
  void handle_OP_CALL(uint16_t instr);
  void handle_OP_RET();
  void handle_OP_HALT();
};
