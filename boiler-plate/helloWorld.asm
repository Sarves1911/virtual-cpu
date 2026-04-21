/// hello_world.asm
// Prints "Hello World!" character by character using OP_PRINT
// Each LDI loads an ASCII value, PRINT outputs it, then we move to the next

LDI R1 72    //load 'H'
PRINT R1
LDI R1 101   //load 'e'
PRINT R1
LDI R1 108   //load 'l'
PRINT R1
LDI R1 108   //load 'l'
PRINT R1
LDI R1 111   //load 'o'
PRINT R1
LDI R1 32    //load ' '
PRINT R1
LDI R1 87    //load 'W'
PRINT R1
LDI R1 111   //load 'o'
PRINT R1
LDI R1 114   //load 'r'
PRINT R1
LDI R1 108   //load 'l'
PRINT R1
LDI R1 100   //load 'd'
PRINT R1
LDI R1 33    //load '!'
PRINT R1
LDI R1 10    //load a newline
PRINT R1
HALT