#include "../include/alu.h"
#include "../include/isa.h"

ALUResult ALU::execute(uint16_t opCode, uint16_t a, uint16_t b) {
	switch(opCode) {
		case ISA::Opcode::OP_ADD: {
			uint16_t res = a + b;
      return { res, res == 0, (res & 0x8000) != 0 };
		}
		default:
			return {0, true, false};
	}
}
