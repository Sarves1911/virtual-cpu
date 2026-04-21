#include "../include/memory.h"
#include "../include/alu.h"
#include "../include/clock.h"
#include "../include/cpu.h"
#include <iostream>

int main() {
    // 1. Boot up the hardware
    MemoryManager ram;
    ALU alu;
    Clock systemClock;
    CPU cpu(ram, alu, systemClock);

    // 2. Inject the Countdown Loop directly into RAM
    // 0x00: LDI R1, 3      (Set Counter to 3)
    ram.write(0x00, 0x1103); 
    
    // 0x01: LDI R2, 1      (Set Decrementer to 1)
    ram.write(0x01, 0x1201); 
    
    // 0x02: SUB R1, R1, R2 (R1 = R1 - 1. Updates Zero Flag!)
    ram.write(0x02, 0x4112); 
    
    // 0x03: JZ 0x05        (If Zero Flag == 1, break loop and jump to HALT)
    ram.write(0x03, 0x8005); 
    
    // 0x04: JMP 0x02       (Else, loop back up to the SUB instruction)
    ram.write(0x04, 0x7002); 
    
    // 0x05: HALT           (Stop execution)
    ram.write(0x05, 0x9000); 

    // 3. Run the Clock Loop
    std::cout << "--- CPU BOOT SEQUENCE INITIATED ---\n";
    
    // We run for a max of 20 cycles just in case we accidentally created an infinite loop
    for (int i = 0; i < 20; i++) {
        // Read the instruction we are about to execute just to see if it's HALT
        // uint16_t currentPC = ram.read(cpu.m_Registers[ISA::PC]); // Note: You might need a getter for PC if it's strictly private
        
        cpu.cycle();
        cpu.printState();
        
        // Break the clock loop if the CPU halted itself (trapped at the same PC)
        // Or you can just let it run out its 20 cycles.
    }

    std::cout << "--- CPU SHUTDOWN ---\n";
    return 0;
}