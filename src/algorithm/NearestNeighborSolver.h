#pragma once

#include "AbstractSolver.h"

class NearestNeighborSolver : public AbstractSolver
{
public:

	bool solve() override;
};
