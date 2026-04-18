#include "Solver.h"

#include <stdexcept>

#include "RandomSolver.h"
#include "NearestNeighborSolver.h"
#include "GraspSolver.h"
#include "VNDSolver.h"

using namespace std;

bool Solver::solve()
{
	constexpr Type type = VariableNeighborhoodDecent;

	AbstractSolver* solver = nullptr;
	switch (type)
	{
	case AbstractSolver::Random: solver = new RandomSolver(); break;
	case AbstractSolver::NearestNeighbor: solver = new NearestNeighborSolver(); break;
	case AbstractSolver::GRASP: solver = new GraspSolver(); break;
	case AbstractSolver::VariableNeighborhoodDecent: solver = new VNDSolver(); break;
	default: throw runtime_error("Unknown solver type");
	}

	const bool ret = solver->solve();
	if (ret) solution = solver->solution;
	delete solver;

	return ret;
}
