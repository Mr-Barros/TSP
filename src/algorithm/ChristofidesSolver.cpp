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

vector<vector<ChristofidesSolver::Edge>> ChristofidesSolver::minimumSpanningTree(vector<vector<Edge>>& graph)
{
    vector<vector<Edge>> mst(graph.size());
    priority_queue<Edge, vector<Edge>, greater<Edge>> edges;
    vector<bool> included(graph.size(), false);

    int u = 0;
    included[u] = true;
    for (Edge edge : graph[u])
        edges.push(edge);

    while (!edges.empty())
    {
        Edge e = edges.top();
        edges.pop();

        if (included[e.to])
            continue;

        mst[e.from].push_back(Edge(e.from, e.to, e.cost));
        mst[e.to].push_back(Edge(e.to, e.from, e.cost));

        u = e.to;
        included[u] = true;
        for (Edge edge : graph[u])
            if (!included[edge.to])
                edges.push(edge);
    }

    return mst;
}

set<int> ChristofidesSolver::oddDegreeNodes(vector<vector<Edge>>& graph)
{
    set<int> nodes;
    for (int u = 0; u < graph.size(); u++)
        if (graph[u].size() % 2 == 1)
            nodes.insert(u);

    return nodes;
}

vector<vector<ChristofidesSolver::Edge>> ChristofidesSolver::perfectMatching(vector<vector<Edge>>& graph, set<int> nodes)
{
    vector<vector<Edge>> matching(graph.size());
    priority_queue<Edge, vector<Edge>, greater<Edge>> edges;

    for (int u : nodes)
        for (Edge edge : graph[u])
            if (u < edge.to and nodes.contains(edge.to))
                edges.push(edge);

    while (!edges.empty())
    {
        Edge e = edges.top();
        edges.pop();

        if (nodes.contains(e.from) and nodes.contains(e.to)) {
            matching[e.from].push_back(Edge(e.from, e.to, e.cost));
            matching[e.to].push_back(Edge(e.to, e.from, e.cost));
            nodes.erase(e.from);
            nodes.erase(e.to);
        }
    }

    return matching;
}