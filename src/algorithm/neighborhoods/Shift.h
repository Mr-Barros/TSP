#pragma once

#include "Neighborhood.h"

class Solution;

class Shift : public Neighborhood
{
public:
	
	bool localSearch(Solution& solution) override;
	
	bool randomMove(Solution& solution) override;

private:
	struct Args
	{
		int pos;
		int profit;
	};

	bool evaluate(const Solution& solution, Args& args);
	void move(Solution& solution, const Args& args);
};
