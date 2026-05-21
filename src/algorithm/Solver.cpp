#include "Solver.h"

#include <stdexcept>

#include "ChristofidesSolver.h"
#include "input/Parameters.h"

#include "RandomSolver.h"
#include "NearestNeighborSolver.h"
#include "GraspSolver.h"
#include "SimulatedAnnealingSolver.h"
#include "VNDSolver.h"

using namespace std;

bool Solver::solve()
{
	AbstractSolver* solver = nullptr;
	switch (params.solverType)
	{
	case Parameters::Random: solver = new RandomSolver(); break;
	case Parameters::NearestNeighbor: solver = new NearestNeighborSolver(); break;
	case Parameters::GRASP: solver = new GraspSolver(); break;
	case Parameters::VariableNeighborhoodDecent: solver = new VNDSolver(); break;
	case Parameters::Christofides: solver = new ChristofidesSolver(); break;
	case Parameters::SimulatedAnnealing: solver = new SimulatedAnnealingSolver(); break;
	default: throw runtime_error("Unknown solver type");
	}

	const bool ret = solver->solve();
	if (ret) solution = solver->solution;
	delete solver;

	return ret;
}
