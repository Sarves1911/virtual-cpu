# VIRTUAL CPU

## LSP
- Using clangd for lsp, depending on how good your editor is, sometimes you may not get proper Intellisense
- execute `bear -- make all` should resolve 
    - `compile_commands.json` will be produced that clangd can use for linting.

## Formatting
- format the entire project directory
- execute `make format`

## building
- builds the actual virtual cpu binary
- execute `make build`

## Testing
- compiles, builds and run a binary for tests defined in /test
- execute `make test`

## All
- do all of the above 
- execute `make all`
