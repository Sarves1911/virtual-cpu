#pragma once
#include "ISA.h"
#include "memory.h"
#include "alu.h"
#include <array>
#include <cstdint>
#include <vector>

class CPU {
	public:
		CPU(MemoryManager& mem, ALU& alu):
			m_MemoryManager(mem), 
      m_ALU(alu) {
				Reset();
			}
		void Reset() {
			m_Registers.fill(0);
			m_Flags.fill(0);
		}
		void fetchNextInst();
		void executeCurrentInst();

	private:
		MemoryManager& m_MemoryManager;
		ALU& m_ALU;
		std::array<uint16_t, ISA::Registers::REG_COUNT> m_Registers;
		std::array<uint16_t, ISA::Flags::FLAG_COUNT> m_Flags;
};
