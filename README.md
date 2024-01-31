# ProcessSchedulingSimulator

## Project Overview
This project is a C-based simulation designed to demonstrate the workings of process scheduling algorithms within operating systems. It features a custom process generator (`process_generator.c`), a scheduler (`scheduler.c`), and a clock mechanism (`clk.c`), providing a comprehensive look at how processes are managed and scheduled on a system level.

## Features
- Process generation and management
- Implementation of Shortest Job First (SJF) and Preemptive Highest Priority First (PHPF) scheduling algorithms
- Clock mechanism for time management
- Use of queues and priority queues for process management
- Makefile for easy compilation

## Technical Overview

### Data Structures
- **Process Generator Queue:** Utilizes a FIFO queue for managing incoming processes.
- **Scheduler Priority Queue:** Employs a priority queue, implemented as an array, for scheduling processes based on execution time or priority.

### Scheduling Algorithms
- **SJF:** Prioritizes processes with the shortest execution time. Processes are scheduled based on their arrival time and execution duration.
- **PHPF:** Extends SJF by preempting the current process if a new process arrives with a higher priority, ensuring urgent tasks are addressed promptly.

### Assumptions
- A maximum of 100 processes can be handled due to the data structure limitations.

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

## Test Case Example

For a detailed test case example and its results, please refer to the [Test Case Document](Test_case.pdf).

Click on the link to view or download the PDF with the test case and result.

## License
This project is open source and available under the [MIT License](LICENSE).

