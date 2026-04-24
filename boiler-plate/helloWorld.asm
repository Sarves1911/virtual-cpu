// hello_world.asm
// Prints "Hi!" using ASCII values

LDI R1 72    // Load 'H'
PRINT R1     // Output 'H'
LDI R1 105   // Load 'i'
PRINT R1     // Output 'i'
LDI R1 33    // Load '!'
PRINT R1     // Output '!'
LDI R1 10    // Load Newline (\n)
PRINT R1     // Output Newline
HALT