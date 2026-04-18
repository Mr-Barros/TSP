#pragma once

class Data;
class Solution;

class Neighborhood
{
public:
	Neighborhood();

	virtual bool localSearch(Solution& solution) = 0;

	virtual bool randomMove(Solution& solution) = 0;

protected:
	const Data& data;
};
