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
        int id;

        static inline int uniqueID = 0;
        bool operator>(const Edge& other) const;
    };

    void createNewEdge(std::vector<std::vector<Edge>>& graph, int from, int to, int cost);

    std::vector<std::vector<Edge>> minimumSpanningTree(std::vector<std::vector<Edge>>& graph);

    std::set<int> oddDegreeNodes(std::vector<std::vector<Edge>>& graph);

    std::vector<std::vector<Edge>> perfectMatching(std::vector<std::vector<Edge>>& graph, std::set<int> nodes);

    std::vector<std::vector<Edge>> combineIntoMultigraph(
        std::vector<std::vector<Edge>>& graph1,
        std::vector<std::vector<Edge>>& graph2
    );

    void eulerTourDfs(
        int u,
        std::vector<std::vector<Edge>>& graph,
        std::set<int>& visEdges,
        std::vector<int>& eulerTour
    );

    std::vector<int> findEulerTour(std::vector<std::vector<Edge>>& graph);

    std::vector<int> convertIntoTSPTour(std::vector<int>& eulerTour);
};
