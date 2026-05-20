#pragma once

#include "AbstractSolver.h"

#include <set>

class ChristofidesSolver: public AbstractSolver
{
public:

    bool solve() override;

private:
    struct Edge
    {
        int from;
        int to;
        int cost;

        bool operator>(const Edge& other) const;
    };

    std::vector<std::vector<int>> minimumSpanningTree(std::vector<std::vector<int>>& graph);

    std::set<int> oddDegreeNodes(std::vector<std::vector<int>>& graph);
};
