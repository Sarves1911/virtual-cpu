// ============================================================
// program.asm — Fibonacci Sequence Demo
// ============================================================
// This file is written in OUR custom assembly language.
// It is NOT C++ — it is read by assembler.cpp, which translates
// each line into a 16-bit binary instruction and saves it to
// machine_code.bin. Then emulator.cpp loads and runs that file.
//
// The Fibonacci sequence: 0, 1, 1, 2, 3, 5, 8, 13, 21 ...
// Each number is the sum of the two before it.
//
// Because our assembler only supports LDI, ADD, and HALT,
// and only knows R1, R2, R3 — we compute one step at a time:
//
//   Step 0: R1 = 0         (1st Fibonacci number)
//   Step 1: R2 = 1         (2nd Fibonacci number)
//   Step 2: R3 = R1 + R2   (3rd Fibonacci number = 0 + 1 = 1)
//
// After HALT, the emulator prints a core dump showing R1, R2, R3.
// You will see: R1=0, R2=1, R3=1
// ============================================================

// --- LOAD INITIAL VALUES ---

LDI R1 0
// LDI = "Load Immediate" — put a hardcoded number directly into a register.
// R1 is the destination register.
// 0 is the value being loaded.
// This represents F(0), the first Fibonacci number.
// After this line: R1 = 0

LDI R2 1
// Same instruction, different register and value.
// R2 is the destination register.
// 1 is the value being loaded.
// This represents F(1), the second Fibonacci number.
// After this line: R2 = 1

// --- COMPUTE NEXT FIBONACCI NUMBER ---

ADD R3 R1 R2
// ADD = add two registers together and store the result in a third.
// R3 is the destination (where the result goes).
// R1 is the first number to add (currently 0).
// R2 is the second number to add (currently 1).
// This computes F(2) = F(0) + F(1) = 0 + 1 = 1.
// After this line: R3 = 1

// --- STOP THE CPU ---

HALT
// Tell the CPU to stop executing instructions.
// Without this, the emulator would keep reading garbage memory values
// and try to execute them as if they were real instructions.
// The assembler translates HALT into 0x0000 (all zeros = OP_NOOP),
// which the emulator treats as a stop signal.

// ============================================================
// EXPECTED OUTPUT (from emulator.cpp's core dump):
//   R1: 0      ← F(0), the starting value we loaded
//   R2: 1      ← F(1), the second starting value we loaded
//   R3: 1      ← F(2) = F(0) + F(1), computed by ADD
//
// TO RUN THIS:
//   1. Compile and run assembler.cpp  → produces machine_code.bin
//   2. Compile and run emulator.cpp   → loads and executes machine_code.bin
// ============================================================