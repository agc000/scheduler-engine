#include "weighted_scheduler.h"

#include <algorithm>
#include <vector>

// Binary search
static int find_latest_compatible(const std::vector<Task>& tasks, int i) {
    int start_time = tasks[i].m_start;

    int left = 0;
    int right = i - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (tasks[mid].m_end <= start_time) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}

ScheduleResult weighted_schedule(std::vector<Task> tasks) {
    ScheduleResult result;

    if (tasks.empty()) {
        return result;
    }

    int n = static_cast<int>(tasks.size());

    // Sort
    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        if (a.m_end != b.m_end) {
            return a.m_end < b.m_end;
        }
        return a.m_start < b.m_start;
    });

    // Compute compatibility
    std::vector<int> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = find_latest_compatible(tasks, i);
    }

    // DP table
    std::vector<int> dp(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        int exclude_value = dp[i - 1];

        int include_value = tasks[i - 1].m_value;
        if (p[i - 1] != -1) {
            include_value += dp[p[i - 1] + 1];
        }

        dp[i] = std::max(exclude_value, include_value);
    }

    result.m_totalValue = dp[n];

    // Reconstruct solution
    std::vector<bool> included(n, false);
    int i = n;

    while (i > 0) {
        int exclude_value = dp[i - 1];

        int include_value = tasks[i - 1].m_value;
        if (p[i - 1] != -1) {
            include_value += dp[p[i - 1] + 1];
        }

        if (include_value >= exclude_value) {
            included[i - 1] = true;
            result.m_scheduled.push_back(tasks[i - 1]);

            if (p[i - 1] != -1) {
                i = p[i - 1] + 1;
            } else {
                i = 0;
            }
        } else {
            i = i - 1;
        }
    }

    std::reverse(result.m_scheduled.begin(), result.m_scheduled.end());

    // Identify tasks that got dropped
    for (int j = 0; j < n; j++) {
        if (!included[j]) {
            result.m_dropped.push_back(tasks[j]);
        }
    }

    return result;
}
