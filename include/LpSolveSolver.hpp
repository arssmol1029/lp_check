#include "SolverInterface.hpp"

class LpSolveSolver : public SolverInterface {
public:
    std::optional<LpSolution> solve(const std::string &lpFilePath);
    virtual ~LpSolveSolver();
};