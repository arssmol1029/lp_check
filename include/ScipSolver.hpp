#include "SolverInterface.hpp"

class ScipSolver : public SolverInterface {
public:
    std::optional<LpSolution> solve(const std::string &lpFilePath);
    virtual ~ScipSolver();
};