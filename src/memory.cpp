#include "../include/memory.h"
#include <cassert>
#include <iomanip>
#include <iostream>

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
void MemoryManager::memoryDump() {
  for (int i = 0x00; i <= ISA::MAX_MEM_ADDR; i += 4) {
    std::cout << std::hex << std::setfill('0') << "0x" << std::setw(2) << i
              << " " << std::setfill('0') << std::setw(4) << _Data[i] << " "
              << std::setfill('0') << std::setw(4) << _Data[i + 1] << " "
              << std::setfill('0') << std::setw(4) << _Data[i + 2] << " "
              << std::setfill('0') << std::setw(4) << _Data[i + 3] << std::endl;
  }
}
