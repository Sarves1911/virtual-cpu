#include "../include/memory.h"
#include <cassert>

uint16_t MemoryManager::read(uint16_t addr) {
  ValidateAddress(addr);
  return _Data[addr];
};
void MemoryManager::write(uint16_t addr, uint16_t value) {
  ValidateAddress(addr);
  _Data[addr] = value;
}
void MemoryManager::reset() { _Data.fill(0); }
void MemoryManager::ValidateAddress(uint16_t addr) const {
  assert(addr >= 0 && addr < ISA::MAX_MEM_SIZE &&
         "Memory Access Violation: Address out of bounds!");
};
