#pragma once
#include <string>
#include <vector>
#include <optional>
#include <chrono>

struct LpSolution {
    double objectiveValue;
    std::vector<double> solution;
    double solveTime;
};

class SolverInterface {
    std::string solverName;
public:
    virtual ~SolverInterface() = default;
    virtual std::optional<LpSolution> get_solution(const std::string &lpFilePath) = 0;
    void set_name(const std::string &name) {
        solverName = name;
    }
    const std::string get_name() {
        return solverName;
    }
};