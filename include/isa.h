#pragma once
#include <cstdint>

// This ISA is a 16 bit architecture. There's not a lot of bits but thats ok
// General format
// [4 bit op code] [12 bit register / data]
namespace ISA {

// We are using WORD-ADDRESSING - but we only address up to 2^8 words!!!
static constexpr uint8_t MEM_WORD_SIZE = 0x10;
static constexpr uint16_t MAX_MEM_SIZE = 0x100;
static constexpr uint16_t MAX_MEM_ADDR = 0xFF;

enum Registers {
  // General purpose 0-15
  R0,
  R1,
  R2,
  R3,
  R4,
  R5,
  R6,
  R7,
  R8,
  R9,
  R10,
  R11,
  R12,
  R13,
  R14,
  R15,

  // Program Counter
  // The next instruction we fetch into the IR
  PC,

  // Instruction Register
  // The current instruction being executed atm
  IR,

  // Number of Register Counter
  // NOT A REGISTER!!!
  REG_COUNT,
};

// Now we could have a status register, but we going to bend the rules a little
// bit. Just define the flags enum here and then create an array of this enum
// size. We shall assume the remaining bits are padded off ..., as long as this
// length does not exceed the size of a register, we can assume we abstracted
// correctly.
//
// meaning -> Flag State array: [1], but hardware should look like [1000 0000
// 0000 0000]
enum Flags {
  ZERO_FLAG,

  // NOT A FLAG!!!
  FLAG_COUNT,
};

// Opcode is constrained to 4 bits - max 16 defined operation
enum Opcode {
  // No Operation
  // [0000 0000 0000 0000]
  OP_NOOP = 0x0,

  // Load an 8-bit number directly into a register
  // [0001] [4 bit dest reg] [8 bit immediate]
  OP_LDI = 0x1,

  // Move data from dest to target register
  // [0010] [4 bit dest reg] [4 bit source reg] [0000]
  OP_MOV = 0x2,

  // Add function: dest = source1 + source2
  // [0011] [4 bit dest reg] [4 bit source1 reg] [4 bit source2 reg]
  OP_ADD = 0x3,

  // Sub function: dest = source1 - source2
  // [0100] [4 bit dest reg] [4 bit source1 reg] [4 bit source2 reg]
  OP_SUB = 0x4,

  // Load data in source into memory[dest]
  // [0101] [4 bit dest reg] [4 bit source reg] [0000]
  OP_LOAD = 0x5,

  // Store data in memory[source] into target
  // [0110] [0000] [4 bit source reg] [4 bit target reg]
  OP_STORE = 0x6,

  // Jump the PC to the immediate address
  // [0111] [0000] [8 bit immediate]
  OP_JMP = 0x7,

// Jump conditionally
// [1000] [0000] [8 bit immediate address]
  OP_JZ = 0x8,

  //To stop the CPU entirely
  // [1001] [0000 0000 0000]
  OP_HALT = 0x9,

  //To print value in the register
  // [1010] [0000] [4 bit source reg] [0000]
  OP_PRINT = 0xA,  
  
};

}; // namespace ISA
