#include "../include/alu.h"
#include "../include/clock.h"
#include "../include/cpu.h"
#include "../include/isa.h"
#include "../include/memory.h"
#include "micro_test_framework.h"

static uint16_t makeInst(uint16_t opcode, uint16_t dest, uint16_t src1,
                         uint16_t src2) {
  return (opcode << 12) | (dest << 8) | (src1 << 4) | src2;
}

static uint16_t makeLDI(uint16_t opcode, uint16_t dest, uint16_t imm) {
  return (opcode << 12) | (dest << 8) | imm;
}

static uint16_t makeJMP(uint16_t opcode, uint16_t addr) {
  return (opcode << 12) | addr;
}

class TestCPUSuite : public TestSuite {
public:
  void runTests() {
    executeTest("TestHandle_OP_LDI", [this] { this->testHandle_OP_LDI(); });
    executeTest("TestHandle_OP_MOV", [this] { this->testHandle_OP_MOV(); });
    executeTest("TestHandle_OP_ADD", [this] { this->testHandle_OP_ADD(); });
    executeTest("TestHandle_OP_SUB", [this] { this->testHandle_OP_SUB(); });
    executeTest("TestHandle_OP_LOAD", [this] { this->testHandle_OP_LOAD(); });
    executeTest("TestHandle_OP_STORE", [this] { this->testHandle_OP_STORE(); });
    executeTest("TestHandle_OP_JMP", [this] { this->testHandle_OP_JMP(); });
    executeTest("TestHandle_OP_JZ_Taken",
                [this] { this->testHandle_OP_JZ_Taken(); });
    executeTest("TestHandle_OP_JZ_NotTaken",
                [this] { this->testHandle_OP_JZ_NotTaken(); });
  }

  void onMount() { std::cout << "\n[SUITE] Test CPU Begin\n"; }
  void onDismount() { std::cout << "[SUITE] Test CPU End\n"; }

private:
  ALU m_ALU;
  Clock m_Clock;
  MemoryManager m_Memory;
  CPU m_CPU{m_Memory, m_ALU, m_Clock};

  void testHandle_OP_LDI() {
    m_CPU.Reset();
    m_Memory.write(0, makeLDI(ISA::OP_LDI, ISA::R1, 0x42));
    m_CPU.cycle();
    test_assert(m_CPU.registers()[ISA::R1] == 0x42);
  }

  void testHandle_OP_MOV() {
    m_CPU.Reset();
    m_CPU.registers()[ISA::R2] = 0xDEAD;
    m_Memory.write(0, makeInst(ISA::OP_MOV, ISA::R1, ISA::R2, ISA::R0));
    m_CPU.cycle();
    test_assert(m_CPU.registers()[ISA::R1] == 0xDEAD);
  }

  void testHandle_OP_ADD() {
    m_CPU.Reset();
    m_CPU.registers()[ISA::R1] = 10;
    m_CPU.registers()[ISA::R2] = 32;
    m_Memory.write(0, makeInst(ISA::OP_ADD, ISA::R3, ISA::R1, ISA::R2));
    m_CPU.cycle();
    test_assert(m_CPU.registers()[ISA::R3] == 42);
  }

  void testHandle_OP_SUB() {
    m_CPU.Reset();
    m_CPU.registers()[ISA::R1] = 100;
    m_CPU.registers()[ISA::R2] = 58;
    m_Memory.write(0, makeInst(ISA::OP_SUB, ISA::R3, ISA::R1, ISA::R2));
    m_CPU.cycle();
    test_assert(m_CPU.registers()[ISA::R3] == 42);
  }

  void testHandle_OP_LOAD() {
    m_CPU.Reset();
    m_Memory.write(0x10, 0xCAFE);
    m_CPU.registers()[ISA::R1] = 0x10;
    m_Memory.write(0, makeInst(ISA::OP_LOAD, ISA::R2, ISA::R1, ISA::R0));
    m_CPU.cycle();
    test_assert(m_CPU.registers()[ISA::R2] == 0xCAFE);
  }

  void testHandle_OP_STORE() {
    m_CPU.Reset();
    m_CPU.registers()[ISA::R1] = 0x20;
    m_CPU.registers()[ISA::R2] = 0xBEEF;
    m_Memory.write(0, makeInst(ISA::OP_STORE, ISA::R0, ISA::R1, ISA::R2));
    m_CPU.cycle();
    test_assert(m_Memory.read(0x20) == 0xBEEF);
  }

  void testHandle_OP_JMP() {
    m_CPU.Reset();
    m_Memory.write(0, makeJMP(ISA::OP_JMP, 0x50));
    m_CPU.cycle();
    test_assert(m_CPU.registers()[ISA::PC] == 0x50);
  }

  void testHandle_OP_JZ_Taken() {
    m_CPU.Reset();
    m_CPU.flags()[ISA::ZERO_FLAG] = 1;
    m_Memory.write(0, makeJMP(ISA::OP_JZ, 0x30));
    m_CPU.cycle();
    test_assert(m_CPU.registers()[ISA::PC] == 0x30);
  }

  void testHandle_OP_JZ_NotTaken() {
    m_CPU.Reset();
    m_CPU.flags()[ISA::ZERO_FLAG] = 0;
    m_Memory.write(0, makeJMP(ISA::OP_JZ, 0x30));
    m_Memory.write(1, 0xFFFF);
    m_CPU.cycle();
    test_assert(m_CPU.registers()[ISA::PC] == 1);
  }
};
