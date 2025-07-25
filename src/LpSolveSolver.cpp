#include "LpSolveSolver.hpp"
#include <lpsolve/lp_lib.h>
#include <fstream>
#include <iostream>



std::optional<LpSolution> LpSolveSolver::get_solution(const std::string& lpFilePath) {
    auto start = std::chrono::high_resolution_clock::now();
    
    std::string mutableStr = lpFilePath;
    char * lpFile = mutableStr.data(); // почему-то функции принимают char*, а не const char*
    lprec* lp = read_LP(lpFile, IMPORTANT, nullptr);
    if (!lp) {
        return std::nullopt;
    }
 
    int ret = solve(lp);
    if (ret != OPTIMAL) {
        delete_lp(lp);
        return std::nullopt;
    }


    double objVal = get_objective(lp);
    int numVars = get_Ncolumns(lp);
    std::vector<double> solution(numVars);
    get_variables(lp, solution.data());

    delete_lp(lp);

    auto end = std::chrono::high_resolution_clock::now();

    LpSolution result;
    result.objectiveValue = objVal;
    result.solution = std::move(solution);
    result.solveTime = std::chrono::duration<double>(end - start).count();

    return result;
}


LpSolveSolver::~LpSolveSolver() = default; 