#include "../include/alu.h"
#include "../include/isa.h"
#include <iostream>

ALUResult ALU::execute(uint16_t opCode, uint16_t a, uint16_t b) {
	switch(opCode) {
		case ISA::Opcode::OP_ADD: {
			uint16_t res = a + b;
      return { res, res == 0, res > 0 };
		}
		case ISA::Opcode::OP_SUB: {
			uint16_t res = a - b;
			return { res, res == 0, res > 0 };
		}
		//When there isn't a matching OpCode, which should never be the case - assume noop													
		default:
			std::cout << "ALU: NON MATCHING OPCODE, HOW DID YOU GET HERE\n";
			return {0, true, false};
	}
}
