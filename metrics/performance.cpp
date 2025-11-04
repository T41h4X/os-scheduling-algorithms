#include "performance.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>

PerformanceMetrics::PerformanceMetrics(const std::vector<Process>& procs, const GanttChart& chart)
    : processes(procs), gantt(chart) {}

double PerformanceMetrics::calculate_average_turnaround_time() const {
    // EXAMPLE IMPLEMENTATION - [demo in class]
    
    if (processes.empty()) return 0.0;

    double total_tat = 0.0;
    for (const auto& p : processes) {
        total_tat += p.turnaround_time;   // turnaround = completion - arrival
    }
    return total_tat / processes.size();
    return 0.0; // Placeholder implementation
}

double PerformanceMetrics::calculate_average_waiting_time() const {
    if (processes.empty()) return 0.0;

    double total_wait = 0.0;
    for (const auto& p : processes) {
        total_wait += p.waiting_time;   // already computed via Process::calculate_metrics()
    }
    return total_wait / processes.size();
}


double PerformanceMetrics::calculate_average_response_time() const {
    if (processes.empty()) return 0.0;

    double total_resp = 0.0;
    for (const auto& p : processes) {
        total_resp += p.response_time;  // start_time - arrival_time
    }
    return total_resp / processes.size();
}

double PerformanceMetrics::calculate_cpu_utilization() const {
    // TODO: Implement CPU utilization calculation
    // 
    // CPU Utilization = (Total CPU busy time / Total time) * 100
    // 
    // You can use gantt.get_cpu_utilization() or calculate manually:
    // - Total time = gantt.get_total_time()
    // - Idle time = gantt.get_total_idle_time()
    // - Busy time = Total time - Idle time
    // 
    // Hint: The GanttChart class already has this functionality
    
    return gantt.get_cpu_utilization();  // This is already implemented
}

double PerformanceMetrics::calculate_throughput() const {
    if (processes.empty()) return 0.0;

    int completed = 0;
    for (const auto& p : processes) {
        if (p.completion_time >= 0) ++completed;
    }
    if (completed == 0) return 0.0;

    // Use reported total time from Gantt (already accounts for idle time)
    const int total_time = gantt.get_total_time();
    if (total_time <= 0) return 0.0;

    return static_cast<double>(completed) / static_cast<double>(total_time);
}

double PerformanceMetrics::calculate_fairness_index() const {
    const int n = static_cast<int>(processes.size());
    if (n == 0) return 1.0;  // trivially fair

    double sum_w = 0.0;
    double sum_w2 = 0.0;
    for (const auto& p : processes) {
        const double w = static_cast<double>(p.waiting_time);
        sum_w  += w;
        sum_w2 += w * w;
    }

    if (sum_w2 <= 0.0) return 1.0; // all waits zero -> perfectly fair
    return (sum_w * sum_w) / (static_cast<double>(n) * sum_w2);
}


int PerformanceMetrics::calculate_context_switches() const {
    // BONUS: Count number of times CPU switches between different processes
    // 
    // Look at gantt chart entries and count transitions between different PIDs
    // Don't count idle time as a context switch
    
    const auto& entries = gantt.get_entries();
    if (entries.size() <= 1) return 0;
    
    int switches = 0;
    for (size_t i = 1; i < entries.size(); i++) {
        if (!entries[i-1].is_idle() && !entries[i].is_idle() && 
            entries[i-1].pid != entries[i].pid) {
            switches++;
        }
    }
    return switches;
}

void PerformanceMetrics::print_summary() const {
    if (!is_valid_metrics()) {
        std::cout << "Warning: Some processes have invalid timing data!\n";
    }
    
    std::cout << "\n=== Performance Metrics Summary ===\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average Turnaround Time: " << calculate_average_turnaround_time() << " time units\n";
    std::cout << "Average Waiting Time:    " << calculate_average_waiting_time() << " time units\n";
    std::cout << "Average Response Time:   " << calculate_average_response_time() << " time units\n";
    std::cout << "CPU Utilization:         " << calculate_cpu_utilization() << "%\n";
    std::cout << "Throughput:              " << calculate_throughput() << " processes/time unit\n";
    std::cout << "Context Switches:        " << calculate_context_switches() << "\n";
    std::cout << "Fairness Index:          " << calculate_fairness_index() << "\n";
    std::cout << "\n";
}

void PerformanceMetrics::print_detailed() const {
    print_summary();
    print_process_metrics();
    
    std::cout << "=== Gantt Chart Analysis ===\n";
    std::cout << "Total Time:      " << gantt.get_total_time() << " time units\n";
    std::cout << "Total Idle Time: " << gantt.get_total_idle_time() << " time units\n";
    std::cout << "Total Processes: " << processes.size() << "\n";
    std::cout << "\n";
}

void PerformanceMetrics::print_process_metrics() const {
    std::cout << "=== Individual Process Metrics ===\n";
    std::cout << "PID\tArrival\tBurst\tStart\tFinish\tTurnaround\tWaiting\tResponse\n";
    std::cout << "---\t-------\t-----\t-----\t------\t----------\t-------\t--------\n";
    
    for (const auto& process : processes) {
        std::cout << process.pid << "\t"
                  << process.arrival_time << "\t"
                  << process.burst_time << "\t"
                  << process.start_time << "\t"
                  << process.completion_time << "\t"
                  << process.turnaround_time << "\t"
                  << process.waiting_time << "\t"
                  << process.response_time << "\n";
    }
    std::cout << "\n";
}

int PerformanceMetrics::get_total_time() const {
    return gantt.get_total_time();
}

int PerformanceMetrics::get_total_processes() const {
    return processes.size();
}

bool PerformanceMetrics::is_valid_metrics() const {
    for (const auto& process : processes) {
        if (process.start_time < 0 || process.completion_time < 0) {
            return false;
        }
        if (process.completion_time < process.start_time) {
            return false;
        }
        if (process.start_time < process.arrival_time) {
            return false;
        }
    }
    return true;
}
