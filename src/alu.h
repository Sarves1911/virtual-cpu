#pragma once
#include <cstdint>

class ALU {
	
	public:
		// Wrapper around operations, seem silly but it's kept for extendability 
		uint16_t add(uint16_t a, uint16_t b) {
			return a + b;
		}

		uint16_t sub(uint16_t a, uint16_t b) {
			return a - b;
		}
};
