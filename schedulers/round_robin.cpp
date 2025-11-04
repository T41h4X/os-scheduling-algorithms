#include "scheduler.h"
#include <queue>
#include <algorithm>
#include <vector>

/**
 * Round Robin (RR) – helper-based, metrics-friendly
 * - Uses base helpers so start/completion/response times are recorded correctly.
 * - No iostream printing here; reporting is handled by the framework.
 */
class RoundRobinScheduler : public Scheduler {
public:
    explicit RoundRobinScheduler(int tq = 2)
        : Scheduler("Round Robin (RR)"), time_quantum(tq) {}

    void schedule() override {
        const int n = static_cast<int>(processes.size());
        if (n == 0) return;

        sort_by_arrival_time();

        // Queue holds PIDs (not indices). We'll enqueue as processes arrive.
        std::queue<int> ready_q;

        int next_to_arrive = 0; // index into `processes` (sorted by arrival)

        auto enqueue_arrivals_up_to = [&](int t) {
            while (next_to_arrive < n && processes[next_to_arrive].arrival_time <= t) {
                ready_q.push(processes[next_to_arrive].pid);
                next_to_arrive++;
            }
        };

        // If simulation starts before the first arrival, jump to the first arrival.
        if (next_to_arrive < n && current_time < processes[0].arrival_time) {
            advance_time(processes[0].arrival_time);
        }
        enqueue_arrivals_up_to(current_time);

        // Main RR loop
        while (!all_processes_complete()) {
            // If nothing is ready, jump to the next arrival time.
            if (ready_q.empty()) {
                if (next_to_arrive < n) {
                    advance_time(processes[next_to_arrive].arrival_time);
                    enqueue_arrivals_up_to(current_time);
                    continue;
                } else {
                    // No one left to arrive and queue empty => done
                    break;
                }
            }

            // Pick next PID in round-robin order
            int pid = ready_q.front();
            ready_q.pop();

            Process* p = find_process_by_pid(pid);
            if (!p || p->is_complete()) {
                // Skip invalid or already finished (defensive)
                enqueue_arrivals_up_to(current_time);
                continue;
            }

            // Time slice for this round
            int slice = std::min(time_quantum, p->remaining_time);

            // Run the process for `slice` time units.
            // This helper sets start_time on first dispatch, updates response_time,
            // adds to Gantt, and handles completion bookkeeping.
            run_process(pid, slice);

            // Enqueue any processes that arrived while we were running `pid`.
            enqueue_arrivals_up_to(current_time);

            // If `pid` still has remaining time, rotate it to the back of the queue.
            if (!p->is_complete()) {
                ready_q.push(pid);
            }
        }
    }

    void set_time_quantum(int quantum) {
        if (quantum > 0) time_quantum = quantum;
    }

private:
    int time_quantum;
};
