#include "ChristofidesSolver.h"

#include <iostream>

#include "input/Data.h"

using namespace std;

bool ChristofidesSolver::solve()
{
    vector<vector<Edge>> graph(data.dimension);
    for (int from = 0; from < data.dimension; from++)
        for (int to = 0; to < data.dimension; to++)
            if (data.costs[from][to] > 0)
                graph[from].push_back(Edge(from, to, data.costs[from][to]));

    vector<vector<Edge>> mst = minimumSpanningTree(graph);
    set<int> nodes = oddDegreeNodes(mst);
    vector<vector<Edge>> matching = perfectMatching(graph, nodes);
    vector<vector<Edge>> multigraph = combineIntoMultigraph(mst, matching);
    vector<int> eulerTour = findEulerTour(multigraph);
    solution.nodes = convertIntoTSPTour(eulerTour);

    solution.evaluate();
    cout << "ChristofidesSolver: " << solution << endl;
    return true;
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

vector<vector<ChristofidesSolver::Edge>> ChristofidesSolver::perfectMatching(
    vector<vector<Edge>>& graph,
    set<int> nodes
) {
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

vector<vector<ChristofidesSolver::Edge>> ChristofidesSolver::combineIntoMultigraph(
    vector<vector<Edge>> &graph1,
    vector<vector<Edge>> &graph2
) {
    int size = max(graph1.size(), graph2.size());
    vector<vector<Edge>> multigraph(size);

    for (int u = 0; u < graph1.size(); u++) {
        for (Edge edge : graph1[u]) {
            multigraph[u].push_back(edge);
        }
    }

    for (int u = 0; u < graph2.size(); u++) {
        for (Edge edge : graph2[u]) {
            multigraph[u].push_back(edge);
        }
    }

    return multigraph;
}

void ChristofidesSolver::eulerTourDfs(
    int u,
    vector<vector<Edge>> &graph,
    set<pair<int, int>> &visEdges,
    vector<int> &eulerTour
) {
    for (int i = 0; i < graph[u].size(); i++)
    {
        pair<int, int> edgeID = make_pair(u, i);
        if (visEdges.contains(edgeID))
            continue;
        visEdges.insert(edgeID);
        eulerTourDfs(graph[u][i].to, graph, visEdges, eulerTour);
    }
    eulerTour.push_back(u);
}

vector<int> ChristofidesSolver::findEulerTour(vector<vector<Edge>> &graph)
{
    vector<int> eulerTour;
    set<pair<int, int>> visEdges;
    eulerTourDfs(0, graph, visEdges, eulerTour);
    ranges::reverse(eulerTour);
    return eulerTour;
}

vector<int> ChristofidesSolver::convertIntoTSPTour(vector<int>& eulerTour)
{
    vector<int> tspTour;
    set<int> visited;

    for (int u : eulerTour) {
        if (visited.contains(u))
            continue;
        tspTour.push_back(u);
        visited.insert(u);
    }

    return tspTour;
}
