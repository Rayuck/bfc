# Brainfuck Compiler

A small Brainfuck compiler written in pure C.

## Limitations

- Input is **not** yet implemented.
- Few optimizations.
- Only compiles Brainfuck to x86_64 (Linux) assembly.
- Doesn't assemble or link the output file (bc lazy :>)

## Usage

```bfc input.bf output.asm```

## Requirements
### Arch based systems
```sudo pacman -S nasm```

### Debian

```sudo apt-get install nasm```
