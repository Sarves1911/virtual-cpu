# VIRTUAL CPU

## Introduction

This project is a C++ implementation of a software CPU running our custom ISA.

## For The Professor

### Part1
- execute `make run-fibo` for fibonacci sequence
- execute `make run-helloworld` for hello world 
- execute `make run-timer` for a quick loop demo
- execute `make run-timer-verbose` for timer program executed in verbose mode (prints out the state of CPU)
- execute `make debug-fibo` for a demo of the debugger

### Part2
- execute `make run-factorial` for a quick factorial demo
- execute  `make debug-factorial` for a demo of the factorial debugger

### Demos
- located in the /demo directory of the repo
- Demo1 -> fibonacci, demo2 -> factorial

## For The Team

### LSP
- Using clangd for lsp, depending on how good your editor is, sometimes you may not get proper Intellisense
- execute `bear -- make all` should resolve 
    - `compile_commands.json` will be produced that clangd can use for linting.

### Formatting
- format the entire project directory
- execute `make format`

### building
- builds the actual virtual cpu binary and assembler
- execute `make build`

### Testing
- compiles, builds and run a binary for tests defined in /test
- execute `make test`

### All
- do all of the above 
- execute `make all`
