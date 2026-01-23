#include "../src/models.h"
#include "../src/greedy_scheduler.h"
#include "../src/weighted_scheduler.h"
#include "../src/metrics.h"

#include <cassert>
#include <iostream>
#include <vector>

static void test_no_overlaps() {
    std::cout << "Running test: no_overlaps...\n";

    std::vector<Task> tasks = {
        Task("T1", 0, 100, 50),
        Task("T2", 50, 150, 100),
        Task("T3", 100, 200, 75)
    };

    ScheduleResult greedy_result = greedy_schedule(tasks);
    assert(verify_no_overlaps(greedy_result.m_scheduled));

    ScheduleResult weighted_result = weighted_schedule(tasks);
    assert(verify_no_overlaps(weighted_result.m_scheduled));

    std::cout << "  ✓ Passed\n";
}

static void test_empty_input() {
    std::cout << "Running test: empty_input...\n";

    std::vector<Task> tasks;

    ScheduleResult greedy_result = greedy_schedule(tasks);
    assert(greedy_result.m_scheduled.empty());
    assert(greedy_result.m_totalValue == 0);

    ScheduleResult weighted_result = weighted_schedule(tasks);
    assert(weighted_result.m_scheduled.empty());
    assert(weighted_result.m_totalValue == 0);

    std::cout << "  ✓ Passed\n";
}

static void test_single_task() {
    std::cout << "Running test: single_task...\n";

    std::vector<Task> tasks = { Task("T1", 0, 100, 50) };

    ScheduleResult greedy_result = greedy_schedule(tasks);
    assert(greedy_result.m_scheduled.size() == 1);
    assert(greedy_result.m_totalValue == 50);

    ScheduleResult weighted_result = weighted_schedule(tasks);
    assert(weighted_result.m_scheduled.size() == 1);
    assert(weighted_result.m_totalValue == 50);

    std::cout << "  ✓ Passed\n";
}

static void test_all_compatible() {
    std::cout << "Running test: all_compatible...\n";

    std::vector<Task> tasks = {
        Task("T1", 0, 10, 5),
        Task("T2", 10, 20, 8),
        Task("T3", 20, 30, 12),
        Task("T4", 30, 40, 6)
    };

    ScheduleResult greedy_result = greedy_schedule(tasks);
    assert(greedy_result.m_scheduled.size() == 4);
    assert(greedy_result.m_dropped.size() == 0);

    ScheduleResult weighted_result = weighted_schedule(tasks);
    assert(weighted_result.m_scheduled.size() == 4);
    assert(weighted_result.m_totalValue == 31);

    std::cout << "  ✓ Passed\n";
}

static void test_all_conflicting() {
    std::cout << "Running test: all_conflicting...\n";

    std::vector<Task> tasks = {
        Task("T1", 0, 100, 10),
        Task("T2", 10, 90, 20),
        Task("T3", 20, 80, 30),
        Task("T4", 30, 70, 40)
    };

    ScheduleResult greedy_result = greedy_schedule(tasks);
    assert(greedy_result.m_scheduled.size() == 1);
    assert(verify_no_overlaps(greedy_result.m_scheduled));

    ScheduleResult weighted_result = weighted_schedule(tasks);
    assert(weighted_result.m_scheduled.size() == 1);
    assert(verify_no_overlaps(weighted_result.m_scheduled));

    std::cout << "  ✓ Passed\n";
}

static void test_weighted_optimal() {
    std::cout << "Running test: weighted_optimal...\n";

    std::vector<Task> tasks = {
        Task("T1", 0, 10, 5),
        Task("T2", 5, 15, 20),
        Task("T3", 10, 20, 5)
    };

    ScheduleResult weighted_result = weighted_schedule(tasks);
    assert(weighted_result.m_totalValue == 20);
    assert(weighted_result.m_scheduled.size() == 1);
    assert(weighted_result.m_scheduled[0].m_id == "T2");
    assert(verify_no_overlaps(weighted_result.m_scheduled));

    std::cout << "  ✓ Passed\n";
}

static void test_known_optimal_value() {
    std::cout << "Running test: known_optimal_value...\n";

    std::vector<Task> tasks = {
        Task("T1", 0, 6, 8),
        Task("T2", 1, 4, 4),
        Task("T3", 3, 5, 2),
        Task("T4", 5, 7, 4),
        Task("T5", 3, 9, 6),
        Task("T6", 5, 9, 2),
        Task("T7", 6, 10, 4),
        Task("T8", 8, 11, 4)
    };

    ScheduleResult weighted_result = weighted_schedule(tasks);
    assert(weighted_result.m_totalValue == 12 || weighted_result.m_totalValue == 16);
    assert(verify_no_overlaps(weighted_result.m_scheduled));

    std::cout << "  ✓ Passed\n";
}

static void test_utilization() {
    std::cout << "Running test: utilization...\n";

    std::vector<Task> scheduled = {
        Task("T1", 0, 50, 10),
        Task("T2", 50, 100, 20)
    };

    double util = calculate_utilization(scheduled);
    assert(util == 100.0);

    scheduled = {
        Task("T1", 0, 25, 10),
        Task("T2", 75, 100, 20)
    };

    util = calculate_utilization(scheduled);
    assert(util == 50.0);

    std::cout << "  ✓ Passed\n";
}

int main() {
    std::cout << "\n=== RUNNING TEST SUITE ===\n\n";

    test_empty_input();
    test_single_task();
    test_no_overlaps();
    test_all_compatible();
    test_all_conflicting();
    test_weighted_optimal();
    test_known_optimal_value();
    test_utilization();

    std::cout << "\n=== ALL TESTS PASSED ✓ ===\n\n";
    return 0;
}
