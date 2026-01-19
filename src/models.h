#ifndef MODELS_H
#define MODELS_H

#include <string>
#include <vector>

struct Task {
    std::string m_id;
    int m_start;
    int m_end;
    int m_value;

    Task()
        : m_id(""), m_start(0), m_end(0), m_value(0) {}

    Task(const std::string& id, int start, int end, int value)
        : m_id(id), m_start(start), m_end(end), m_value(value) {}


    int duration() const {
        return m_end - m_start;
    }


    bool overlaps(const Task& other) const {
        return !(m_end <= other.m_start || other.m_end <= m_start);
    }
};

struct ScheduleResult {
    std::vector<Task> m_scheduled;
    std::vector<Task> m_dropped;
    int m_totalValue;

    ScheduleResult() : m_totalValue(0) {}
};

#endif
