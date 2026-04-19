# VIRTUAL CPU

## LSP
- Using clangd for lsp, depending on how good your editor is, sometimes you may not get proper Intellisense
- execute `bear -- make all` should resolve 
    - `compile_commands.json` will be produced that clangd can use for linting.

## building
- ensure there is a build dir in the folder
- builds the actual virtual cpu binary
- execute `make build`

## Testing
- ensure there is a build dir in the folder
- compiles, builds and run a binary for tests defined in /test
- execute `make test`
