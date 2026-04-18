#pragma once

#include "../output/Solution.h"

class Data;

class AbstractSolver
{
public:
	AbstractSolver();
	virtual ~AbstractSolver() = default;

	enum Type
	{
		Random,
		NearestNeighbor,
		GRASP,
		VariableNeighborhoodDecent,
	};

	virtual bool solve() = 0;

	Solution solution;

protected:
	const Data& data;
};
