#include <cassert>
#include <stdio.h>
#include "micro_test_framework.h"
#include "../include/alu.h"
#include "../include/isa.h"
class TestALUSuite: public TestSuite {
	
	public:	
		void runTests() {
			executeTest("testAdd_Basic", [this]{this->testAdd_Basic(); });
		}
		void onMount() {
			std::cout << "\n[SUITE] Test ALU Begin\n";
		}
		void onDismount() {
			std::cout << "\n[SUITE] Test ALU End\n";
		}
	private:
		void testAdd_Basic() {
			ALU alu;	
			ALUResult result = alu.execute(ISA::Opcode::OP_ADD, 0, 67);
			test_assert(result.value == 67);
		};
};

