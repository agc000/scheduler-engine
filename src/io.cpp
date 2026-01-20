#include "io.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace io {

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");

    if (start == std::string::npos) {
        return "";
    }

    return str.substr(start, end - start + 1);
}

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(trim(token));
    }

    return tokens;
}

std::vector<Task> read_tasks_from_csv(const std::string& filepath) {
    std::vector<Task> tasks;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filepath << "\n";
        return tasks;
    }

    std::string line;
    bool first_line = true;
    int line_num = 0;

    while (std::getline(file, line)) {
        line_num++;
        line = trim(line);

        if (line.empty()) {
            continue;
        }

        if (first_line) {
            first_line = false;
            continue;
        }

        std::vector<std::string> fields = split(line, ',');

        if (fields.size() != 4) {
            std::cerr << "Warning: Line " << line_num
                      << " has incorrect number of fields (expected 4, got "
                      << fields.size() << "). Skipping.\n";
            continue;
        }

        try {
            std::string id = fields[0];
            int start = std::stoi(fields[1]);
            int end = std::stoi(fields[2]);
            int value = std::stoi(fields[3]);

            // Validate task
            if (end <= start) {
                std::cerr << "Warning: Task " << id
                          << " has invalid time range [" << start << ", " << end
                          << "]. Skipping.\n";
                continue;
            }

            if (value < 0) {
                std::cerr << "Warning: Task " << id
                          << " has negative value " << value
                          << ". Skipping.\n";
                continue;
            }

            tasks.emplace_back(id, start, end, value);
        } catch (const std::exception&) {
            std::cerr << "Warning: Line " << line_num
                      << " has invalid data format. Skipping.\n";
            continue;
        }
    }

    std::cout << "Loaded " << tasks.size() << " valid tasks from " << filepath << "\n";
    return tasks;
}

}