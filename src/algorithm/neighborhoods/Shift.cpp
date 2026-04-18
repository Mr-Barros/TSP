#include "Shift.h"

#include <iostream>

#include "../../input/Data.h"
#include "../../output/Solution.h"

using namespace std;

bool Shift::evaluate(const Solution& solution, Args& args)
{
    int prev = solution.nodes[args.pos - 1];
    int curr = solution.nodes[args.pos];
	int next = solution.nodes[args.pos + 1];
	int next2 = solution.nodes[args.pos + 2];

    args.profit = data.costs[prev][curr] + data.costs[next][next2] -
        data.costs[next][prev] - data.costs[curr][next2];

    return true;
}

void Shift::move(Solution& solution, const Args& args)
{
	swap(solution.nodes[args.pos], solution.nodes[args.pos + 1]);
    solution.evaluate();
}

bool Shift::localSearch(Solution& solution)
{
    bool any = false;
    bool found = true;
    while (found)
    {
        found = false;
        for (int pos = 1; pos < data.dimension - 1; pos++)
        {
            Args args(pos);
            evaluate(solution, args);
            if (args.profit > 0)
            {
                move(solution, args);
                found = any = true;
                cout << "[SH] " << solution << endl;
            }
        }
    }
    return any;
}

bool Shift::randomMove(Solution& solution) { return false; }
