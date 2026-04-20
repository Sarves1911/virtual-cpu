#include "../include/alu.h"
#include "../include/isa.h"
#include "micro_test_framework.h"
#include <cassert>
#include <stdio.h>
class TestALUSuite : public TestSuite {

public:
  void runTests() {
    executeTest("testAdd_Basic", [this] { this->testAdd_Basic(); });
    executeTest("testSub_Basic", [this] { this->testSub_Basic(); });
  }
  void onMount() { std::cout << "\n[SUITE] Test ALU Begin\n"; }
  void onDismount() { std::cout << "\n[SUITE] Test ALU End\n"; }

private:
  void testAdd_Basic() {
    ALU alu;
    ALUResult result = alu.execute(ISA::Opcode::OP_ADD, 0, 67);
    test_assert(result.value == 67);
  };

  void testSub_Basic() {
    ALU alu;
    ALUResult result = alu.execute(ISA::OP_SUB, 42, 10);
    test_assert(result.value == 32);
  }
};
