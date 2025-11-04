#include "scheduler.h"
#include <iostream>

/**
 * First Come First Serve (FCFS) Scheduler
 * Also known as First In First Out (FIFO)
 * 
 * Algorithm: Execute processes in the order they arrive
 * - Non-preemptive
 * - Simple queue-based scheduling
 * 
 * TODO: Implement the schedule() function
 * HINT: Sort processes by arrival time, then execute each completely
 */
class FCFSScheduler : public Scheduler {
public:
    FCFSScheduler() : Scheduler("First Come First Serve (FCFS)") {}
    
    void schedule() override {
        std::cout << "Starting FCFS scheduling...\n";
        
        // EXAMPLE IMPLEMENTATION [Demo in class]
        
        sort_by_arrival_time();

        // Iterate through all processes
        for (auto& process : processes) {
            // If CPU is idle (no process has arrived yet), advance time
            if (current_time < process.arrival_time) {
                advance_time(process.arrival_time);
            }

            // Run process for its entire burst time
            run_process(process.pid, process.burst_time);
        }

        
        
        std::cout << "FCFS scheduling completed.\n";
    }
};
