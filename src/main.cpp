#include "SolverInterface.hpp"
#include "LpSolveSolver.hpp"
#include "HighsSolver.hpp"
#include "ScipSolver.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <dirent.h>



int main() {
    std::string test_dir = "tests";
    std::vector<std::string> files;
    DIR* dir;
    struct dirent* ent;
    
    if ((dir = opendir(test_dir.c_str())) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            std::string filename = ent->d_name;
            if (filename.size() > 3 && 
                filename.substr(filename.size() - 3) == ".lp") {
                files.push_back(filename);
            }
        }
        closedir(dir);
    }

    std::vector<std::unique_ptr<SolverInterface>> solvers;
    solvers.push_back(std::make_unique<LpSolveSolver>());
    solvers.push_back(std::make_unique<HighsSolver>());
    solvers.push_back(std::make_unique<ScipSolver>());

    std::cout << "Benchmarking LP solvers..." << std::endl;

    for (const auto& file : files) {
        std::cout << "Testing file: " << file << std::endl;
        for (const auto& solver : solvers) {
            auto solution = solver->get_solution(test_dir + "/" + file);
            if (solution) {
                std::cout << "Solver: " << typeid(*solver).name()  << std::endl
                          << "Objective Value: " << std::fixed << std::setprecision(2)
                          << solution->objectiveValue << std::endl
                          << "Solve Time: " << solution->solveTime 
                          << " seconds" << std::endl;
            } else {
                std::cout << "Solver: " << typeid(*solver).name() 
                          << ", failed to solve problem." << std::endl;
            }
        }
    }

    return 0;
}