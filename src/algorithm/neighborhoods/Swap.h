#pragma once

#include "Neighborhood.h"

class Solution;

class Swap : public Neighborhood
{
public:

	bool localSearch(Solution& solution) override;

	bool randomMove(Solution& solution) override;

private:
	struct Args
	{
		int pos1;
		int pos2;
		int profit;
	};

	bool evaluate(const Solution& solution, Args& args);
	void move(Solution& solution, const Args& args);
};
