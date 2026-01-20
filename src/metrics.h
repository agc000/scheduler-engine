#ifndef METRICS_H
#define METRICS_H

#include "models.h"
#include <string>
#include <vector>

// Calculate schedule utilization (percentage of time covered by scheduled tasks)
double calculate_utilization(const std::vector<Task>& scheduled);

// Verify that scheduled tasks do not overlap
bool verify_no_overlaps(const std::vector<Task>& scheduled);

// Print schedule result with metrics
void print_schedule_result(const ScheduleResult& result,
                           int total_tasks,
                           const std::string& mode);

#endif // METRICS_H
