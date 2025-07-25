#include "HighsSolver.hpp"
#include <highs/Highs.h>
#include <iostream>



std::optional<LpSolution> HighsSolver::get_solution(const std::string& lpFilePath) {
    auto start = std::chrono::high_resolution_clock::now();
    
    Highs highs;
    highs.setOptionValue("output_flag", false);
    highs.setOptionValue("time_limit", 30.0);
    
    HighsStatus status = highs.readModel(lpFilePath);
    if (status != HighsStatus::kOk) {
        return std::nullopt;
    }

    status = highs.run();
    if (status != HighsStatus::kOk) {
        return std::nullopt;
    }

    const HighsModelStatus& model_status = highs.getModelStatus();
    if (model_status != HighsModelStatus::kOptimal) {
        return std::nullopt;
    }

    const HighsSolution& sol = highs.getSolution();

    auto end = std::chrono::high_resolution_clock::now();

    LpSolution result;
    result.objectiveValue = highs.getObjectiveValue();
    result.solution.assign(sol.col_value.begin(), sol.col_value.end());
    result.solveTime = std::chrono::duration<double>(end - start).count();

    return result;
}

HighsSolver::~HighsSolver() = default; 