#include "GraspSolver.h"

#include <vector>
#include <iostream>
#include <algorithm>

#include "../input/Data.h"

#include "../util/Random.h"

using namespace std;
 
bool GraspSolver::solve()
{
	for (int k = 0; k < 30'000; k++)
	{
		Solution current = solveOne(k == 0);
		if (k == 0 || current.cost < solution.cost)
		{
			solution = current;
			cout << "Grasp: " << current << endl;
		}
	}

	return true;
}

Solution GraspSolver::solveOne(bool deterministic)
{
	Solution current;
	current.nodes.push_back(0);

	vector<bool> visited(data.dimension, false);
	visited[0] = true;

	for (int _ = 1; _ < data.dimension; _++)
	{
		int last = current.nodes.back();
		vector<pair<double, int>> candidates;

		double total = 0.0;
		for (int j = 1; j < data.dimension; j++)
			if (!visited[j])
			{
				candidates.push_back({ 1.0 / data.costs[last][j], j });
				total += 1.0 / data.costs[last][j];
			}

		for (auto& candidate : candidates)
			candidate.first /= total;

		sort(candidates.begin(), candidates.end(), greater<pair<double, int>>());

		int next = candidates.front().second;
		if (!deterministic)
		{
			double r = Random::randomDouble();
			double total = 0.0;
			for (const auto& candidate : candidates)
			{
				total += candidate.first;
				if (r <= total)
				{
					next = candidate.second;
					break;
				}
			}
		}

		current.nodes.push_back(next);
		visited[next] = true;
	}
	current.nodes.push_back(0);
	current.evaluate();

	return current;
}
