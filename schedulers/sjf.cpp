#include "scheduler.h"
#include <algorithm>
#include <vector>

/**
 * Shortest Job First (SJF) - Non-preemptive
 * Follows the assignment guidelines:
 *  - Use get_ready_processes(current_time) to obtain arrived, incomplete processes
 *  - If none are ready, advance_time(next_arrival)
 *  - Always pick the ready process with the smallest burst (remaining) time
 *  - Run the chosen process to completion with run_process(pid, duration)
 */
class SJFScheduler : public Scheduler {
public:
    SJFScheduler() : Scheduler("Shortest Job First (SJF)") {}

    void schedule() override {
        // Ensure deterministic start state
        sort_by_arrival_time();

        while (!all_processes_complete()) {
            // Get all arrived & incomplete processes at current_time
            std::vector<Process*> ready = get_ready_processes(current_time);

            if (ready.empty()) {
                // No ready processes: jump to the next arrival
                int next_arrival = -1;
                for (const auto& p : processes) {
                    if (!p.is_complete() && p.arrival_time > current_time) {
                        if (next_arrival == -1 || p.arrival_time < next_arrival) {
                            next_arrival = p.arrival_time;
                        }
                    }
                }
                if (next_arrival == -1) {
                    // Nothing left to arrive; we're done
                    break;
                }
                // Advance time using the provided helper (adds idle slot to Gantt)
                advance_time(next_arrival);
                continue;
            }

            // Choose the shortest job among ready processes (by remaining_time, tie by PID)
            Process* chosen = *std::min_element(
                ready.begin(), ready.end(),
                [](const Process* a, const Process* b) {
                    if (a->remaining_time != b->remaining_time) {
                        return a->remaining_time < b->remaining_time;
                    }
                    return a->pid < b->pid;
                }
            );

            // Non-preemptive: run to completion
            const int duration = chosen->remaining_time;
            run_process(chosen->pid, duration);
        }
    }
};
