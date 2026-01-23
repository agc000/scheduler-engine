# Schedule Engine — C++ Scheduling & Conflict Resolution Tool

A command-line scheduling engine implemented in **C++17** that solves interval scheduling problems using both **greedy** and **dynamic programming** approaches.  
Designed with clean engineering practices, correctness verification, and resume-readiness in mind.

---

## Overview

This project takes a set of tasks with start times, end times, and values, and selects an optimal non-overlapping subset based on the chosen scheduling strategy.

It supports:
- **Greedy interval scheduling** (maximizes number of tasks)
- **Weighted interval scheduling** (maximizes total value)
- Metrics for solution quality and validation
- Unit tests covering edge cases and correctness

The tool is intentionally focused: a **CLI-only**, well-tested C++ project emphasizing algorithms, correctness, and clean structure.

---

##  Algorithms Implemented

### Greedy Interval Scheduling
- Sorts tasks by earliest end time
- Iteratively selects the next compatible task
- Optimal for maximizing **number of non-overlapping tasks**
- Runs in **O(n log n)** time

### Weighted Interval Scheduling
- Uses **dynamic programming**
- Precomputes the latest non-conflicting task for each interval
- Maximizes **total value**, not task count
- Runs in **O(n log n)** time due to sorting and binary search

This contrast highlights when greedy algorithms are sufficient and when DP is required.

---

## Metrics Reported

After scheduling, the engine reports:
- **Total value** of selected tasks
- **Utilization** (scheduled time / total time span)
- **Overlap verification** to ensure correctness

---

## Input Format (CSV)

```csv
id,start,end,value
T1,0,60,50
T2,30,90,80
T3,70,120,30
...
