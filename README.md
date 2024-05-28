# Pascal to x86 Compiler

This project compiles the Pascal programming language into x86 instructions. The compiler is structured into three main components: the Lexer, Parser, and Code Generator.

## Components

- **Lexer**: The lexer (`lexan.l`) processes raw Pascal code and generates tokens. It sets the stage for syntactic analysis by breaking down the code into meaningful symbols.
- **Parser**: Utilizing a Context-Free Grammar, the parser builds an Abstract Syntax Tree (AST) that represents the hierarchical structure of the program code.
- **Code Generator**: This component takes the AST and translates it into executable x86 assembly instructions.

## Getting Started

To run the compiler, follow these steps in the `/src` directory:

### Building the Compiler

Compile the source code using Make:

```
make compiler
```
To generate assembly instructions from a Pascal source file, run:
```
Copy code
./compiler < /path/to/pascal/file > /path/to/output/file
```
Move instructions to code.s
```
cc driver.c code.s -lm
./a.out
```
These instructions will convert your Pascal code into a running executable on an x86-based machine.
