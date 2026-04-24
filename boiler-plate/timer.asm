// Timer Countdown Program
// R1 = Timer Value (Starts at 10)
// R2 = Decrementer (Always 1)

LDI R1 10
LDI R2 1

TIMER_LOOP:
SUB R1 R1 R2   // R1 = R1 - 1
JZ END         // If R1 hits 0, Z-Flag flips, jump to END
JMP TIMER_LOOP // Otherwise, jump back to the top of the loop

END:
HALT