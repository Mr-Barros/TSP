#include "VNDSolver.h"

#include <vector>

#include "neighborhoods/Neighborhood.h"
#include "neighborhoods/Shift.h"
#include "neighborhoods/Swap.h"

#include "NearestNeighborSolver.h"

using namespace std;

VNDSolver::VNDSolver()
{
	neighborhoods.push_back(new Swap());
	neighborhoods.push_back(new Shift());
}

VNDSolver::~VNDSolver()
{
	for (Neighborhood* neighborhood : neighborhoods)
		delete neighborhood;
}

bool VNDSolver::solve()
{
	NearestNeighborSolver nearest;
	nearest.solve();
	return solve(nearest.solution);
}

bool VNDSolver::solve(Solution& initial)
{
	solution = initial;

	bool found = true;
	while (found)
	{
		found = false;
		for (Neighborhood* neighborhood : neighborhoods)
			if (neighborhood->localSearch(solution))
				found = true;
	}

	return true;
}