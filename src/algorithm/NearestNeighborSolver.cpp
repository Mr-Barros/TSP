#include "NearestNeighborSolver.h"

#include <vector>
#include <iostream>

#include "../input/Data.h"

using namespace std;

bool NearestNeighborSolver::solve()
{
	vector<bool> visited(data.dimension);

	solution.nodes.push_back(0);
	visited[0] = true;

	for (int _ = 1; _ < data.dimension; _++)
	{
		int last = solution.nodes.back();
		int next = -1;
		
		for (int j = 1; j < data.dimension; j++)
			if (!visited[j] && (next == -1 || data.costs[last][j] < data.costs[last][next]))
				next = j;

		solution.nodes.push_back(next);
		visited[next] = true;
	}
	solution.nodes.push_back(0);
	solution.evaluate();

	cout << "NearestNeighborSolver: " << solution << endl;

    return true;
}
