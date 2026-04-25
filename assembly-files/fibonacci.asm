// Iterative Fibonacci Sequence
// R1 = Current (Starts at 0)
// R2 = Next (Starts at 1)
// R3 = Temp (Math result)
// R4 = Loop Counter (How many numbers to generate)
// R5 = Decrementer (Always 1)

LDI R1 0
LDI R2 1
LDI R4 10      // We will calculate the 10th Fibonacci number
LDI R5 1

LOOP_START:
ADD R3 R1 R2   // R3 = R1 + R2
MOV R1 R2      // Shift Current
MOV R2 R3      // Shift Next

SUB R4 R4 R5   // Counter = Counter - 1
JZ END         // If Counter hits 0, Z-Flag flips, jump to END
JMP LOOP_START // Otherwise, unconditionally jump to loop again

END:
HALT
