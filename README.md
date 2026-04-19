# VIRTUAL CPU

## LSP
- Using clangd for lsp, depending on how good your editor is, sometimes you may not get proper Intellisense
- execute `bear -- make all` should resolve 
    - `compile_commands.json` will be produced that clangd can use for linting.

## Testing
- ensure there is a build dir in the folder
- execute `make test`
