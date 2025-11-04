#include "scheduler.h"
#include <algorithm>
#include <vector>

/**
 * Shortest Time to Completion First (STCF) / SRTF
 * Preemptive SJF: always run the ready process with the smallest remaining time.
 * - Uses helper functions so metrics (response/start/finish) are recorded correctly.
 * - No iostream output here; reporting is handled by the framework.
 */
class STCFScheduler : public Scheduler {
public:
    STCFScheduler() : Scheduler("Shortest Time to Completion First (STCF)") {}

    void schedule() override {
        sort_by_arrival_time();

        while (!all_processes_complete()) {
            // Fetch all arrived & not-yet-finished processes at current_time
            std::vector<Process*> ready = get_ready_processes(current_time);

            if (ready.empty()) {
                // Nothing ready: jump to the next arrival time
                int next_arrival = -1;
                for (const auto& p : processes) {
                    if (!p.is_complete() && p.arrival_time > current_time) {
                        if (next_arrival == -1 || p.arrival_time < next_arrival) {
                            next_arrival = p.arrival_time;
                        }
                    }
                }
                if (next_arrival == -1) break;  // no more arrivals; done
                advance_time(next_arrival);
                continue;
            }

            // Pick the process with the smallest remaining time (tie-break by PID for stability)
            Process* chosen = *std::min_element(
                ready.begin(), ready.end(),
                [](const Process* a, const Process* b) {
                    if (a->remaining_time != b->remaining_time) {
                        return a->remaining_time < b->remaining_time;
                    }
                    return a->pid < b->pid;
                }
            );

            // Preemptive step: run only 1 time unit to allow switching if a shorter job arrives
            run_process(chosen->pid, 1);
        }
    }
};
