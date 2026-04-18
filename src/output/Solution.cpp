#include "Solution.h"

#include <format>

#include "../input/Data.h"

using namespace std;

void Solution::evaluate()
{
	const Data& data = Data::getInstance();

	cost = 0;
	for (size_t i = 0; i < nodes.size() - 1; i++)
		cost += data.costs[nodes[i]][nodes[i + 1]];
}

ostream& operator<<(ostream& os, const Solution& solution)
{
	const Data& data = Data::getInstance();
	os << format("{} ({:.2f}%)", solution.cost, (solution.cost - data.bks) / (double)data.bks * 100.0);
	return os;
}
