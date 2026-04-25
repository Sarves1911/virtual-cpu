#pragma once
#include "isa.h"
#include <array>

class MemoryManager {
public:
  uint16_t read(uint16_t addr);
  void write(uint16_t addr, uint16_t value);
  void reset();

private:
  std::array<uint16_t, ISA::MAX_MEM_SIZE> _Data;

  // This is needed because we decided that MAX_MEM_SIZE was gonna be 2^8
  // instead of a full 2^16 for now. This will slow down read / write but I
  // doubt we'll notice nor care.
  void ValidateAddress(uint16_t addr) const;
};
