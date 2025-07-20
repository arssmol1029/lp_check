#include "SolverInterface.hpp"

class LpSolveSolver : public SolverInterface {
public:
    std::optional<LpSolution> get_solution(const std::string &lpFilePath);
    virtual ~LpSolveSolver();
};