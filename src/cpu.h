#pragma once
#include "ISA.h"
#include "memory.h"
#include <array>
#include <cstdint>
#include <vector>

class CPU {
	public:
		CPU(MemoryManager& mem) {
			_MemoryManager = mem;
		}
		void fetchNextInst();
		void executeCurrentInst();
	private:
		MemoryManager _MemoryManager;
		std::array<uint16_t, ISA::Registers::REG_COUNT> _Registers;
		std::array<uint16_t, ISA::Flags::FLAG_COUNT> _Flags;
};
