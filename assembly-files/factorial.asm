// Computes factorial(5) using recursion + stack

// main
LDI R0 5        // R0 = n
CALL FACT       // R1 = factorial(R0)
PRINT R1        // Expected: 120
HALT

// FACT(n)
// Input: R0 = n
// Output: R1 = factorial(n)
FACT:
LDI R2 1
SUB R3 R0 R2    // R3 = n - 1
JZ BASE_CASE    // if n - 1 == 0, return 1

PUSH R0         // save current n
MOV R0 R3       // R0 = n - 1
CALL FACT       // recursive call: factorial(n-1)
POP R4          // restore original n into R4

// Multiply R4 * R1 using repeated addition
// R4 = original n
// R1 = factorial(n-1)
// R6 = product
LDI R6 0

MULT_LOOP:
ADD R6 R6 R1    
SUB R4 R4 R2
JZ MULT_DONE
JMP MULT_LOOP

MULT_DONE:
MOV R1 R6
RET 

BASE_CASE:
LDI R1 1
RET