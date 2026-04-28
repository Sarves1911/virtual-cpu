// Tests PUSH, POP, CALL, RET in one program

// --- Stack Test ---
LDI R0 42
PUSH R0
LDI R0 0
POP R1
PRINT R1        // Expected output: 42

// --- Function Call Test ---
CALL FUNC
PRINT R0        // Expected output: 99

HALT

// --- Function ---
FUNC:
LDI R0 99
RET