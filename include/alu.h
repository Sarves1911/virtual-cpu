#pragma once
#include <cstdint>

struct ALUResult {
	uint16_t value;
	bool zero;
	bool negative;
};

class ALU {
	public: 
		ALUResult execute(uint16_t opCode, uint16_t a, uint16_t b);
	private:
		// Wrapper around operations, seem silly but it's kept for extendability 
		uint16_t add(uint16_t a, uint16_t b) {
			return a + b;
		}

		uint16_t sub(uint16_t a, uint16_t b) {
			return a - b;
		}


};
