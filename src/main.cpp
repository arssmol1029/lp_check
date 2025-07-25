#include "SolverInterface.hpp"
#include "LpSolveSolver.hpp"
#include "HighsSolver.hpp"
#include "ScipSolver.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <dirent.h>
#include <sys/stat.h>


void print_separator(const std::string& symbol = "═", int length = 40) {
    for (int i = 0; i < length; ++i) {
        std::cout << symbol;
    }
    std::cout << std::endl;
}


struct FileInfo {
    std::string name;
    std::string fullPath;
};

void findTestsRec(const std::string& path, std::vector<FileInfo>& files) {
    DIR* dir;
    struct dirent* ent;
    
    if ((dir = opendir(path.c_str())) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            std::string name = ent->d_name;
            if (name == "." || name == "..") {
                continue;
            }
            
            std::string fullPath = path + "/" + name;
            struct stat path_stat;
            stat(fullPath.c_str(), &path_stat);
            
            if (S_ISDIR(path_stat.st_mode)) {
                findTestsRec(fullPath, files);
            } else {
                if (name.size() > 4 && 
                        (name.substr(name.size() - 4) == ".mps" || 
                        name.substr(name.size() - 3) == ".lp")) {
                    FileInfo file;
                    file.name = name;
                    file.fullPath = fullPath;
                    files.push_back(file);
                }
            }
        }
        closedir(dir);
    }
}


int main() {
    std::string test_dir = "tests";
    std::vector<FileInfo> files;

    findTestsRec(test_dir, files);


    std::vector<std::unique_ptr<SolverInterface>> solvers;
    solvers.push_back(std::make_unique<LpSolveSolver>());
    solvers.back()->set_name("lp_solve");
    solvers.push_back(std::make_unique<HighsSolver>());
    solvers.back()->set_name("highs");
    solvers.push_back(std::make_unique<ScipSolver>());
    solvers.back()->set_name("scip");


    std::cout << "Benchmarking LP solvers..." << std::endl;


    for (const auto& file : files) {
        std::cout << "\n─── Testing file: " << file.name << " ───\n\n";
        for (const auto& solver : solvers) {
            std::cout << "Solver: " << solver->get_name() << std::endl;
            auto solution = solver->get_solution(file.fullPath);
            if (solution) {
                std::cout << "Objective Value: " << std::fixed << std::setprecision(2)
                          << solution->objectiveValue << std::endl;

                std::cout << "Solve Time: " << solution->solveTime 
                          << " seconds" << std::endl;
            } else {
                std::cout << "Failed to solve problem." << std::endl;
            }
            std::cout << std::endl;
        }
        print_separator();
    }

    return 0;
}