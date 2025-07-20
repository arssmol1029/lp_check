#include "SolverInterface.hpp"

class HighsSolver : public SolverInterface {
public:
    std::optional<LpSolution> get_solution(const std::string &lpFilePath);
    virtual ~HighsSolver();
};