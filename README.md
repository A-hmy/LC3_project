# LC3_project
# LC3 Simulator

This project is a simulator for the LC3 architecture that takes assembly instructions from an input file, converts them into machine code, fills the memory with this machine code, and then executes the instructions.

## Features

- Uploads an assembly instruction file.
- Converts assembly instructions to machine code.
- Populates memory with machine code.
- Executes instructions from memory and displays results in registers and memory.
- Executes instructions in 6 phases corresponding to the LC3 architecture.
- Displays the state of registers and memory at each step of execution.
  
## Usage

1. Run the application.
2. Upload the assembly instruction file by clicking the "Click here to upload your file" button.
3. Click the "Assemble" button to populate the memory with machine code.
4. Each time you click the "Next" button, one phase of the six-phase instruction execution is performed, and the contents of the registers and memory are displayed.
5. Click the "Stop" button to halt the execution of instructions.

## Project Structure

- `LC3project.pro`: Project configuration file.
- `Headers/`:
  - `assembler.h`: Header file for the assembler.
  - `globalvariable.h`: Header file for global variables.
  - `handlefunction.h`: Header file for handling functions.
  - `instructions.h`: Header file for instructions.
  - `mainwindow.h`: Header file for the main window.
  - `memory.h`: Header file for memory management.
  - `MessageBox.h`: Header file for message box handling.
  - `registers.h`: Header file for registers management.
- `Sources/`:
  - `assembler.cpp`: Implementation of the assembler.
  - `globalvariable.cpp`: Implementation of global variables.
  - `handlefunction.cpp`: Implementation of handling functions.
  - `instructions.cpp`: Implementation of instructions.
  - `main.cpp`: Main file to run the application.
  - `mainwindow.cpp`: Implementation of the main window.
  - `memory.cpp`: Implementation of memory management.
  - `registers.cpp`: Implementation of registers management.
- `Forms/`: UI forms used in the project.

## Execution Phases

The LC3 instructions are executed in the following six phases, each corresponding to a clock cycle:

1. **Fetch**: The instruction is fetched from memory. The Program Counter (PC) points to the memory address of the instruction to be fetched. The instruction is then stored in the Instruction Register (IR).

2. **Decode**: The instruction stored in the IR is decoded to determine the operation to be performed and the operands to be used.

3. **Evaluate Address**: The effective address of the operand is calculated. This phase involves computing the memory address if the instruction requires one.

4. **Fetch Operands**: The operands required for the execution of the instruction are fetched from the memory or registers.

5. **Execute**: The instruction is executed. This could involve arithmetic or logical operations, data movement, or control operations.

6. **Store Result**: The result of the execution is stored in the appropriate destination register or memory location.

## How It Works

1. The assembly file is uploaded, and when the "Assemble" button is pressed, the assembly instructions are converted to machine code, and the memory is populated.
2. Each time the "Next" button is pressed, one phase of the six-phase instruction execution is performed.
3. The state of the registers and memory is displayed at each phase.

## Application Screenshot

![LC3 Simulator](./path/to/your/image.png)

## Detailed Description

- **Assembler**: The assembler processes the assembly code in two passes. In the first pass, it scans all lines to store labels and their addresses in a table. In the second pass, it converts the instructions to their machine code forms.
- **Execution Phases**: Instructions are divided into six phases corresponding to the LC3 architecture. Each press of the "Next" button executes one phase, updating the register and memory contents, and displaying the current state to the user. Each phase represents a clock cycle.
- **User Interface**: The user interface provides buttons to upload files, assemble code, and step through the instruction execution phases. The interface displays the current state of the registers, including PC (Program Counter), IR (Instruction Register), MAR (Memory Address Register), MDR (Memory Data Register), and the general-purpose registers R0 to R7. It also shows the memory contents in a table format.

## Example

To see the simulator in action, follow these steps:
1. Run the application.
2. Upload an assembly file (e.g., `example.asm`).
3. Click "Assemble" to convert and load the instructions into memory.
4. Click "Next" to start the execution. Each click advances the execution by one phase, showing the updated state of registers and memory.
5. Click "Stop" to end the simulation.

