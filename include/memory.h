#pragma
#include "isa.h"
#include <array>
#include <cassert>

class MemoryManager {
public:
  uint16_t read(uint16_t addr) {
    ValidateAddress(addr);
    return _Data[addr];
  };
  void write(uint16_t addr, uint16_t value) {
    ValidateAddress(addr);
    _Data[addr] = value;
  }

private:
  std::array<uint16_t, ISA::MAX_MEM_SIZE> _Data;

  // This is needed because we decided that MAX_MEM_SIZE was gonna be 2^8
  // instead of a full 2^16 for now. This will slow down read / write but I
  // doubt we'll notice nor care.
  void ValidateAddress(uint16_t addr) const {
    assert(addr >= 0 && addr < ISA::MAX_MEM_SIZE &&
           "Memory Access Violation: Address out of bounds!");
  };
};
