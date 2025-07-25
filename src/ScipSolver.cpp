#include "ScipSolver.hpp"
#include <scip/scip.h>
#include <scip/scipdefplugins.h>
#include <iostream>



std::optional<LpSolution> ScipSolver::get_solution(const std::string& lpFilePath) {
    auto start = std::chrono::high_resolution_clock::now();
    
    SCIP* scip = nullptr;

    SCIP_RETCODE retcode;
    retcode = SCIPcreate(&scip);
    if(retcode != SCIP_OKAY) {
        return std::nullopt;
    }

    retcode = SCIPincludeDefaultPlugins(scip);
    if(retcode != SCIP_OKAY) {
        SCIPfree(&scip);
        return std::nullopt;
    }

    SCIPsetIntParam(scip, "display/verblevel", 0);

    retcode = SCIPreadProb(scip, lpFilePath.c_str(), nullptr);
    if(retcode != SCIP_OKAY) {
        SCIPfree(&scip);
        return std::nullopt;
    }

    retcode = SCIPsolve(scip);
    if(retcode != SCIP_OKAY) {
        SCIPfree(&scip);
        return std::nullopt;
    }

    SCIP_STATUS status = SCIPgetStatus(scip);
    if (status != SCIP_STATUS_OPTIMAL) {
        SCIPfree(&scip);
        return std::nullopt;
    }

    SCIP_Real objVal = SCIPgetPrimalbound(scip);

    SCIP_VAR** vars = SCIPgetOrigVars(scip);
    int nvars = SCIPgetNOrigVars(scip);
    std::vector<double> solution;

    for(int i = 0; i < nvars; ++i) {
        SCIP_Real val = SCIPgetSolVal(scip, nullptr, vars[i]);
        solution.push_back(double(val));
    }

    SCIPfree(&scip);

    auto end = std::chrono::high_resolution_clock::now();

    LpSolution result;
    result.objectiveValue = objVal;
    result.solution = std::move(solution);
    result.solveTime = std::chrono::duration<double>(end - start).count();

    return result;
}

ScipSolver::~ScipSolver() = default; 