#include "ChristofidesSolver.h"

#include "input/Data.h"

using namespace std;

bool ChristofidesSolver::solve()
{
    return false;
}

bool ChristofidesSolver::Edge::operator>(const Edge &other) const
{
    return cost > other.cost;
}

vector<vector<int>> ChristofidesSolver::minimumSpanningTree(vector<vector<int>>& graph)
{
    vector<vector<int>> mst(graph.size(), vector<int>(graph.size(), -1));
    priority_queue<Edge, vector<Edge>, greater<Edge>> edges;
    vector<bool> included(graph.size(), false);

    included[0] = true;
    for (int to = 0; to < graph.size(); to++)
        if (graph[0][to] > 0)
            edges.push(Edge(0, to, data.costs[0][to]));

    while (!edges.empty())
    {
        Edge e = edges.top();
        edges.pop();

        if (included[e.to])
            continue;

        mst[e.from][e.to] = e.cost;
        mst[e.to][e.from] = e.cost;

        included[e.to] = true;
        for (int to = 0; to < graph.size(); to++)
            if (!included[to] and graph[e.to][to] > 0)
                edges.push(Edge(e.to, to, graph[e.to][to]));
    }

    return mst;
}

set<int> ChristofidesSolver::oddDegreeNodes(vector<vector<int>>& graph)
{
    set<int> nodes;
    for (int u = 0; u < graph.size(); u++)
    {
        int degree = 0;
        for (int v = 0; v < graph.size(); v++)
            if (graph[u][v] > 0)
                degree++;

        if (degree % 2 == 1)
            nodes.insert(u);
    }
    return nodes;
}
