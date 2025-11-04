# CPU Scheduling Simulator Assignment

## Overview
This assignment will help you understand and implement various CPU scheduling algorithms. You'll work with a simulation framework that models processes and implements different scheduling strategies.

## What's Provided
- Process class and simulation framework
- Visualization tools for Gantt charts
- Performance metrics calculation framework
- Test cases and sample data
- Makefile for easy compilation

## What You Need to Implement
1. **First Come First Serve (FCFS)** - `schedulers/fcfs.cpp`
2. **Shortest Job First (SJF)** - `schedulers/sjf.cpp`
3. **Shortest Time to Completion First (STCF)** - `schedulers/stcf.cpp`
4. **Round Robin (RR)** - `schedulers/round_robin.cpp`
5. **Performance Metrics** - Complete functions in `metrics/performance.cpp`

## Compilation
```bash
make all          # Compile everything
make test         # Run test cases
make clean        # Clean build files
```

## Running the Simulator
```bash
./scheduler <algorithm> <input_file>
```

Example:
```bash
./bin/scheduler fcfs test_data/simple.txt
./bin/scheduler rr test_data/interactive.txt
```

## Project Structure
```
scheduling/
├── include/           # Header files
├── src/              # Core implementation
├── schedulers/       # Your algorithm implementations
├── metrics/          # Performance calculation
├── test_data/        # Sample process files
├── tests/            # Unit tests
└── README.md
```
