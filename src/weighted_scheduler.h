#ifndef WEIGHTED_SCHEDULER_H
#define WEIGHTED_SCHEDULER_H

#include "models.h"
#include <vector>

// Weighted interval scheduling algorithm using dynamic programming
// Maximizes the total value of non-overlapping tasks
// Time complexity: O(n log n)
ScheduleResult weighted_schedule(std::vector<Task> tasks);

#endif
