# System Software Lab Programs

This repository contains key implementations from the **System Software Lab**, focusing on the foundational components of a compiler or assembler. It includes:

- ⚙️ **Pass 1** – Symbol table generation and intermediate code creation
- ⚙️ **Pass 2** – Final machine code or object code generation using intermediate code and symbol table
- ⚙️ **One Pass Assembler** – Single pass implementation that combines both phases for efficiency

---

## 📘 Program Overview

### 1. `pass1.c`
- Reads the source code (assembly or intermediate language)
- Generates the **Symbol Table**
- Produces **Intermediate Code**
- Outputs line-by-line location counter (LC) values

### 2. `pass2.c`
- Uses the **Symbol Table** and **Intermediate Code**
- Generates the final **Object Code** or **Machine Code**
- Resolves labels and memory addresses

### 3. `onepass.c`
- Combines symbol table creation and code generation in a single pass
- Suitable for simple, small-sized assembly programs
- More efficient, but complex labels must be handled carefully

---

## 🧠 Concepts Demonstrated

- Lexical Analysis (manual)
- Symbol Table Management
- Location Counter Tracking
- Mnemonic to Opcode Mapping
- Handling of Labels, Constants, and Directives
- Memory Allocation Simulation

---

## 🛠️ How to Compile & Run

### Compilation:
```bash
gcc pass1.c -o pass1
gcc pass2.c -o pass2
gcc onepass.c -o onepass
