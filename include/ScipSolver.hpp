#include "SolverInterface.hpp"

class ScipSolver : public SolverInterface {
public:
    std::optional<LpSolution> get_solution(const std::string &lpFilePath);
    virtual ~ScipSolver();
};