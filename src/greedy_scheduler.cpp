#include "greedy_scheduler.h"
#include <algorithm>

ScheduleResult greedy_schedule(std::vector<Task> tasks) {
    ScheduleResult result;

    if (tasks.empty()) {
        return result;
    }


    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        if (a.m_end != b.m_end) {
            return a.m_end < b.m_end;
        }

        if (a.m_start != b.m_start) {
            return a.m_start < b.m_start;
        }
        return a.m_id < b.m_id;
    });


    result.m_scheduled.push_back(tasks[0]);
    result.m_totalValue += tasks[0].m_value;
    int last_end = tasks[0].m_end;

    for (size_t i = 1; i < tasks.size(); i++) {
        if (tasks[i].m_start >= last_end) {
            result.m_scheduled.push_back(tasks[i]);
            result.m_totalValue += tasks[i].m_value;
            last_end = tasks[i].m_end;
        } else {
            result.m_dropped.push_back(tasks[i]);
        }
    }

    return result;
}