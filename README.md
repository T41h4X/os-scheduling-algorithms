# CPU Scheduling Algorithms Simulator

A comprehensive C++ implementation of fundamental CPU scheduling algorithms with performance analysis and Gantt chart visualization. This educational tool demonstrates how different scheduling strategies affect system performance metrics.

## 🚀 Features

- **Multiple Scheduling Algorithms:**
  - First Come First Serve (FCFS/FIFO)
  - Shortest Job First (SJF)
  - Shortest Time to Completion First (STCF/SRTF)
  - Round Robin (RR) with configurable time quantum

- **Visual Analysis:**
  - Interactive Gantt chart generation
  - Process execution timeline visualization
  - Color-coded process representation

- **Performance Metrics:**
  - Average turnaround time
  - Average waiting time
  - Average response time
  - CPU utilization percentage
  - Context switch analysis

- **Flexible Input System:**
  - File-based process definition
  - Multiple test scenarios included
  - Custom process creation support

## 📋 Requirements

- **Compiler:** C++11 compatible compiler (g++, clang++, MSVC)
- **Build System:** Make utility
- **Operating System:** Cross-platform (Linux, macOS, Windows)

## 🛠️ Installation

### Clone the Repository
```bash
git clone https://github.com/T41h4X/os-scheduling-algorithms.git
cd os-scheduling-algorithms
```

### Compile the Project
```bash
make all
```

### Run Tests (Optional)
```bash
make test
```

### Clean Build Files
```bash
make clean
```

## 🎯 Usage

### Basic Usage
```bash
./bin/scheduler <algorithm> <input_file> [options]
```

### Available Algorithms
- `fcfs` or `fifo` - First Come First Serve
- `sjf` - Shortest Job First
- `stcf` or `srtf` - Shortest Time to Completion First
- `rr` - Round Robin

### Command Line Options
- `--no-gantt` - Disable Gantt chart display
- `--detailed` - Show detailed performance metrics
- `--help` - Display help information

### Examples
```bash
# Run FCFS algorithm with simple test data
./bin/scheduler fcfs test_data/simple.txt

# Run Round Robin with detailed metrics
./bin/scheduler rr test_data/interactive.txt --detailed

# Run SJF without Gantt chart
./bin/scheduler sjf test_data/mixed.txt --no-gantt

# Display help information
./bin/scheduler --help
```

## 📁 Project Structure

```
scheduling/
├── include/           # Header files
│   ├── scheduler.h    # Main scheduler interface
│   ├── process.h      # Process class definition
│   ├── gantt_chart.h  # Gantt chart utilities
│   ├── performance.h  # Performance metrics
│   └── file_parser.h  # Input file parsing
├── src/              # Core implementation
│   ├── scheduler.cpp  # Base scheduler logic
│   ├── process.cpp    # Process management
│   ├── gantt_chart.cpp# Visualization code
│   └── file_parser.cpp# File I/O operations
├── schedulers/       # Algorithm implementations
│   ├── fcfs.cpp      # First Come First Serve
│   ├── sjf.cpp       # Shortest Job First
│   ├── stcf.cpp      # Shortest Time to Completion
│   └── round_robin.cpp# Round Robin
├── metrics/          # Performance analysis
│   └── performance.cpp# Metrics calculation
├── test_data/        # Sample input files
│   ├── simple.txt    # Basic test case
│   ├── interactive.txt# Interactive processes
│   ├── mixed.txt     # Mixed workload
│   ├── priority.txt  # Priority-based processes
│   └── simultaneous.txt# Simultaneous arrivals
├── tests/            # Unit tests
├── bin/              # Compiled executables
├── obj/              # Object files
├── Makefile          # Build configuration
└── README.md         # This file
```

## 📊 Input File Format

Process files should follow this format:
```
# Process_ID Arrival_Time Burst_Time [Priority]
P1 0 5
P2 1 3
P3 2 8
P4 3 6
```

- **Process_ID:** Unique identifier for the process
- **Arrival_Time:** When the process arrives in the system
- **Burst_Time:** CPU time required by the process
- **Priority:** Optional priority value (higher number = higher priority)

## 📈 Sample Output

```
Loading processes from: test_data/simple.txt
Loaded 4 processes

=== FCFS Scheduling Results ===

Process Execution Order: P1 → P2 → P3 → P4

Gantt Chart:
|  P1  |  P2  | P3 | P4 |
0      5      8    16   22

Performance Metrics:
- Average Turnaround Time: 11.25
- Average Waiting Time: 5.75
- Average Response Time: 5.75
- CPU Utilization: 100.00%
- Total Context Switches: 3
```

## 🧪 Testing

The project includes comprehensive test cases:

- **simple.txt:** Basic 4-process scenario
- **interactive.txt:** Short, frequent processes
- **mixed.txt:** Combination of CPU and I/O bound processes
- **simultaneous.txt:** All processes arrive at time 0
- **priority.txt:** Priority-based scheduling scenarios

### Running All Tests
```bash
# Test each algorithm with different datasets
./bin/scheduler fcfs test_data/simple.txt
./bin/scheduler sjf test_data/simple.txt
./bin/scheduler rr test_data/interactive.txt
./bin/scheduler stcf test_data/mixed.txt
```

## 🎓 Educational Value

This simulator is designed for:
- **Operating Systems Courses:** Understanding CPU scheduling concepts
- **Algorithm Analysis:** Comparing scheduling algorithm performance
- **System Performance:** Learning about metrics and optimization
- **Research Projects:** Baseline for advanced scheduling research

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/new-algorithm`)
3. Commit your changes (`git commit -am 'Add new scheduling algorithm'`)
4. Push to the branch (`git push origin feature/new-algorithm`)
5. Create a Pull Request

## 📝 Algorithm Details

### First Come First Serve (FCFS)
- **Strategy:** Execute processes in arrival order
- **Advantages:** Simple, fair, no starvation
- **Disadvantages:** Poor average waiting time, convoy effect

### Shortest Job First (SJF)
- **Strategy:** Execute shortest remaining job first
- **Advantages:** Optimal average waiting time
- **Disadvantages:** Starvation of long processes, requires burst time knowledge

### Round Robin (RR)
- **Strategy:** Time-sliced execution with configurable quantum
- **Advantages:** Fair, good response time, no starvation
- **Disadvantages:** Higher context switch overhead

### Shortest Time to Completion First (STCF)
- **Strategy:** Preemptive SJF with remaining time consideration
- **Advantages:** Better response time than SJF
- **Disadvantages:** Complex implementation, starvation possible

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👨‍💻 Author

**T41h4X**
- GitHub: [@T41h4X](https://github.com/T41h4X)
- Repository: [os-scheduling-algorithms](https://github.com/T41h4X/os-scheduling-algorithms)

## 🙏 Acknowledgments

- Operating Systems concepts from modern textbooks
- CPU scheduling algorithm research papers
- Educational resources from computer science curriculum

---

**⭐ Star this repository if you found it helpful!**
