# ProcessSchedulingSimulator
A C-based simulation for process scheduling and management, featuring a custom process generator, scheduler, and clock mechanism. Designed to demonstrate the workings of process scheduling algorithms in operating systems.

## Project Overview
This project is a C-based simulation designed to demonstrate the workings of process scheduling algorithms within operating systems. It features a custom process generator (`process_generator.c`), a scheduler (`scheduler.c`), and a clock mechanism (`clk.c`), providing a comprehensive look at how processes are managed and scheduled on a system level.

## Features
- Process generation and management
- Custom scheduling algorithms
- Clock mechanism for time management
- Makefile for easy compilation

## Getting Started

### Prerequisites
- GCC compiler
- Make

### Compilation
To compile the project, run the following command in the project's root directory:
```
make all
```

### Execution
After compilation, you can run the simulator components as follows:
```
./process_generator.out
./scheduler.out
./clk.out
```


## License
This project is open source and available under the [MIT License](LICENSE).

