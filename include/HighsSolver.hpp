#include "SolverInterface.hpp"

class HighsSolver : public SolverInterface {
public:
    std::optional<LpSolution> solve(const std::string &lpFilePath);
    virtual ~HighsSolver();
};