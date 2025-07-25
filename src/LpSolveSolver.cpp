#include "LpSolveSolver.hpp"
#include <lpsolve/lp_lib.h>
#include <fstream>
#include <iostream>



std::optional<LpSolution> LpSolveSolver::get_solution(const std::string& filePath) {
    bool isMps = filePath.size() > 4 && 
                filePath.substr(filePath.size() - 4) == ".mps";
    bool isLp = filePath.size() > 3 && 
                filePath.substr(filePath.size() - 3) == ".lp";
    
    if (!isMps && !isLp) {
        std::cerr << "Формат файла не поддерживается" << filePath << std::endl;
        return std::nullopt;
    }

    auto start = std::chrono::high_resolution_clock::now();

    lprec* lp = nullptr;
    if (isMps) {
        lp = read_MPS(const_cast<char*>(filePath.c_str()), IMPORTANT); // почему-то функции принимают char*, а не const char*
    } else {
        lp = read_LP(const_cast<char*>(filePath.c_str()), IMPORTANT, nullptr);
    }

    if (!lp) {
        return std::nullopt;
    }

    set_timeout(lp, 30);

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