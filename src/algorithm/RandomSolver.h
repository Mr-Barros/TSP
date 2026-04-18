#pragma once

#include "AbstractSolver.h"

class RandomSolver : public AbstractSolver
{
public:
	bool solve() override;
};
