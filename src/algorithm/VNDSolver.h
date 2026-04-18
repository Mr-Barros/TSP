#pragma once

#include "Solver.h"

class Neighborhood;

class VNDSolver : public Solver
{
public:
	VNDSolver();
	~VNDSolver();
	
	bool solve() override;
	bool solve(Solution& initial);

private:
	std::vector<Neighborhood*> neighborhoods;
};
