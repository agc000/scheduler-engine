#include "models.h"
#include "io.h"
#include "greedy_scheduler.h"
#include "weighted_scheduler.h"

#include <iostream>
#include <string>
#include <vector>

struct CliOptions {
    std::string m_inputFile = "";
    std::string m_mode = "greedy";
    bool m_showHelp = false;
    bool m_runTestStub = false;

    bool m_valid = true;
    std::string m_errorMessage = "";
};

static void print_usage(const char* program_name) {
    std::cout << "Usage: " << program_name << " --input <filepath> [--mode <greedy|weighted>]\n";
    std::cout << "\nOptions:\n";
    std::cout << "  --input    Path to CSV file with task data\n";
    std::cout << "  --mode     Scheduling algorithm: 'greedy' or 'weighted' (default: greedy)\n";
    std::cout << "  --test     Run test stub (no real tests yet)\n";
    std::cout << "  --help     Show this help message\n";
}

static CliOptions parse_args(int argc, char* argv[]) {
    CliOptions opts;

    if (argc <= 1) {
        opts.m_showHelp = true;
        return opts;
    }

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "--help" || arg == "-h") {
            opts.m_showHelp = true;
            return opts;
        } else if (arg == "--test") {
            opts.m_runTestStub = true;
        } else if (arg == "--input") {
            if (i + 1 >= argc) {
                opts.m_valid = false;
                opts.m_errorMessage = "Error: Missing value for --input";
                return opts;
            }
            opts.m_inputFile = argv[++i];
        } else if (arg == "--mode") {
            if (i + 1 >= argc) {
                opts.m_valid = false;
                opts.m_errorMessage = "Error: Missing value for --mode";
                return opts;
            }
            opts.m_mode = argv[++i];

            if (opts.m_mode != "greedy" && opts.m_mode != "weighted") {
                opts.m_valid = false;
                opts.m_errorMessage =
                    "Error: Invalid mode. Must be 'greedy' or 'weighted'.";
                return opts;
            }
        } else {
            opts.m_valid = false;
            opts.m_errorMessage = "Error: Unknown argument '" + arg + "'";
            return opts;
        }
    }

    if (!opts.m_runTestStub && opts.m_inputFile.empty() && !opts.m_showHelp) {
        opts.m_valid = false;
        opts.m_errorMessage = "Error: Missing required argument --input <filepath>";
        return opts;
    }

    return opts;
}

static void print_result_summary(const ScheduleResult& result) {
    std::cout << "\n--- Schedule Result ---\n";
    std::cout << "Scheduled tasks: " << result.m_scheduled.size() << "\n";
    std::cout << "Dropped tasks: " << result.m_dropped.size() << "\n";
    std::cout << "Total value: " << result.m_totalValue << "\n";

    std::cout << "\nScheduled task IDs:\n";
    for (size_t i = 0; i < result.m_scheduled.size(); i++) {
        std::cout << "  " << result.m_scheduled[i].m_id << "\n";
    }
}

int main(int argc, char* argv[]) {
    CliOptions opts = parse_args(argc, argv);

    if (opts.m_showHelp) {
        print_usage(argv[0]);
        return 0;
    }

    if (!opts.m_valid) {
        std::cerr << opts.m_errorMessage << "\n\n";
        print_usage(argv[0]);
        return 1;
    }

    std::cout << "\n=== SCHEDULING ENGINE ===\n";

    if (opts.m_runTestStub) {
        std::cout << "Running test stub... (not implemented yet)\n";
        std::cout << "OK\n";
        return 0;
    }

    std::cout << "Input file: " << opts.m_inputFile << "\n";
    std::cout << "Mode: " << opts.m_mode << "\n\n";

    std::vector<Task> tasks = io::read_tasks_from_csv(opts.m_inputFile);

    if (tasks.empty()) {
        std::cerr << "Error: No valid tasks loaded. Exiting.\n";
        return 1;
    }

    std::cout << "Loaded tasks: " << tasks.size() << "\n";

    ScheduleResult result;

    if (opts.m_mode == "greedy") {
        result = greedy_schedule(tasks);
    } else { // Weighted
        result = weighted_schedule(tasks);
    }

    print_result_summary(result);
    return 0;
}
