#pragma once

#include "AbstractSolver.h"

class GraspSolver : public AbstractSolver
{
public:

	bool solve() override;

	Solution solveOne(bool deterministic = false);
};
