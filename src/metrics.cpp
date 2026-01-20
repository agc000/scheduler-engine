#include "../metrics.h"

#include <algorithm>
#include <iomanip>
#include <iostream>

double calculate_utilization(const std::vector<Task>& scheduled) {
    if (scheduled.empty()) {
        return 0.0;
    }

    int earliest_start = scheduled[0].m_start;
    int latest_end = scheduled[0].m_end;
    int total_duration = 0;

    for (const Task& task : scheduled) {
        earliest_start = std::min(earliest_start, task.m_start);
        latest_end = std::max(latest_end, task.m_end);
        total_duration += task.duration();
    }

    int time_span = latest_end - earliest_start;
    if (time_span == 0) {
        return 0.0;
    }

    return (100.0 * total_duration) / time_span;
}

bool verify_no_overlaps(const std::vector<Task>& scheduled) {
    for (size_t i = 0; i < scheduled.size(); i++) {
        for (size_t j = i + 1; j < scheduled.size(); j++) {
            if (scheduled[i].overlaps(scheduled[j])) {
                return false;
            }
        }
    }
    return true;
}

void print_schedule_result(const ScheduleResult& result,
                           int total_tasks,
                           const std::string& mode) {
    std::cout << "\n";
    std::cout << "=== ";
    if (mode == "greedy") {
        std::cout << "GREEDY INTERVAL SCHEDULING";
    } else {
        std::cout << "WEIGHTED INTERVAL SCHEDULING";
    }
    std::cout << " ===\n\n";

    // Print scheduled tasks
    std::cout << "SCHEDULED TASKS:\n";
    if (result.m_scheduled.empty()) {
        std::cout << "  (none)\n";
    } else {
        for (const Task& task : result.m_scheduled) {
            std::cout << "  " << std::setw(6) << std::left << task.m_id
                      << " [" << std::setw(4) << std::right << task.m_start
                      << " - " << std::setw(4) << task.m_end << "]"
                      << "   Value: " << task.m_value << "\n";
        }
    }

    // Calculate and print metrics
    double utilization = calculate_utilization(result.m_scheduled);

    std::cout << "\nMETRICS:\n";
    std::cout << "  Total Tasks Processed: " << total_tasks << "\n";
    std::cout << "  Tasks Scheduled: " << result.m_scheduled.size() << "\n";
    std::cout << "  Tasks Dropped: " << result.m_dropped.size() << "\n";
    std::cout << "  Total Value: " << result.m_totalValue << "\n";
    std::cout << "  Schedule Utilization: " << std::fixed << std::setprecision(2)
              << utilization << "%\n";

    if (!verify_no_overlaps(result.m_scheduled)) {
        std::cout << "  WARNING: Overlapping tasks detected in schedule!\n";
    }

    if (!result.m_dropped.empty()) {
        std::cout << "\nDROPPED TASKS ";
        if (mode == "greedy") {
            std::cout << "(Conflicts):\n";
        } else {
            std::cout << "(Not Selected):\n";
        }

        for (const Task& task : result.m_dropped) {
            std::cout << "  " << std::setw(6) << std::left << task.m_id
                      << " [" << std::setw(4) << std::right << task.m_start
                      << " - " << std::setw(4) << task.m_end << "]"
                      << "   Value: " << task.m_value << "\n";
        }
    }

    std::cout << "\n";
}
