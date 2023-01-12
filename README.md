# ALU Emulator

### Overview

This is a study project written in C++ that emulates an Arithmetic Logic Unit (ALU).  
Program reads ALU command mnemonics from a file (`files/in.txt`), converts them into bit flags and processes to the ALU emulator.  
Output is done to a file (`files/out.txt`).  
As an example, there's also a simple Fibonacci program (`files/fibonacci.txt`).

### Mnemonics

All mnemonics are defined in 'CMD_TABLE' map.  
Current list of mnemonics:  
|   Mnemonics   |         Result        |       Name       |
|:-------------:|:---------------------:|:----------------:|
| `XZ`          | X = 0                 | Zero X           |
| `X++`         | X = X + 1             | Increment X      |
| `X--`         | X = X - 1             | Decrement X      |
| `OR X`        | X = X OR Y (bitwise)  | Bitwise OR       |
| `AND X`       | X = X AND Y (bitwise) | Bitwise AND      |
| `ADD X`       | X = X + Y             | Sum X, Y         |
| `SUB X`       | X = X - Y             | Difference X, Y  |
| `SUB XS`      | X = Y - X             | Difference Y, X  |
| `IMP X`       | X = X → Y             | Implication X, Y |
| `OUT X`       | Print X               | Output X         |
| `YZ`          | Y = 0                 | Zero Y           |
| `Y++`         | Y = Y + 1             | Increment Y      |
| `Y--`         | Y = Y - 1             | Decrement Y      |
| `OR Y`        | Y = Y OR X (bitwise)  | Bitwise OR       |
| `AND Y`       | Y = Y AND X (bitwise) | Bitwise AND      |
| `ADD Y`       | Y = Y + X             | Sum Y, X         |
| `SUB Y`       | Y = Y - X             | Difference Y, X  |
| `SUB YS`      | Y = X - Y             | Difference X, Y  |
| `IMP Y`       | Y = Y → X             | Implication Y, X |
| `OUT Y`       | Print Y               | Output Y         |

### Usage example

1. (Optional) Configure input/output files through defines `FILE_IN` and `FILE_OUT`
2. Write in `files/in.txt` a program using mnemonics, one on each line
3. Compilate and run `main.cpp` with `files/` directory located in working folder
4. See the result in `files/out.txt`