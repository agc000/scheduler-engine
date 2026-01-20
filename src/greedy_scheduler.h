#ifndef GREEDY_SCHEDULER_H
#define GREEDY_SCHEDULER_H

#include "models.h"
#include <vector>

// Greedy interval scheduling algorithm (unweighted)
// Maximizes the number of non-overlapping tasks
// Time complexity: O(n log n)
ScheduleResult greedy_schedule(std::vector<Task> tasks);

#endif
