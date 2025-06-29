# Brainfuck Compiler

A small Brainfuck compiler written in pure C.

## Limitations

- Input is **not** yet implemented.
- Few optimizations.
- Only compiles Brainfuck to x86_64 (Linux) assembly.
- Generates build.sh instead of assembling and linking at run time
- Undefined behaviour beyond 30k buffer (somehow accurate behaviour)

## Usage

```bfc input.bf output```

## Requirements
### Arch based systems
```sudo pacman -S nasm```

### Debian based systems

```sudo apt-get install nasm```
