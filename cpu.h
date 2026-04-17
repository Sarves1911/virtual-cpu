#pragma once
#include <cstdint>

// Opcodes defined in the doc
enum Opcode
{
    OP_HALT = 0x0,
    OP_LDI = 0x1,
    OP_MOV = 0x2,
    OP_ADD = 0x3,
    OP_SUB = 0x4,
    OP_LOAD = 0x5,
    OP_STORE = 0x6,
    OP_JMP = 0x7,
    OP_JZ = 0x8
};