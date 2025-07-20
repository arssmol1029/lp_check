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
public:
    virtual ~SolverInterface() = default;
    virtual std::optional<LpSolution> get_solution(const std::string &lpFilePath) = 0;
};